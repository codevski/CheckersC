/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1
 * Full Name        : Saso Petrovski
 * Student Number   : S3435996
 * Course Code      : COSC1076
 * Program Code     : B096
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "game.h"
#include <time.h>
#include <string.h>
#include "utility.h"

/* Requirement 7 - Controls the flow of play in the game*/
void play_game(char * player_one, char * player_two,
    struct result * outcome)
{
    int number;
    char player1col[10], player2col[10];
   	int option = 0;
   	int has_moves = TRUE;
    struct player player1;
	struct player player2;

    enum cell_contents gameboard[BOARDWIDTH][BOARDHEIGHT];
    init_gameboard( gameboard );

    strcpy(player1.name, player_one);
    strcpy(player2.name, player_two);

	/* Receives a random number from the random_number function */
    if ((random_number(&number)) == 1)
    {
        player2.col = 0;
        player1.col = 1;
        strcpy(player1col, "White");
        strcpy(player2col, "Red");
    }
    else
    {
        player2.col = 1;
        player1.col = 0;
        strcpy(player1col, "Red");
        strcpy(player2col, "White");
    }

    printf("%s will be colour: %s\n", player1.name, player1col);
    printf("%s will be colour: %s\n", player2.name, player2col);
    
    display_gameboard( gameboard );
	
	/* Main flow of the game */
    do
    {
  		
        if (player1.col == P_RED && player2.col == P_WHITE)
        {
        	printf("It is %s's turn. Please enter a move"
        		 	"[press enter or ctrl-D to quit the current game]: ", player1.name);
	    	
	    	/* Decision to return back to menu */
	    	option = player_turn(&player1, gameboard);
	    	if (option == RTM)
	    	{
	    		break;
	    	}
	    	display_gameboard(gameboard);
	    	
	    	/* Checks if they are a winner */
			has_moves = test_for_winner(&player1, gameboard);
			if (has_moves == FALSE)
			{
				printf("name copy");
				strcpy(outcome->won, player_one);
				strcpy(outcome->lost, player_two);
				printf("Would you like to play again: ");
				
				break;
			}
			
			printf("It is %s's turn. Please enter a move"
		    		"[press enter or ctrl-D to quit the current game]: ", player2.name);
		    		
			option = player_turn(&player2, gameboard);
			if (option == RTM)
	    	{
	    		break;
	    	}

			display_gameboard( gameboard );

			has_moves = test_for_winner(&player2, gameboard);
			if (has_moves == FALSE)
			{
				printf("name copy");
				strcpy(outcome->won, player_two);
				strcpy(outcome->lost, player_one);
				break;
			}

		}
	    
        else
        {
        	printf("It is %s's turn. Please enter a move"
        	 "[press enter or ctrl-D to quit the current game]: ", player2.name);
        	 
	    	option = player_turn(&player2, gameboard);
	    	if (option == RTM)
	    	{
	    		break;
	    	}
	    	
			display_gameboard( gameboard );
			
			has_moves = test_for_winner(&player2, gameboard);
			if (has_moves == FALSE)
			{
				printf("name copy");
				strcpy(outcome->won, player_two);
				strcpy(outcome->lost, player_one);
				break;
			}

			printf("It is %s's turn. Please enter a move"
		    		"[press enter or ctrl-D to quit the current game]: ", player1.name);
					
			option = player_turn(&player1, gameboard);
			if (option == RTM)
	    	{
	    		break;
	    	}
	    	
			display_gameboard( gameboard );

			has_moves = test_for_winner(&player1, gameboard);
			if (has_moves == FALSE)
			{
				printf("name copy");
				strcpy(outcome->won, player_one);
				strcpy(outcome->lost, player_two);
				break;
			}
			
	    }
    } while (option == 1);
}

/* Requirement 5 - Handles the logic for the player's turn*/
enum str_result player_turn(struct player * current,
    enum cell_contents board[][BOARDWIDTH])
{
    enum move_type valid1;
    struct move move;
    char userinput[MOVE_LEN];
    int val1, val2, val3, val4, player_move_x, player_move_y;
    const char delim[] = ",-,";
    char *token;
    int finished = FALSE;
    char ctrlD;
    int anotherAttack = FALSE;
    

    /*enum colour col = current->col;*/
    
