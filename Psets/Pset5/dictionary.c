/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

// this is included just to declare them first I guess. 
#include "dictionary.h"


// Global Variable Declarations

// pointer to first node - First node lives on the heap
node root_node; // root node lives on the stack.
node* trav; // initialize here, lives on the heap 
int words_loaded = 0; 

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // gets passed word that already assumes correct letters and no numbers
    // moving through the word's letters 
    
    int i = 0; 
    // declare a buffer for the new word
    char lower_word[LENGTH]; 
    int char_pos = 0;
    
    
    while ( word[i] != '\0' ) 
    {
        // Convert all capitals to lower case
        int l = word[i]; // converts the letter to int
        
        if ( l >= 65 && l <= 90)
        {
            l = l + 32; 
        }
        else if (l == 39 || ( l >= 97 && l <= 122) )
        {   
            // Do nothing - allow Apostrophe + lowercase
        } 
        else 
        {
            printf("ERROR: non alpha or apostrophe being passed \n");
            return 3;
        }
        
        lower_word[i] = l;
        i++;  
        
        if (word[i] == '\0')
        {
            lower_word[i] = '\0'; 
        }
        
    } // end of lower conversion. 
    
    
     // Check Against dictionary Trie
    i = 0; 
    trav = &root_node; // set here for now. 
    
    while(lower_word[i] != '\0')
    {
        // convert letter to pos in trie
        char_pos = triepos(lower_word[i]);
        if (char_pos == -1)
        {
            // Unsupported Position
            return 3;
        }
        
        // check in trie. 
        // this is all while  != '\0'
        if (trav->letter[char_pos] != NULL)
        {
            trav = trav->letter[char_pos];
        }
        else if (trav->letter[char_pos] == NULL)
        {
            return false;
        }
        
        i++;
    }
        
    if (trav->is_word == 1)
    {
        return true;
    }    
    else
    {
        return false;    
    }

}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // set the traveling node 
    node* trav = &root_node; 
    
    // Begin Loading words
    // "dictionary" should be a string
    FILE* dict = fopen(dictionary , "r"); //
    
    if (dict == NULL)
    {
        printf("Dictionary file does not exist.\n");
        return 2;
    }
    
    char buffer[LENGTH + 1 ] = { 0 }; // + 1 to make room for "\0"
    
    // runs over every word in dictionary
    // while there is still a string left, i.e != EOF
    while( fscanf( dict, "%s", buffer) == 1) 
    {
        // resets the buffer position
        int char_pos = 0; 
        int buffer_pos = 0;
        
        // now need to go through letter by letter for buffer. 
        while (buffer[buffer_pos] != '\0') 
        {
            // convert letters to position in node. 
            // triepos is a funct defined below. 
            char_pos = triepos(buffer[buffer_pos]); 
            
            if (char_pos == -1) // check not garbage in
            {
                return false;
            }
            
            // storing 
            if (trav->letter[char_pos] == NULL) // at first set to root node
            {
                // malloc a new node
                node* new_node = malloc(sizeof(node)); 
                // put pointer to new node in letter's position node.letter[pos]
                trav->letter[char_pos] = new_node;
            }
            
            // moves the traveling pointer to the pointer in letter[char_pos]
            trav = trav->letter[char_pos];
            
            buffer_pos++; 
    
            
        } // When while loop breaks due to (nextchar = "\0")
            
        // bool value of last new node malloced 
        (trav->is_word) = 1;
        words_loaded++; 
        
        // set the traveler back to the root node for the next word
        trav = &root_node; // Root node is on stack - need ptr so &     
    }         
    
    // close file
    fclose(dict);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    
    // Can just make a counter out of the Load section
    
    return words_loaded;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for( int i = 0; i <= (LETTERLENGTH - 1); i++)
    {   
        if (root_node.letter[i] != NULL)
        {
            nodefree(root_node.letter[i]);
        }
    }
    
    return true;
}


/**
 * Converts lower case letters into a position in the trie array and returns
 * that value
 */
int triepos(const char letter)
{
    int l = letter; // converts to a number    
    int pos = 0; 
        
    if (l == 39) // Apostrophe
    {
        pos = 26; // 0-25 for alpha
    }
    else if ( l >= 65 && l <= 90) // Uppercase
    {
        pos = (l + 32) % 97; 
    }
    else if ( l >= 97 && l <= 122) // Lowercase
    {
        pos = l % 97;      
    }
    else
    {
        printf("ERROR: attempt to load unsupported char \n");
        return -1; // normal values must be positive
    }
    
    return pos; 
}


/**
 * Frees the memory of a node
 * 
**/


bool nodefree(struct node* next_node)
{
    // cycles recursively - once greater than Letterlength
    // then it frees the node
    for (int i = 0; i <= (LETTERLENGTH ); i++) 
    {   
        
        // if has gone all the way through letters
        // base case
        if (i == (LETTERLENGTH ) )
        {   
            // node is a ptr
            free(next_node);
            return true; 
        }   
        else if ( (next_node->letter[i]) == NULL)
        {
            // DO nothing, move to next i
        }
        else if ( (next_node->letter[i]) != NULL)
        {
            nodefree( next_node->letter[i] );
        }
    }         
    return true; 

}