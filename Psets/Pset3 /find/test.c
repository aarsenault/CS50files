#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "helpers.h"

const int MAX = 65536

int main(int argc, string argv[])
{
    // fill haystack
    int size;
    int haystack[MAX];
    for (size = 0; size < MAX; size++)
    {
        // wait for hay until EOF
        printf("\nhaystack[%i] = ", size);
        int straw = GetInt();
        if (straw == INT_MAX)
        {
            break;
        }
     
        // add hay to stack
        haystack[size] = straw;
    }
    printf("\n");
    

    sort(haystack, size);
    for ( int i = 0; i<size; i++)
    {
            printf("%i \n ", i);
    }
        
        
    
    
}

