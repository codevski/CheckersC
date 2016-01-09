/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1
 * Full Name        : Saso Petrovski
 * Student Number   : S3435996
 * Course Code      : COSC1076
 * Program Code     : B096
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/

#include "scoreboard.h"
#include <string.h>

/* Req 2 -Initialises the scoreboard and sets all the strings to be 
 * empty*/
void init_scoreboard(struct result * scoreboard)
{
    reset_scoreboard(scoreboard);
}

/* Req 9 -Adds a result to the beginning of the scoreboard*/
void add_to_scoreboard(struct result * scoreboard, 
    struct result * latest_game)
{
    int i;
    for (i = SCOREBOARDSIZE; i >= 0; i--)
    {
    	strcpy(scoreboard[i+1].won, scoreboard[i].won);
    	strcpy(scoreboard[i+1].lost, scoreboard[i].lost);
    }
    
    /* Suport from mentors, Allows the latest game to be on top */
    strcpy(scoreboard[0].won, latest_game->won);
    strcpy(scoreboard[0].lost, latest_game->lost);
}

/* Req 11 - Initialises the scoreboard and sets all the strings to be 
 * empty*/
void reset_scoreboard(struct result * scoreboard)
{
    int i;
    for(i = 0; i <= SCOREBOARDSIZE; i++)
    {
    	strcpy(scoreboard->won, "");
    	strcpy(scoreboard->lost, "");
    	
    	scoreboard++;
    }
}

/* Req 10 - Displays a formatted printout of the last 10 winners and 
 * losers*/
void display_scoreboard(struct result * scoreboard)
{
    int i;
    printf("APT English Draughts Tournament - History of Games Played.\n");
    printf("===========================================================\n");
    printf("| Winner                    | Loser                       |\n");
    printf("| ------------------------- | --------------------------- |\n");
    
    for(i = 0; i < SCOREBOARDSIZE; i++)
    {
    	printf("| %-25s | %-27s |\n", scoreboard[i].won, scoreboard[i].lost);
    }
}