	do
	{
		/* User can use CtrlD or enter to exit game */
		do
		{
			fgets(userinput, MOVE_LEN + 1, stdin);
			
			if (strcmp(userinput, "\n\0") == 0 || (ctrlD = strchr(userinput, '\n') == NULL))
			{
				return RTM;
			}
			else
			{
				finished = TRUE;
			}
		} while (finished == FALSE);
    	
    	/* Going through token to assign numbers to var's */
    	token = strtok(userinput, delim);
    	
    	while (token != NULL)
    	{
    		val1 = atoi(token);
       		token = strtok(NULL, delim);
       		val2 = atoi(token);
 	   		token = strtok(NULL, delim);
 	   		val3 = atoi(token);
 	   		token = strtok(NULL, delim);
 	   		val4 = atoi(token);
 	   		token = strtok(NULL, delim);
    	}
    	
    	
    	move.start.x = val1;
    	move.start.y = val2;
    	move.end.x = val3;
    	move.end.y = val4;
    	
    	/* Checking if second attack is the same token - Help from mentors */
		if (anotherAttack == TRUE && player_move_x != move.start.x && player_move_y != move.start.y)
		{
			valid1 = INVALID;
		}
		else
		{
			valid1 = is_valid_move(move, current, board);
		}
		
		if (valid1 == INVALID)
		{
			printf("Your move is invalid please try again: ");
		}
		else if (valid1 == ATTACK)
		{
			display_gameboard( board );
			player_move_x = move.end.x;
			player_move_y = move.end.y;
			
			printf("You attacked! Would you like to attempt a further attack move with this token?"
					"[y for yes, n for no or press enter or ctrl-D to quit the current game]: ");
			
			fgets(userinput, 3, stdin);
			if (strcmp(userinput, "n\n\0") == 0 || strcmp(userinput, "N\n\0") == 0)
			{
				printf("breaking");
				return SUCCESS;
			}
			else
			{
				printf("Please enter your next move: ");
				anotherAttack = TRUE;
				continue;
			}
				
		}
	}while (valid1 == INVALID || valid1 == ATTACK);
    return SUCCESS;
}

