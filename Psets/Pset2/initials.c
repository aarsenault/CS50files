#include <cs50.h>
#include <stdio.h>
#include <string.h>

/*

    Initials take input from the user and returns the User's Initials

*/

int main(void)
{
    
    printf("Please type your name: \n");
    string name = GetString(); 
    
    
    int length = strlen(name);
    int intArr[length];
    
    for (int i = 0; i < length; i++)
    {
        intArr[i] = (char) name[i];
    }
    
    // Find all instances of space
    
    if (intArr[0] < 65 || intArr[0] > 90 )
    {
        printf("%c", (intArr[0] - 32));
    }
    else 
    {
        printf("%c", intArr[0]); 
    }
        
    for ( int i = 0; i < length; i++)
    {
            
        if (intArr[i - 1] == 32)
        {
            if (intArr[i] < 65 || intArr[i] > 90)
            {
                printf("%c", (intArr[i] - 32) );
            }    
            else 
            {   
                printf("%c", intArr[i] ); 
            }
        }
    
    }
    
    // Print out the initials
    printf("\n");
}

