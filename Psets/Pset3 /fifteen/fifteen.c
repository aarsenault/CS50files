/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

void swap(int title_pos, int zero_pos);


int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("\33[05;44m YOU WON] \n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(20000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // Initialize array to hold values before board is construct.
   
   // Populates the game board
    for ( int i = 0; i < d * d; i++)
    {   
        // fills the places in memory
        *( (int*) board + i) = d * d - i - 1;

    }
    
    // make the place holder
    int swap;
    
    // condition for d being even
    if ( d % 2 == 0)
    {
        // should hold value 2
        swap = *( (int*) board + (d * d - 3) );
        // should now take value 1
        *( (int*) board + (d * d - 3) ) = *( (int*) board + (d * d - 2) );
        
        // should now take value 2 from swap
        *( (int*) board + (d * d - 2) ) = swap; 
    }
    
    
   
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    printf( "\n \n \n");
    
    for ( int i = 0; i < d * d; i++ )
    {
        if ( *( (int *) board + i) >= 10) 
        {
            printf( "%i  " , *( (int *) board + i) );
        }
        else
        {
            printf( "%i   " , *( (int *) board + i) );
        }        
            
        if ( ( (i % d) == (d - 1)) && ( i != 0 ) )
        {
            printf("\n");
        }
    }
    
    printf( "\n \n \n");
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // Checks pos. of letter
    int tile_pos = -1;
    int zero_pos = -1;
    
    for (int i = 0; i < (d * d); i++)
    {
        if (tile == *( (int*) (*board + i) ) )
        {
            tile_pos = i; 
        }
        
        // Cheks pos. of zero
        if ( 0 ==  *( (int*) (*board + i) ) )
        {
            zero_pos = i; 
        }
    }
    
    // Checks the movability conditions
    if ( (zero_pos % d) == (tile_pos % d) )
    {
        swap(tile_pos, zero_pos);
        return true;
    }
    else if ( tile_pos == (zero_pos + 1))
    {
        swap(tile_pos, zero_pos);
        return true;
    }
    else if (tile_pos == (zero_pos - 1) )
    {
        swap(tile_pos, zero_pos);
        return true;
    }
    
    return false;
}



void swap(int pos1, int pos2)
{
    
    // should hold value of pos 1.
    int tmpswap = *( (int*) board + (pos1) );
    
    // pos1 should now take value from pos 2
    *( (int*) board + (pos1) ) = *( (int*) board + (pos2) );
    
    // should now take value 2 from swap
    *( (int*) board + (pos2) ) = tmpswap; 
        
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */

bool won(void)
{
    int true_counter = 0;
    for (int i = 0; i < d * d - 1; i++)
    {
        if ( *( (int*) board + (i) ) == (i + 1) )
        {
            true_counter++;
        }
    }
    
    if (true_counter == (d * d - 1) )
    {
        return true; 
    }
    
    return false;
}