/* Requirement 4 - Tests to see whether a move is valid or not*/
enum move_type is_valid_move(struct move next_move,
    struct player * current, enum cell_contents board[][BOARDWIDTH])
{
    /* Delete this comment and write your own comments and code here*/
    struct player;
    enum colour col = current->col;
    if (col == P_RED && next_move.end.x != 0)
    {
        /* Red Player and going forward*/
        if (board[next_move.start.x][next_move.start.y] == RED && 
        	next_move.start.x < next_move.end.x && next_move.end.x > next_move.start.x)
    	{
            /* going forward by 1 and is valid move */
            if ((next_move.end.x - next_move.start.x) == 1 && next_move.start.y != next_move.end.y &&
            	((next_move.start.y - next_move.end.y == 1) || (next_move.end.y - next_move.start.y == 1)) && 
            	board[next_move.end.x][next_move.end.y] == EMPTY)
            {
                /* Normal Move to King */
                if (next_move.end.x == 7)
                {
                	board[next_move.start.x][next_move.start.y] = EMPTY;
                	board[next_move.end.x][next_move.end.y] = K_RED;
		            return NORMAL;
                }
                else
                {
		            board[next_move.start.x][next_move.start.y] = EMPTY;
		            board[next_move.end.x][next_move.end.y] = RED;
		            return NORMAL;
		        }
            }
            /* Normal Red going forward by 2 and is valid move */
            else if ((next_move.end.x - next_move.start.x) == 2 && next_move.start.y != next_move.end.y && 
            		board[next_move.end.x][next_move.end.y] == EMPTY)
            {
            	/* checking attack make sure if its moving to Y=0 colume to ignore it */
            	if (next_move.start.y != next_move.end.y && next_move.end.y != 0 && 
            	(board[next_move.end.x -1][next_move.end.y +1] == WHITE || board[next_move.end.x -1][next_move.end.y +1] == K_WHITE ||
            	board[next_move.end.x -1][next_move.end.y -1] == WHITE || board[next_move.end.x -1][next_move.end.y -1] == K_WHITE))
            	{
		        	if ((board[next_move.end.x -1][next_move.end.y +1] == WHITE || board[next_move.end.x -1][next_move.end.y +1] == K_WHITE) && 
		        		(board[next_move.start.x +1][next_move.start.y -1] == WHITE || board[next_move.start.x +1][next_move.start.y -1] == K_WHITE) && 
		        		(next_move.start.y - next_move.end.y) == 2)
		            {
		            	board[next_move.end.x -1][next_move.end.y +1] = EMPTY;
		            	board[next_move.start.x][next_move.start.y] = EMPTY;
		            	
		            	if (next_move.end.x == 7)
		            	{
		            		board[next_move.end.x][next_move.end.y] = K_RED;
		            		return ATTACK;
		            	}
		            	else
		            	{
		            		board[next_move.end.x][next_move.end.y] = RED;
		            		return ATTACK;
		            	}
		            }
					else if ((board[next_move.end.x - 1][next_move.end.y - 1] == WHITE || board[next_move.end.x - 1][next_move.end.y - 1] == K_WHITE) &&
							(board[next_move.start.x + 1][next_move.start.y + 1] == WHITE || board[next_move.start.x + 1][next_move.start.y + 1] == K_WHITE) &&
							(next_move.end.y - next_move.start.y) == 2)
		            {
		            	board[next_move.end.x -1][next_move.end.y -1] = EMPTY;
		            	board[next_move.start.x][next_move.start.y] = EMPTY;
		            	
		            	if (next_move.end.x == 7)
		            	{
		            		board[next_move.end.x][next_move.end.y] = K_RED;
		            	}
		            	else
		            	{
		            		board[next_move.end.x][next_move.end.y] = RED;
		            	}
		            	return ATTACK;
		            }         		
            	}
            	/* Catch Y=0 here to know that its the edge of the board */
            	else if (next_move.end.y == 0)
            	{
		           	board[next_move.end.x -1][next_move.end.y +1] = EMPTY;
		           	board[next_move.start.x][next_move.start.y] = EMPTY;
		           	board[next_move.end.x][next_move.end.y] = RED;
		           	return ATTACK;
		        }
            }   
        }
        /* Its a King going back or forward */
        else if (board[next_move.start.x][next_move.start.y] == K_RED  &&
           		next_move.start.x != next_move.end.x && next_move.start.y != next_move.end.y)
        {
           	/* Going 1 step */
           	if (((next_move.end.x - next_move.start.x) == 1 || (next_move.start.x - next_move.end.x) == 1) && 
           		((next_move.start.y - next_move.end.y) == 1 || (next_move.end.y - next_move.start.y) == 1) && 
           		board[next_move.end.x][next_move.end.y] == EMPTY)
           	{
           		board[next_move.start.x][next_move.start.y] = EMPTY;
               	board[next_move.end.x][next_move.end.y] = K_RED;
		        return NORMAL;
           	}
           	/* Going 2 step */
           	else if (((next_move.end.x - next_move.start.x) == 2 || (next_move.start.x - next_move.end.x) == 2) &&
           			((next_move.start.y - next_move.end.y) == 2 || (next_move.end.y - next_move.start.y) == 2) &&
           			next_move.end.y != next_move.start.y && board[next_move.end.x][next_move.end.y] == EMPTY)
           	{
           		if (((next_move.end.y != 0 && board[next_move.end.x -1][next_move.end.y -1] == WHITE) || 
           			(next_move.end.y != 0 && board[next_move.end.x -1][next_move.end.y -1] == K_WHITE) ||
           			(next_move.end.y != 0 && board[next_move.end.x +1][next_move.end.y +1] == WHITE) ||
           			(next_move.end.y != 0 && board[next_move.end.x +1][next_move.end.y +1] == K_WHITE)) ||
           			board[next_move.end.x -1][next_move.end.y +1] == WHITE || board[next_move.end.x -1][next_move.end.y +1] == K_WHITE ||
           			board[next_move.end.x +1][next_move.end.y -1] == WHITE || board[next_move.end.x +1][next_move.end.y -1] == K_WHITE ||
           			board[next_move.end.x +1][next_move.end.y +1] == WHITE || board[next_move.end.x +1][next_move.end.y +1] == K_WHITE)
           		{
					if ((board[next_move.end.x - 1][next_move.end.y - 1] == WHITE || board[next_move.end.x - 1][next_move.end.y - 1] == K_WHITE) &&
						(board[next_move.start.x + 1][next_move.end.y + 1] == WHITE || board[next_move.start.x + 1][next_move.end.y + 1] == K_WHITE))
           			{
		           		board[next_move.end.x -1][next_move.end.y -1] = EMPTY;
		           		board[next_move.start.x][next_move.start.y] = EMPTY;
		           		board[next_move.end.x][next_move.end.y] = K_RED;
		           		return ATTACK;
		           	}
					else if ((board[next_move.end.x - 1][next_move.end.y + 1] == WHITE || board[next_move.end.x - 1][next_move.end.y + 1] == K_WHITE) &&
								(board[next_move.start.x + 1][next_move.end.y - 1] == WHITE || board[next_move.start.x + 1][next_move.end.y - 1] == K_WHITE))
		           	{
		           		board[next_move.end.x -1][next_move.end.y +1] = EMPTY;
		           		board[next_move.start.x][next_move.start.y] = EMPTY;
		           		board[next_move.end.x][next_move.end.y] = K_RED;
		           		return ATTACK;
		           	}
					else if ((board[next_move.end.x +1][next_move.end.y -1] == WHITE || board[next_move.end.x +1][next_move.end.y -1] == K_WHITE) && 
							(board[next_move.start.x -1][next_move.end.y +1] == WHITE || board[next_move.start.x -1][next_move.end.y +1] == K_WHITE))
		           	{
		           		board[next_move.end.x +1][next_move.end.y -1] = EMPTY;
		           		board[next_move.start.x][next_move.start.y] = EMPTY;
		           		board[next_move.end.x][next_move.end.y] = K_RED;
		           		return ATTACK;
		           	}
					else if ((board[next_move.end.x + 1][next_move.end.y + 1] == WHITE || board[next_move.end.x + 1][next_move.end.y + 1] == K_WHITE) &&
								(board[next_move.start.x - 1][next_move.start.y - 1] == WHITE || board[next_move.start.x - 1][next_move.start.y - 1] == K_WHITE))
		           	{
		           		board[next_move.end.x +1][next_move.end.y +1] = EMPTY;
		           		board[next_move.start.x][next_move.start.y] = EMPTY;
		           		board[next_move.end.x][next_move.end.y] = K_RED;
		           		return ATTACK;
		           	}
		           	
           		}
           		else if (next_move.end.y == 0)
           		{
					if (board[next_move.end.x + 1][next_move.end.y + 1] == WHITE || board[next_move.end.x + 1][next_move.end.y + 1] == K_WHITE)
           			{
		           		board[next_move.end.x +1][next_move.end.y +1] = EMPTY;
		           		board[next_move.start.x][next_move.start.y] = EMPTY;
		           		board[next_move.end.x][next_move.end.y] = K_RED;
		           		return ATTACK;
		           	}
		           	else
		           	{
		           		board[next_move.end.x -1][next_move.end.y +1] = EMPTY;
		           		board[next_move.start.x][next_move.start.y] = EMPTY;
		           		board[next_move.end.x][next_move.end.y] = K_RED;
		           		return ATTACK;
		           	}
		        }
           	}
        }
    }
    /* If White Player */
    else
    {
    	/* White Player and going forward*/
    	if (board[next_move.start.x][next_move.start.y] == WHITE && next_move.start.x > next_move.end.x && 
    		next_move.end.x < next_move.start.x)
    	{
    		if ((next_move.start.x - next_move.end.x) == 1 && next_move.start.y != next_move.end.y && 
    			((next_move.start.y - next_move.end.y == 1) || (next_move.end.y - next_move.start.y == 1)) && 
    			board[next_move.end.x][next_move.end.y] == EMPTY)
    		{
    			if (next_move.end.x == 0)
                {
                	board[next_move.start.x][next_move.start.y] = EMPTY;
                	board[next_move.end.x][next_move.end.y] = K_WHITE;
		            return NORMAL;
                }
                else
                {
		            board[next_move.start.x][next_move.start.y] = EMPTY;
		            board[next_move.end.x][next_move.end.y] = WHITE;
		            return NORMAL;
		        }
    		}
    		/* Going forward by 2 and is valid move */
    		else if ((next_move.start.x - next_move.end.x) == 2 && next_move.start.y != next_move.end.y && 
    					board[next_move.end.x][next_move.end.y] == EMPTY)
    		{
    			/* checking attack make sure if its moving to Y=0 colume to ignore it */
    			if (next_move.start.y != next_move.end.y && next_move.end.y != 0 && 
					((board[next_move.end.x + 1][next_move.end.y - 1] == RED || board[next_move.end.x + 1][next_move.end.y - 1] == K_RED) ||
					(board[next_move.end.x + 1][next_move.end.y + 1] == RED || board[next_move.end.x + 1][next_move.end.y + 1] == K_RED)))
    			{
					if ((board[next_move.end.x + 1][next_move.end.y + 1] == RED || board[next_move.end.x + 1][next_move.end.y + 1] == K_RED) &&
						(	board[next_move.start.x - 1][next_move.start.y - 1] == RED || board[next_move.start.x - 1][next_move.start.y - 1] == K_RED) &&
						(next_move.start.y - next_move.end.y) == 2)
					{
				        board[next_move.end.x +1][next_move.end.y +1] = EMPTY;
				        board[next_move.start.x][next_move.start.y] = EMPTY;
				        if (next_move.end.x == 0)
				        {
				        	board[next_move.end.x][next_move.end.y] = K_WHITE;
				        }
				        else
				        {
				        	board[next_move.end.x][next_move.end.y] = WHITE;
				        }
				        return ATTACK;
				    }
					else if ((board[next_move.end.x + 1][next_move.end.y - 1] == RED || board[next_move.end.x + 1][next_move.end.y - 1] == K_RED) &&
							(board[next_move.start.x - 1][next_move.start.y + 1] == RED || board[next_move.start.x - 1][next_move.start.y + 1] == K_RED) &&
				    		(next_move.end.y - next_move.start.y) == 2)
				    {
				        board[next_move.end.x +1][next_move.end.y -1] = EMPTY;
				        board[next_move.start.x][next_move.start.y] = EMPTY;
				        if (next_move.end.x == 0)
				        {
				        	board[next_move.end.x][next_move.end.y] = K_WHITE;
				        }
				        else
				        {
				        	board[next_move.end.x][next_move.end.y] = WHITE;
				        }
				        return ATTACK;
				    }
		        }
		        /* Catch Y=0 here to know that its the edge of the board */
		        else if (next_move.end.y == 0)
		        {
				    board[next_move.end.x +1][next_move.end.y +1] = EMPTY;
				    board[next_move.start.x][next_move.start.y] = EMPTY;
				    board[next_move.end.x][next_move.end.y] = WHITE;
				    return ATTACK;
				}
    		}
    	}
    	/* Its a King going back or forward */
    	else if ((board[next_move.start.x][next_move.start.y] == K_WHITE || board[next_move.start.x][next_move.start.y] == K_WHITE) &&
    			next_move.start.x != next_move.end.x && next_move.start.y != next_move.end.y)
    	{
    		/* Going 1 step */
    		if (((next_move.end.x - next_move.start.x) == 1 || (next_move.start.x - next_move.end.x) == 1) &&
    			((next_move.start.y - next_move.end.y) == 1 || (next_move.end.y - next_move.start.y) == 1) &&
	       		((next_move.start.y - next_move.end.y) == 1 || (next_move.end.y - next_move.start.y) == 1) && 
           		next_move.end.y != next_move.start.y && board[next_move.end.x][next_move.end.y] == EMPTY)
           	{
           		board[next_move.start.x][next_move.start.y] = EMPTY;
               	board[next_move.end.x][next_move.end.y] = K_WHITE;
		        return NORMAL;
           	}
           	/* Going 2 step */
           	else if (((next_move.end.x - next_move.start.x) == 2 || (next_move.start.x - next_move.end.x) == 2) &&
           			((next_move.start.y - next_move.end.y) == 2 || (next_move.end.y - next_move.start.y) == 2) &&
           			next_move.end.y != next_move.start.y && board[next_move.end.x][next_move.end.y] == EMPTY)
           	{
				if (next_move.end.y != 0 && (board[next_move.end.x - 1][next_move.end.y - 1] == RED || board[next_move.end.x - 1][next_move.end.y - 1] == K_RED || 
					board[next_move.end.x - 1][next_move.end.y + 1] == RED || board[next_move.end.x - 1][next_move.end.y + 1] == K_RED || 
					board[next_move.end.x + 1][next_move.end.y - 1] == RED || board[next_move.end.x + 1][next_move.end.y - 1] == K_RED || 
					board[next_move.end.x + 1][next_move.end.y + 1] == RED || board[next_move.end.x + 1][next_move.end.y + 1] == K_RED))
           		{
					if ((board[next_move.end.x - 1][next_move.end.y - 1] == RED || board[next_move.end.x - 1][next_move.end.y - 1] == K_RED) &&
							(board[next_move.start.x + 1][next_move.start.y + 1] == RED || board[next_move.start.x + 1][next_move.start.y + 1] == K_RED))
           			{
		           		board[next_move.end.x -1][next_move.end.y -1] = EMPTY;
		           		board[next_move.start.x][next_move.start.y] = EMPTY;
		           		board[next_move.end.x][next_move.end.y] = K_WHITE;
		           		return ATTACK;
		           	}
					else if ((board[next_move.end.x - 1][next_move.end.y + 1] == RED || board[next_move.end.x - 1][next_move.end.y + 1] == K_RED) &&
								(board[next_move.start.x + 1][next_move.start.y - 1] == RED || board[next_move.start.x + 1][next_move.start.y - 1] == K_RED))
		           	{
		           		board[next_move.end.x -1][next_move.end.y +1] = EMPTY;
		           		board[next_move.start.x][next_move.start.y] = EMPTY;
		           		board[next_move.end.x][next_move.end.y] = K_WHITE;
		           		return ATTACK;
		           	}
					else if ((board[next_move.end.x + 1][next_move.end.y - 1] == RED || board[next_move.end.x + 1][next_move.end.y - 1] == K_RED) &&
								(board[next_move.start.x - 1][next_move.start.y + 1] == RED || board[next_move.start.x - 1][next_move.start.y + 1] == K_RED))
		           	{
		           		board[next_move.end.x +1][next_move.end.y -1] = EMPTY;
		           		board[next_move.start.x][next_move.start.y] = EMPTY;
		           		board[next_move.end.x][next_move.end.y] = K_WHITE;
		           		return ATTACK;
		           	}
					else if ((board[next_move.end.x + 1][next_move.end.y + 1] == RED || board[next_move.end.x + 1][next_move.end.y + 1] == K_RED) &&
								(board[next_move.start.x - 1][next_move.start.y - 1] == RED || board[next_move.start.x - 1][next_move.start.y - 1] == K_RED))
		           	{
		           		board[next_move.end.x +1][next_move.end.y +1] = EMPTY;
		           		board[next_move.start.x][next_move.start.y] = EMPTY;
		           		board[next_move.end.x][next_move.end.y] = K_WHITE;
		           		return ATTACK;
		           	}
           		}
           	}
    	}
    }

