/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE; 

int main(void)
{
    
    // Initialize Variables:
    int jpg_count = -1; 
    
    // int buff[128] = {0}; // initialized to 0 
    
    BYTE buff[512]; 
    
    // Input the file: 
    FILE* file = fopen("card.raw", "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", "card.raw");
        return 1;
    }
    
    // Reads into address of buff, 512 bytes, 1 time, from file
    // FILE* cur_jpg = fopen("000.jpg", "a");
    
    FILE* cur_jpg = NULL; 
    
    // needs a while loop to check if there is enough bytes left.  
    while (fread( &buff, 1, 512, file ) == 512)
    {
        if ( buff[0] == 0xff && buff[1] == 0xd8 && buff[2] == 0xff 
        && ( buff[3] >= 0xe0 && buff[3] <= 0xef) )
        // if ( (buff[0] >= 0xffd8ffe0) && (buff[0] <= 0xffd8ffef) )
        {
            if (cur_jpg != NULL)
            {
                // close file with name jpgcount.txt
                fclose(cur_jpg);
            }
           
            // create new file. 
            jpg_count++;
               
    
            // ptr to title buffer:
            char title[8];
             
            // Have to do with ifs 
            if (jpg_count < 10)
            {
                sprintf(title, "00%d.jpg", jpg_count);  
            }
            else if (jpg_count > 9 && jpg_count < 100)
            {
                sprintf(title, "0%d.jpg", jpg_count);
            }
            else if (jpg_count > 99 && jpg_count < 1000)
            {
                sprintf(title, "%d.jpg", jpg_count);
            }
            else 
                return 1; 
                
            // opens that file for writing
            cur_jpg = fopen(title, "a"); // a is for append
        
            
        } // new file is now open and named - if no new file just write
        
        // Now need to write block
        if (cur_jpg != NULL)  // only starts writing after we hit first file
        {
            fwrite(buff, 1, 512, cur_jpg);
        } 
        
        
    }
    
    
    // This runs when there is less than 512 left in file: 
    if (cur_jpg != NULL) // just for safety - but if program good don't need. 
    {
        int left = fread( &buff, 1, 512, file );
        fwrite(buff, 1, left, cur_jpg);
        fclose(cur_jpg);
    }   
     
    fclose(file);
       
    return 0;  
    
} // Main
