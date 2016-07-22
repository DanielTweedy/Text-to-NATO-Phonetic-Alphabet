/* File: StringToNPAlpha.c
 *
 * Author: Daniel "MelBrooksKA" Tweedy
 *
 * Description: Takes an input string and converts the individual printable
 *              characters to the NATO Phonetic Alphabet with the end of a
 *              converted character denoted with a '.'. Non-alphanumeric
 *              characters are printed directly to the screen.
 *
 *   Constants: ERROR_FREE
 *              ERROR_THROWN
 *              MAX_DICT
 *              DEFAULT_STRING_SIZE
 *              MEM_ALLOC_ERROR
 *              NUM_OFFSET
 *
 *  Language: C C99 ANSI Standard or Later
 * Libraries: stdio.h
 *            stdbool.h
 *            stdlib.h
 *            ctype.h
 *            string.h
 *            errno.h
 *            unistd.h
 *
 * Deficiencies: Options not yet implemented
 *               Edge cases not tested
 */

// Libraries
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

// Constants
#define ERROR_FREE 0
#define ERROR_THROWN 1
#define MAX_DICT 36
#define DEFAULT_STRING_SIZE 128
#define MEM_ALLOC_ERROR "Memory Allocation Error"
#define NUM_OFFSET 26

// Structures

// Prototypes
void toNatoPhonetic(char *);
void printUserFormat(char *);

// Global Variables
// Contains all the phonetic translations of the NATO Phonetic Alphabet for the alphanumeric characters
char *NPAlpha[MAX_DICT] = {"alpha", "bravo", "charlie", "delta", "echo", "foxtrot", "golf", "hotel", "india", "juliett", "kilo", "lima", "mike", "november", "oscar", "papa", "quebec", "romeo", "sierra", "tango", "uniform", "victor", "whiskey", "xray", "yankee", "zulu", "zero", "one", "two", "tree", "fower", "fife", "six", "seven", "eight", "niner"};

bool capital = false;


int main(int argc, char *argv[]) {
    size_t read = 0, length = 0; // contains the return value of getline
    char *inputLine = NULL, // input line from getline
         *manipulantLine = NULL; // String that will be a copy of the input line and will be manipulated

    manipulantLine = malloc(DEFAULT_STRING_SIZE);
    if(manipulantLine == NULL) {
        perror(MEM_ALLOC_ERROR);
        exit(ERROR_THROWN);
    }

    manipulantLine[0] = '\0';

    while((read = getline(&inputLine, &length, stdin)) != EOF) {
        if(strlen(manipulantLine) < length) {
            manipulantLine = realloc(manipulantLine, length);

            if(manipulantLine == NULL) {
                perror(MEM_ALLOC_ERROR);
                exit(ERROR_THROWN);
            }
        }

        strcpy(manipulantLine, inputLine);
        toNatoPhonetic(manipulantLine);
    }

    free(manipulantLine);
    free(inputLine);

    return ERROR_FREE;
}

/* toNatoPhonetic(char *)
 * Converts the individal alphanumeric characters to their NATO Phonetic
 * counterparts.
 */
void toNatoPhonetic(char *inString) {
    char *traveler = NULL; // String used to travel along the input stirng 
    char normalizer; // used for calulating the input character's place in the NPAlpha

    for(traveler = inString; *traveler != '\0'; traveler++) {
        if(isalnum(*traveler)) {
            if(isdigit(*traveler)) {
                normalizer = '0' - NUM_OFFSET; // Numbers are after the letters in the npa array
            } else if(isupper(*traveler)) {
                normalizer = 'A';
            } else {
                normalizer = 'a';
            }

            // printf("%s.", NPAlpha[*traveler - normalizer]);
            printUserFormat(NPAlpha[*traveler - normalizer]);
        } else {
            printf("%c", *traveler);
        }
    }
}

/* printUserFormat(char *)
 * Takes user information from command-line flags and prints out Nato conversion
 * based on what flags the user has specified. Program takes a Nato character
 * string and prints it out based on the command-line flags.
 * Function assumes that the input is a Nato string.
 */
void printUserFormat(char *natoString) {
   printf("%s.", natoString); 
}
