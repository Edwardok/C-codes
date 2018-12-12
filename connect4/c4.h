#include <stdio.h>
#include <stdbool.h>    /* For boolean true and false values */
#include <string.h>     /* strlen(): to get the length of a string */
#include <stdlib.h>     /* strol(): for converting strings to integers
                           rand(): to generate random numbers */
#include <time.h>       /* time(): used to initialize the PRNG */
#include <ctype.h>      /* isspace(): to check if a character is whitespace */


#define BUFFER_SIZE 80  // size for input buffers, equal to width of the screen

#define ROWS 6                  // number of rows in the game board
#define COLS 7                  // number of columns in the game board
#define TOP_ROW 0               // index for the top row of the game board
#define EMPTY_CELL 0            // empty flag for a cell in the game board
#define PLAYER_1_CELL 1         // player 1 flag for a cell in the game board
#define PLAYER_2_CELL 2         // player 2 flag for a cell in the game board
#define COLOR_BLUE "\033[1;36m" // blue color for player 1's pieces
#define COLOR_RED "\033[1;31m"  // red color for player 2's pieces
#define COLOR_RESET "\033[0m"   // reset the color to normal
#define SLEEP_TIME 1000000      // time that the computer sleeps during its turn


/* Identifier for the current player's turn */
enum player
{
    PLAYER_1 = 1,
    PLAYER_2 = 2
};
    

/* Type of the player's opponent */
enum opponent
{
    HUMAN = 1,
    COMPUTER = 2
};


/* Function prototypes */
bool computerMove(int board[ROWS][COLS], int currentPlayer);
bool makeMove(int board[ROWS][COLS], int currentPlayer);
bool placePiece(int board[ROWS][COLS], int columnChoice, int currentPlayer);
int count(int board[ROWS][COLS], int row, int col,
        int rowAdd, int colAdd, int cellValue);
bool isBoardFull(int board[ROWS][COLS]);
void switchPlayer(int *currentPlayerPtr);
void displayBoard(int board[ROWS][COLS]);
void printColor(char *colorString);
int chooseOpponent();
bool parseInt(const char *string, long int *numberPtr);
bool isWhitespace(const char *string);
void clearStdinBuffer();
void displayRules();
