#include <cs50.h>
#include <stdio.h>
#include <math.h>

/*  greedy algorithm that returns the fewest total coins possible to make 
    up the amount inputted from the user

*/



int main(void){

    
    // Take value:
    float cash = 0; 
    
    while (cash <= 0){
    
        printf("How many dollars would you like to change?\n" );
        cash = GetFloat();
    }
    
    int cashint = round(cash * 100);
    
    // Determine amount of quarters
    int remq = 0;  int remd = 0; int remn = 0; int remp = 0;
    
    int quarters = 0;
    int dimes = 0;
    int nickles = 0;
    int pennies = 0;
     
     
    if (cashint >= 25){
    
        remq = (cashint) % 25;
     
        quarters = (cashint - remq) / 25;
     
    }
    
    else { remq = cashint; }
         
    
    if (remq >= 10){
     
        remd = (remq) % 10;
         
        dimes = (remq - remd) / 10;
    }
     
    
     
    if (dimes == 0){  
          remd = remq; 
        
    }
          
          
    if (remd >= 5){
     
        remn = (remd) % 5;
        nickles = (remd - remn) / 5;
         
     }
          
    if (nickles == 0){  
          remn = remd;
    }
          
    if (remn >= 1){
     
        remp = (remn) % 1;
        pennies = (remn - remp) / 1;
         
    }
         
    printf("%i\n", quarters + dimes + nickles + pennies); 
    
}


 
