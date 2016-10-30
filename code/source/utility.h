#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LEN 20
#define SWITCH 1
#define INPUT 3

typedef enum
{
    FALSE, TRUE
} BOOLEAN;

/*Clears residual data from stdin*/
void read_rest_of_line(void);

int getInteger(int* integer, unsigned length, char* prompt, int min, int max);

int random_number();

#endif
