#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*

    A program to impliment a simple Caesar cypher encription of imputted text. 
    
    USAGE - takes an int, as number of letters to shift
          - takes a string to encrypt
*/

int main(int argc, string argv[])
{
    // place holder for cipher
    int k  = 0; 
    // Checks to see if the correct comand line args are given
    if (argc != 2)
    {
        
        printf("You didn't enter the correct no. of command line arguments \n");
        
        return(1);
    }
    else // modulos the key to get something < 26
    {
        k = atoi(argv[1]) % 26;
       
        // checks the key is infact numerical       
        if (k == 0)
        { 
            printf("Need type positive integer \n");
            
            return(2);
        }
    }
       
    // string to encrypt from user   
    string phrase = GetString();
  
  
    // Sorts into upper and lower case, else special, and ecnripts
    for ( int i = 0, n = strlen(phrase); i < n; i++)
    {
            
        // looks for uppercase letters that are out of bounds  
        if (isupper(phrase[i]) && ((int) phrase[i] + k) > 90)
        {
            
            
            printf( "%c", ( ( ( (int) phrase[i] + k) % 90) + 64) );
        }
            
        else if (isupper(phrase[i]) ) 
        {
            
            printf( "%c", ( (int) phrase[i] + k) );
        }
        
        // looks for lower case that are out of bounds  
        else if ( islower( phrase[i]) && ((int) phrase[i] + k) > 122  )
        {
            printf( "%c", ( ( ( (int) phrase[i] + k) % 122) + 96 ) );
        }
            
            
        else if (islower( phrase[i])) 
        {
            printf( "%c", ( (int) phrase[i] + k) );
        }
        
        // prints special charachters as is - no cipher    
        else
        {
            printf( "%c", ( (int) phrase[i]));
        }    
            
        
    }
    
    // appends a new line
    printf("\n");
            
     
}