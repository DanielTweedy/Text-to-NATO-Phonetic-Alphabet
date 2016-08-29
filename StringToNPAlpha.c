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
 * Deficiencies: Other military dictionaries have yet to be implemented.
 *
 */

// Libraries
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>

// Constants
#define ERROR_FREE 0
#define ERROR_THROWN 1
#define MAX_DICT 36
#define DEFAULT_STRING_SIZE 128
#define MEM_ALLOC_ERROR "Memory Allocation Error"
#define NUM_OFFSET 26
#define UPPER_SHORT "upper"
#define UPPER_LONG "all-uppercase"
#define LOWER_SHORT "lower"
#define LOWER_LONG "all-lowercase"
#define FIRST_SHORT "first"
#define FIRST_LONG "first-capital"
#define FOLLOW_SHORT "follow"
#define FOLLOW_LONG "follow-input"

// Structures
/* Used to determine the format of the individual characters
 * All lower case (default), all upper case, first character in the alphabetic
 * string is upper case and followed by lower, or case follows the case of the input
 * character
 */
typedef enum {LOWER, CAPS, FIRST, FOLLOW} AlphaFormat;

/* Used to determine the Phonetic alphabet the user wants text to be converted to.
 * NATO Phonetic Alphabet (NPA), WW1 British Royal Navy (RN) Phonetic Alphabet, WW1
 * Informal Phonetic Alphabet, 1924-1942 British Royal Airforce (RAF) Phonetic
 * Alphabet, 1943-1956 RAF Phonetic Alphabet, 1941-1956 US Phonetic Alphabet,
 * User Supplied Alphabet.
 * Program defaults to NPA
 */
typedef enum {NPA, WW1RN, WW1INF, RAF24, RAF43, USPA, USER} AlphaType;

// Prototypes
void toNatoPhonetic(char *);
void printUserFormat(char *, bool, AlphaFormat);
void takeInputLine();
char *stringToUpper(char *);
char *stringToFirst(char *);
void setFollowFormat(char *);
void setNumberFormat(char *);
void setAlphabet(char *);

// Global Variables
// Contains all the phonetic translations of the NATO Phonetic Alphabet for the alphanumeric characters
char *Alphabet[MAX_DICT]; 

char *NPAlpha[MAX_DICT] = {
    "alpha", "bravo", "charlie", "delta", "echo", "foxtrot", "golf", "hotel",
    "india", "juliett", "kilo", "lima", "mike", "november", "oscar", "papa",
    "quebec", "romeo", "sierra", "tango", "uniform", "victor", "whiskey", "x-ray",
    "yankee", "zulu", "zero", "one", "two", "tree", "fower", "fife", "six",
    "seven", "eight", "niner"
};

// Universal format of the characters, lowercase by default
AlphaFormat universalFormat = LOWER;
// Format of the character if program defines the universal format as "follow",
// defaults to "first" and can only be "first" or "caps"
AlphaFormat followFormat = FIRST;
// Format of numbers, defaults to the universal format
AlphaFormat numberFormat = LOWER;
bool numSet = false; // tells if the numberFormat has been set

bool isDefaultAlpha = true; // used to determine if a user alphabet is being input

// Usage for the program
char *usage = "Usage: StringToNPAlpha [OPTION]...";

int main(int argc, char *argv[]) {
    int opt; // Return value from getopt_lonn
    // structure used for getopt_long
    static struct option long_options[] = {
        {"all-uppercase",       no_argument, NULL, 'A'},
        {"all-lowercase",       no_argument, NULL, 'L'},
        {"first-capital",       no_argument, NULL, 'F'},
        {"follow-input",  optional_argument, NULL, 'f'},
        {"number-format", optional_argument, NULL, 'n'},
        {"alphabet",      required_argument, NULL, 'a'}
    };

    while((opt = getopt_long(argc, argv, "ALFf::n::a:", long_options, NULL)) != EOF) {
        switch(opt) {
            case 'A': universalFormat = CAPS;
                break;
            case 'L': universalFormat = LOWER;
                break;
            case 'F': universalFormat = FIRST;
                break;
            case 'f': setFollowFormat(optarg);
                break;
            case 'n': setNumberFormat(optarg);
                break;
            case 'a': setAlphabet(optarg);
                break;
            default: printf("%s\n", usage);
                exit(ERROR_THROWN);
                break;
        }
    }

    if(isDefaultAlpha) {
        int i;
        for(i = 0; i < MAX_DICT; i++) {
            Alphabet[i] = NPAlpha[i];
        }
    }

    takeInputLine();

    return ERROR_FREE;
}

/* setFollowFormat(char *)
 * Function that takes arugments for "follow" option and sets variables that
 * change the behavior of the program.
 * Assumes that input argument can be NULL or invalid
 */
