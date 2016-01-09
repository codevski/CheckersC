/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1
 * Full Name        : Saso Petrovski
 * Student Number   : S3435996
 * Course Code      : COSC1076
 * Program Code     : B096
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/

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
