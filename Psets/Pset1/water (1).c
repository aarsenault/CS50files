#include <cs50.h>
#include <stdio.h>

int main(void){
    
    /* program to calculate the equivalent amount of bottles of watter used per shower
    
    odds are your shower spits out 1.5 gallons of water per minute. 
    A gallon, meanwhile, is 128 ounces, and so that shower spits out 1.5 × 128 = 192 ounces of water per minute. 
    A typical bottle of water (that you might have for a drink, not a shower), meanwhile, might be 16 ounces. 
    So taking a 1-minute shower is akin to using 192 ÷ 16 = 12 bottles of water. */
    
    int mins;
    int bottles;
    
   
    printf("Minutes per shower:\n");
    
    mins = GetInt(); 
    
    while(mins <= 0) 
    {
        printf("Retry:");
        mins = GetInt(); 
    
    }
    
    bottles = 12 * mins;
    
    printf("Bottles: %i \n", bottles);
    
}
    
    
    

    
    
    
    
     
    