void setFollowFormat(char *optarg) {
    universalFormat = FOLLOW;
    if(optarg == NULL) {
        followFormat = FIRST;
    } else {
        if(strcmp(optarg, UPPER_SHORT) == 0 || strcmp(optarg, UPPER_LONG) == 0) {
            followFormat = CAPS;
        } else if(strcmp(optarg, FIRST_SHORT) == 0 || strcmp(optarg, FIRST_LONG) == 0) {
            followFormat = FIRST;
        } else {
            fprintf(stderr, "Error: %s is not a valid Follow format\n", optarg);
            exit(ERROR_THROWN);
        }
    }
}

/* setNumberFormat(char *)
 * Takes arguments for number formats and sets variables that change the
 * behavior of the program.
 * Function assumes that input can be NULL or invalid.
 */
void setNumberFormat(char *optarg) {
    if(optarg == NULL) {
        if(universalFormat == FOLLOW) {
            numberFormat = followFormat;
        } else {
            numberFormat = universalFormat;
        }
    } else {
        if(strcmp(optarg, UPPER_SHORT) == 0 || strcmp(optarg, UPPER_LONG) == 0) {
            numberFormat = CAPS;
        } else if(strcmp(optarg, LOWER_SHORT) == 0 || strcmp(optarg, LOWER_LONG) == 0) {
            numberFormat = LOWER;
        } else if(strcmp(optarg, FIRST_SHORT) == 0 || strcmp(optarg, FIRST_LONG) == 0) {
            numberFormat = FIRST;
        } else if(strcmp(optarg, FOLLOW_SHORT) == 0 || strcmp(optarg, FOLLOW_LONG)) {
            numberFormat = universalFormat;
        } else {
            fprintf(stderr, "Error: %s is not a valid Number format\n", optarg);
            exit(ERROR_THROWN);
        }
    }

    numSet = true;
}

/* takeInputLine()
 * Gateway function to starting the conversion to the NPA.
 * Assumes default behavior of the program has been choosen
 */
void takeInputLine() {
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
}

/* setAlphabet(char *)
 * Takes the name of a file as an argument and changes the internal alphabet
 * based on the contents of the file, picking all words and replacing the
 * alphabet with those words contained in the file, words defined as any string
 * of characters seperated by whitespace.
 * Function assumes that the file name can be invalid or inaccessable and will
 * handle errors as neccessary.
 */
void setAlphabet(char *optarg) {
    FILE *alphaFile;

    alphaFile = fopen(optarg, "r");

    if(alphaFile == NULL) {
        perror("File Open Error");
        exit(ERROR_THROWN);
    }

    fclose(alphaFile);
}

/* toNatoPhonetic(char *)
 * Converts the individal alphanumeric characters to their NATO Phonetic
 * counterparts.
 */
void toNatoPhonetic(char *inString) {
    char *traveler = NULL; // String used to travel along the input stirng 
    char normalizer; // used for calulating the input character's place in the Alphabet

    for(traveler = inString; *traveler != '\0'; traveler++) {
        bool isCapital;
        AlphaFormat inputFormat;

        if(isalnum(*traveler)) {
            if(isdigit(*traveler)) {
                normalizer = '0' - NUM_OFFSET; // Numbers are after the letters in the npa array
                isCapital = false;
                inputFormat = numberFormat;
            } else if(isupper(*traveler)) {
                normalizer = 'A';
                isCapital = true;
                inputFormat = universalFormat;
            } else {
                normalizer = 'a';
                isCapital = false;
                inputFormat = universalFormat;
            }

            printUserFormat(Alphabet[*traveler - normalizer], isCapital, inputFormat);
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
void printUserFormat(char *natoString, bool isCapital, AlphaFormat inputFormat) {
    char *changer = strdup(natoString); // manipulated value of the input string

    if(changer == NULL) {
        perror(MEM_ALLOC_ERROR);
        exit(ERROR_THROWN);
    }

    if((inputFormat == CAPS) || (inputFormat == FOLLOW && followFormat == CAPS && isCapital)) {
        changer = stringToUpper(changer);
    } else if((inputFormat == FIRST) || (inputFormat == FOLLOW && followFormat == FIRST && isCapital)) {
        changer = stringToFirst(changer);
    }

    printf("%s.", changer);

    free(changer);
}

/* stringToUpper(char *)
 * Takes a string and converts it into a string with all lower case letters to
 * uppercase.
 */
char *stringToUpper(char *inputString) {
    char *changer = inputString;
    char *traveler = NULL;

    for(traveler = changer; *traveler != '\0'; traveler++) {
        *traveler = toupper(*traveler);
    }

    return changer;
}

/* stringToFirst(char *)
 * Takes a string and changes the first letter in the string to uppercase and
 * the rest of the string to lower case.
 */
char *stringToFirst(char *inputString) {
    char *changer = inputString;
    *changer = toupper(*changer);

    return changer;
}
