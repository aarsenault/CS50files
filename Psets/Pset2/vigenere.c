#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


/*  
    VIGENERE CYPHER: takes a command line cypher code in the form of 
    a keyword and decripts the prompted input 
*/

// funciton which gives each letter (case insensitive) a value from 1-26 where a = 1 ;
int shifter( char letter );

int main(int argc, string argv[])
{
    // Checks to see if the correct comand line args are given
    if (argc != 2)
    {
        
        printf("You didn't enter the correct no. of command line arguments \n");
        
        return(1);
    }
    
    // Creates an array to contain the keyword
    else
    {   
        // char key[keylen];
        int keylen = strlen(argv[1]);
        for (int i = 0; i < keylen; i++)
        {
            if ( !(isalpha(argv[1][i]) ) )
            {
                printf( "You need to enter only letters \n");
                return(1);
            }
        }
        
    }
       
    // string to encrypt from user   
    string phrase = GetString();
    // gets length of key
    int keylen = strlen(argv[1]);
    int ii = 0;  
 
    
    // Sorts into upper and lower case, else special, and ecnripts
    for ( int i = 0, n = strlen(phrase); i < n; i++)
    {
        if ( isalpha(phrase[i]) )
        {
            // sets k, the amount to adjust each time
            int k = shifter( argv[1][(ii % keylen)] );
            
            ii++;
            
            //int k  = shifter("k");
            
            // looks for uppercase letters that are out of bounds  
            if ( isupper(phrase[i]) && ((int) phrase[i] + k) > 90)
            {
                printf( "%c", (  (( (int) phrase[i] + k) % 90) + 64) );
            }
            else if (isupper( phrase[i])) 
            {
                printf( "%c", ( (int) phrase[i] + k) );
            }
            // looks for lower case that are out of bounds  
            else if ( islower( phrase[i]) && ((int) phrase[i] + k) > 122  )
            {
                printf( "%c", ( (( (int) phrase[i] + k) % 122) + 96 ) );
            }
            else if (islower( phrase[i])) 
            {
                printf( "%c", ( (int) phrase[i] + k));
            }
            // prints special charachters as is - no cipher    
        }
        else 
            {
                printf( "%c", ( (int) phrase[i]));
            }
    
    // appends a new line
    printf("\n");
            
    
}


int shifter( char letter )
{
    // sets k, the amount to adjust each time
    if ( isupper( letter ) )
        {
         return( ( (int) letter ) % 65 ); 
        }
    else
        {
            return( ( (int) letter ) % 97);
        }
}