    return INVALID;
}

/* Requirement  - Tests whether the next player has any valid moves */
BOOLEAN test_for_winner(struct player * next_player,
    enum cell_contents board[][BOARDWIDTH])
{
    BOOLEAN has_moves = TRUE;
    int i,j;
    enum colour col = next_player->col;
    
    printf("TESTF-");
    for (i = 0; i < BOARDHEIGHT; i++)
    {
    	for (j = 0; j < BOARDWIDTH; j++)
    	{
    		if (col == 0)
    		{
				if (board[i][j] == WHITE || board[i][j] == K_WHITE)
				{
					/* Checking the board for k_white and white checkers and to see if they have valid moves */
					if ((board[i][j] == WHITE && ((board[i-1][j+1] == EMPTY || board[i-1][j-1] == EMPTY) ||
						(board[i-2][j+2] == EMPTY || board[i-2][j-2]))) || 
						((board[i][j] == K_WHITE && ((board[i+1][j+1] == EMPTY || board[i+1][j-1] == EMPTY) ||
						board[i-1][j+1] == EMPTY || board[i-1][j-1] == EMPTY ||
						board[i+2][j+2] == EMPTY || board[i+2][j-2] == EMPTY || 
						board[i-2][j+2] == EMPTY || board[i-2][j-2] == EMPTY))))
					{
						printf("%d,%d", i, j);
						return has_moves;
					}
				}
			}
			else
			{
				if (board[i][j] == RED || board[i][j] == K_RED)
				{
					/* Checking the board for k_red and red checkers and to see if they have valid moves */
					if ((board[i][j] == RED && ((board[i + 1][j + 1] == EMPTY || board[i + 1][j - 1] == EMPTY) ||
						(board[i + 2][j + 2] == EMPTY || board[i + 2][j - 2]))) ||
						((board[i][j] == K_RED && ((board[i + 1][j + 1] == EMPTY || board[i + 1][j - 1] == EMPTY) ||
						board[i - 1][j + 1] == EMPTY || board[i - 1][j - 1] == EMPTY ||
						board[i + 2][j + 2] == EMPTY || board[i + 2][j - 2] == EMPTY ||
						board[i - 2][j + 2] == EMPTY || board[i - 2][j - 2] == EMPTY))))
					{
						return has_moves;
					}
				}
			}
    	}
    }
    return FALSE;
}
