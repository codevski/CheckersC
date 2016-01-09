 /***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1
 * Full Name        : Saso Petrovski
 * Student Number   : S3435996
 * Course Code      : COSC1076
 * Program Code     : B096
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "draughts.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define SIZE 10
#define TRUE 1
#define FALSE 0

/* Function to store player names */
void player_names(char * player1, char * player2)
{
    int finished = FALSE;
    int finished2 = FALSE;
    char tempString[SIZE + 2];
    
    do
    {
        printf("Player 1 Enter name (1-20 Characters): ");
        fgets(tempString, SIZE + 2, stdin);
        
        if (tempString[strlen(tempString) - 1] != '\n')
        {
            printf("Input was too long.\n");
            read_rest_of_line();
        }
        else
        {
            finished = TRUE;
        }
    } while (finished == FALSE);
    
    tempString[strlen(tempString) - 1] = '\0';
    
    strcpy(player1, tempString);
    
    do
    {
        printf("Player 2 Enter name (1-20 Characters): ");
        fgets(tempString, SIZE + 2, stdin);
        
        if (tempString[strlen(tempString) - 1] != '\n')
        {
            printf("Input was too long.\n");
            read_rest_of_line();
        }
        else
        {
            finished2 = TRUE;
        }
    } while (finished2 == FALSE);
    
    tempString[strlen(tempString) - 1] = '\0';
    
    strcpy(player2, tempString);
    
}

int main (int argc, char *argv[])
{
    struct result scoreboard[SCOREBOARDSIZE];
	struct result outcome;
	
    /*Menu*/
	int menuChoice;
	char player1[SIZE + 2];
	char player2[SIZE + 2];
    char* menuPrompt = "\nEnter choice [1-4]: ";
    
    do
    {
    	printf("English Draughts Main Menu\n");
		printf("~~~~~~~~~~~~~~~~~~~~\n");
		printf("1) Play Game\n");
		printf("2) Display Winners\n");
		printf("3) Rest scoreboard\n");
		printf("4) Quit\n");
		
		getInteger(&menuChoice, SWITCH + 1, menuPrompt, 1, 4);
		switch ( menuChoice )
		{
			case FIRST:
			{
				init_scoreboard(&outcome);
				player_names(player1, player2);
		        play_game(player1, player2, &outcome);
		        add_to_scoreboard(&outcome, scoreboard);
		        break;
		    }
		    case SECOND:
		    {
		        display_scoreboard(&outcome);
		        break;
		    }
		    case THIRD:
		    {
		    	printf("\nBoard has been reset!\n");
		        reset_scoreboard(&outcome);
		        break;
		    }
		    case FOURTH:
		    {
		    	printf("\nQuiting....\n");
		        break;
		    }
		    default:
		    {
		    	printf("Not Valid\n");
		    	break;
		    }
		}
	} while (menuChoice != 4);
    return EXIT_SUCCESS;
}


