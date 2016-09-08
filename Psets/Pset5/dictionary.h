/**
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// length of the alphabet - A-Z is 26, plus '\'' (reminder, including 0)
#define LETTERLENGTH 27 // This is Absolute - 



// Create Dictionary node structure
typedef struct node
{
    bool is_word;

    // there is an array of LETTERLENGTH pointers to type "struct node"
    struct node* letter[ LETTERLENGTH ]; 
}
node;


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/**
 * Turns a letter l into a position in the trie - returns the position
 */
 
int triepos(const char letter); 

/**
 * Recursive function to free mem. in trie
 */

bool nodefree(struct node* next_node);

#endif // DICTIONARY_H
