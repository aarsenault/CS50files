#include <cs50.h>
#include <stdio.h>
#include <math.h>


/* 

credit.c script takes a credit card number from prompt and 
checks the validity of the following:

American Express uses 15-digit numbers,
MasterCard uses 16-digit numbers, 
and Visa uses 13- and 16-digit numbers.

American Express numbers all start with 34 or 37; 
MasterCard numbers all start with 51, 52, 53, 54, or 55; 
and Visa numbers all start with 4

*/


int main(void)
{
    
    // Prompt user for number
    printf("Number:");
    long long int ccnumber = GetLongLong(); 

    
    // make a copy of cc_number for computation
    long long ccnumber_2 = ccnumber;

    // determine how many digits ccnumber is
    int digits = 0; 
    while (ccnumber_2 > 0)
    {
        ccnumber_2 = ccnumber_2 / 10;
       
        digits++;
        // printf("ccnumber now: %lli \n", ccnumber_2);
    }

    if (digits == 16 || digits == 15 || digits == 13 || digits == 14)
    {
        // printf("card VALID, digits: %i \n", digits);
    }
    else
    {
        // printf("INVALID, digits: %i \n", digits);
        printf("INVALID\n");

        return 0; 
    }
  
    
    // Check Syntactical Validity with following formula:
    /*  1.  Multiply every other digit by 2, starting with the number’s second-to-last digit,
            and then add those products' digits together.

        2.  Add the sum to the sum of the digits that weren’t multiplied by 2.

        3.  If the total’s last digit is 0 (or, put more formally, 
            if the total modulo 10 is congruent to 0), the number is valid!
    */ 
    

    long long numbuffer = 0; 
    
    ccnumber_2 = ccnumber; 
    long long power = 0; 
    bool odd = false; 
    long long odd_buffer = 0; 
    int odd_sum = 0; 
    int even_sum = 0; 
    
    for (int i = 0; i < digits + 1; i++)
    {
        power = 10; 
        
        numbuffer = ccnumber_2 % power; 
        
        // debug
        // printf("current digit: %lli \n", numbuffer);
        
        // add to sums
        if (odd)
        {
            odd_buffer = numbuffer * 2;
            odd_sum = odd_sum + (odd_buffer % 10) + ( (odd_buffer - (odd_buffer % 10)) / 10 ); 
        }
        else
        {
            even_sum = even_sum + numbuffer; 
        }
        
        ccnumber_2 = (ccnumber_2 - numbuffer * power / 10) / power;
        
        // flip the odd marker
        odd = !odd; 
    }
      
    // now odd_sum is the total sum    
    odd_sum = odd_sum + even_sum; 
    
    if (odd_sum % 10 == 0)
    {
        // if true continue
        //printf("Card check is valid \n");
    }
    else
    {
        // DEBUG
        // printf("card check not valid \n");
        printf("INVALID\n"); 
        return false;
    }
        
    // Determine Type
    // Should also be separated by digit length - for now will put longest types first
   
    if (ccnumber / 100000000000000 >= 51 && ccnumber / 100000000000000 <= 55) 
    {
        printf("MASTERCARD\n");
    }
    else if (ccnumber / 10000000000000 == 34 || ccnumber / 10000000000000 == 37 || ccnumber / 1000000000000 == 34 || ccnumber / 100000000000 == 37)
    {
        printf("AMEX\n");
    }
    else if (ccnumber / 1000000000000 == 4 || ccnumber / 1000000000000000 == 4)
    {
        printf("VISA\n"); 
    }
    else
    {
        printf("INVALID\n"); 
    }
    

}



