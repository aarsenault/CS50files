/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
 

bool search(int value, int values[], int n)
{

    // Binary Search: 
    
    int start = 0;  
    int end = n - 1;
    int old_end = 0;
    
    if ( (value > values[end]) || (value < values[start]) )
    {
        return false; 
    }
    
    while (end > start)    
    {   
        // checks the trivial condition
        if ( (value == values[end]) || (value == values[start]) )
        {
            return true; 
        }
        
        // checks if the array has collapsed
        // Prevents an infinite loop
        else if ( end == (start + 1) ) 
        {
              return false; 
        }
        
        // Shrinks the end by ~1/2 array size
        else if ( value < values[end] )
        {
            old_end = end;
            
            // the length of matrix = old_end - start
            end = old_end - (old_end - start) / 2;
        }
        
        // Adjusts the range of the array to ensure values
        // is within
        else 
        {
            start = end;
            end = old_end;
        }
        
    }
    
   

            
    
    
}

/**
 * Sorts array of n values via bubble sort
 * O(n^2)
 */
 
 
void sort( int values[], int n )
{
    // Does the bubbling over list n times
    for ( int j = 1, counter = 0; j < n; j++ )
    {
        // runs over elements (i) up to n - j
        for ( int i = 0, swap = 0; i < (n - j); i++ )
        {
            // checks and swaps two values
            if (values[i + 1] < values[i])
            {
                // swap is place holder
                swap = values[i];
                values[i] = values[i + 1];
                values[i + 1] = swap;
                // counter counts the num of swaps
                counter = 1;
            }
        }
        
        // if no more swaps then it's sorted
        if (counter == 0)
        {
            return;
        }
    }
    
    return;
}