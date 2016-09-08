#include <cs50.h>
#include <stdio.h>
#include <math.h>


int main(void){
    
    int rows = -1; 
    
    while (rows < 0 || rows > 23)
    {
        printf("Enter the number of rows: ");
        rows = GetInt();
    }
    
    if (rows == 0)
    {
    
    }
    else 
    {
        for (int j = 1; j <= rows; j++)
        {
    
            for (int ii = 1; ii <= (rows - j); ii++)
            {
                printf(" ");
            }
                
            for (int i = 1; i <= j; i++)
            {
                printf("#");
            }
            
            printf("#\n");
        
        }
    }

}