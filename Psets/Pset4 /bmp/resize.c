/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *

 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4) // add 1 for n
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // checks the conditions given for n
    if ( n < 0 || n > 100)
    {
        printf( "n must be positive int less than 100 \n");     
        return 4; 
    }


    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }


    // Create the new bitmaps
    BITMAPFILEHEADER bf2; 
    BITMAPINFOHEADER bi2;
    bf2 = bf; 
    bi2 = bi; 
 
  
    // first determine the amount of padding for the new. 
    
    int padding2 =  (4 - (bi.biWidth * sizeof(RGBTRIPLE) * n) % 4) % 4;

   // Need to adjust fields in infoheader:
    
    bi2.biWidth = bi.biWidth * n; 
    bi2.biHeight = bi.biHeight * n; // Should remain negative since top-down
    
    // biSizeImage stores all the info minus the two headers
    bi2.biSizeImage = bi2.biWidth * bi2.biHeight + (padding2 * n);  
    
    // Need to adjust file size of File header
    // only want to mult pixels not header bytes
    // subtract old image and add in new calc.
    
    bf2.bfSize = ( bf.bfSize - bi.biSizeImage + bi2.biSizeImage ); 
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf2, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi2, sizeof(BITMAPINFOHEADER), 1, outptr);

    
    // determine padding for scanlines for INPUT
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE) ) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // write each row n times: 
        for (int jj = 0; jj < n; jj++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple n times to the row
                for (int ii = 0; ii < n; ii++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);   
                }
            }
            
            // skip over padding, if any --- of the original file
            fseek(inptr, padding, SEEK_CUR);
            
            // then add padding for the new file
            for (int k = 0; k < padding2; k++) 
            {
                fputc(0x00, outptr);
            }  // this is the end of a row
            
            if ( jj < (n - 1) )
            {   // need to move the scanline back to the orig line infile
                fseek(inptr, -(bi.biWidth * sizeof(RGBTRIPLE) + padding ), SEEK_CUR );
            }
        }
    
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
