#include "utility.h"
#include <time.h>
#include <string.h>


/* Tidy up residual data in stdin when encountering an error. You will
 * need to use this when there is a possibility that there will be
 * leftover characters in the input buffer. */
void read_rest_of_line(void)
{
    int ch;
    /* remove all characters from the buffer */
    while(ch = getc(stdin), ch!='\n' && ch!=EOF)
        ;
    /* clear the error status of the input pointer */
    clearerr(stdin);
}

/* Function written by Steven Burrows - Validates the menu to only use numbers and values between 1-4 */
int getInteger(int* integer, unsigned length, char* prompt, int min, int max)
{
	int finished = FALSE;
	char tempString[SWITCH + 2];
	int tempInteger = 0;
	char* endPtr;
	
	do
	{
		printf("%s", prompt);
		
		fgets(tempString, length + 2, stdin);
		
		if (tempString[strlen(tempString) - 1] != '\n')
		{
			printf("Input was too long.\n");
		}
		else
		{
			tempString[strlen(tempString) - 1] = '\0';
			tempInteger = (int) strtol(tempString, &endPtr, 10);
			
			if (strcmp(endPtr, "") != 0)
			{
				printf("Input was not numeric.\n");
			}
			else if (tempInteger < min || tempInteger > max)
			{
				printf("Input was not within range %d - %d.\n", min, max);
			}
			else
			{
				finished = TRUE;
			}
		}
	} while (finished == FALSE);
	
	*integer = tempInteger;
	return TRUE;
}

/* Generates a random number to assign white or red player - Based off http://www.tutorialspoint.com/c_standard_library/c_function_srand.htm */
int random_number()
{
    int r;
    time_t t;
    srand((unsigned) time(&t));
    r = rand() % 2;
    
    return r;
}
