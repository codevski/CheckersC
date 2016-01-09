/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1
 * Full Name        : Saso Petrovski
 * Student Number   : S3435996
 * Course Code      : COSC1076
 * Program Code     : B096
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "gameboard.h"

/* Copies the master board to a local copy for each game */
void init_gameboard(enum cell_contents board[][BOARDWIDTH])
{
    int i, j;
    for ( i = 0 ; i < BOARDWIDTH; i++)
    {
        for (j = 0; j < BOARDWIDTH; j++)
           {
               board[i][j] = master_board[i][j];
           }
    }
}

/* Prints the game board to the screen */
void display_gameboard(enum cell_contents board[][BOARDWIDTH])
{
    int i,j;
    
    printf("\n     |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |\n");

    for (i = 0; i < BOARDWIDTH; i++)
    {
        printf("------------------------------------------------------\n");
        printf("  %d  |", i);
        for (j = 0; j < BOARDWIDTH; j++)
        {
            printf("  ");
            
            switch( board[i][j] )
            {
                case EMPTY:
                    printf(" ");
                    break;
               
                case RED:
                    printf(RED_DISPLAY);
                    break;
                
                case WHITE:
                    printf(WHITE_DISPLAY);
                    break;

                case K_RED:
                    printf(RED_KING_DISPLAY);
                    break;
                
                case K_WHITE:
                    printf(WHITE_KING_DISPLAY);
                    break;

            }
            printf("  %s|", WHITE_RESET);
        }
        printf("\n");
    }
    printf("\n\n");
}
