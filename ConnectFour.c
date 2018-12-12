#include "c4.h"

int main()
{
    int board[ROWS][COLS] = {EMPTY_CELL};
    int currentPlayer = PLAYER_1;           // player 1 moves first
    int opponent = 0;
    bool gameWon = false;                   // did a player connect four?
    bool gameOver = false;                  // did the game end in a draw?
    srand(time(NULL));
    
    displayRules();
    opponent = chooseOpponent();
    
    /* Game loop */
    do
    {
        system("clear");                    // wipe the screen
        
        printf("Player %d's turn\n\n\n", currentPlayer);
        displayBoard(board);
        
        // if a computer's turn
        if (opponent == COMPUTER && currentPlayer == PLAYER_2)
        {
            usleep(SLEEP_TIME);
            gameWon = computerMove(board, currentPlayer);
        }
        // if a human's turn
        else
        {
            gameWon = makeMove(board, currentPlayer);
        }
        
        if (!gameWon)
        {   
            // if no player won, check if the board is full (i.e. game is a tie)
            gameOver = isBoardFull(board);
            
            if (!gameOver)
            {
                // if no player won and board is not full, next player's turn
                switchPlayer(&currentPlayer);
            }
        }
    }
    while (!gameWon && !gameOver);
    
    
    system("clear");
    
    if (gameWon)
    {
        printf("Player %d wins!\n\n\n", currentPlayer);
    }
    else
    {
        printf("It's a tie!\n\n\n");
    }
    
    displayBoard(board);
}


/*
 * Computer player makes a random move.
 *
 * It is assumed that the board is not full, otherwise an infinite loop
 * will occur.
 *
 * params:
 * board: the game board
 * currentPlayer: the player making the move
 *
 * returns:
 * true if the computer won the game, false otherwise
 */
bool computerMove(int board[ROWS][COLS], int currentPlayer)
{
    bool connectedFour = false;
    unsigned int col = 0;
    
    do
    {
        col = rand() % COLS;
    }
    while (board[TOP_ROW][col] != EMPTY_CELL);      // while column is full
    
    connectedFour = placePiece(board, col, currentPlayer);
    return connectedFour;
}


/*
 * Prompt the user to choose a column to drop their piece in.
 * The user is continually prompted until a valid input is made.
 *
 * If the user's input was successfully read (i.e. fgets does not return NULL),
 * check if the user's input ends with the newline character. If it does not,
 * then the local input buffer was not large enough to hold the user's input
 * and the input is assumed to be invalid. If this is the case, then the
 * standard input stream (stdin) will still have the remainder of the user input
 * that must be discarded manually.
 *
 * params:
 * board: the game board
 * currentPlayer: the player making the move
 *
 * returns:
 * true if the player won the game, false otherwise
 */
bool makeMove(int board[ROWS][COLS], int currentPlayer)
{
    bool connectedFour = false;
    long int choice = 0;            // long int so it can be used in parseInt()
    bool validChoice = false;
    char input[BUFFER_SIZE] = {0};
    char *returnPtr = NULL;
    unsigned int inputLen = 0;
    unsigned int col = 0;
    
    printf("Choose a column to place your piece (%d - %d)\n\n", 1, COLS);
    
    do
    {
        printf("Enter choice: ");
        
        returnPtr = fgets(input, BUFFER_SIZE, stdin);
        
        if (returnPtr != NULL)
        {
            inputLen = strlen(input);
            
            // no need to bounds check, already done at returnPtr != NULL
            if (input[inputLen - 1] != '\n')
            {
                clearStdinBuffer();
            }
            else
            {
                // if user input was a valid integer
                if (parseInt(input, &choice))
                {
                    // check for valid range
                    if (choice >= 1 && choice <= COLS)
                    {
                        col = choice - 1;   // subtract 1 for valid indexing
                        
                        // make sure the column is not already full
                        if (board[TOP_ROW][col] == EMPTY_CELL)
                        {
                            validChoice = true;
                        }
                        else
                        {
                            printf("Column %d is full\n", choice);
                        }
                    }
                    else
                    {
                        printf("Integer must be in range %d to %d\n", 1, COLS);
                    }
                }
            }
        }
    }
    while (!validChoice);
    
    connectedFour = placePiece(board, col, currentPlayer);
    return connectedFour;
}


/*
 * Place a player piece in the board at the specified column, and at the
 * next available row. If the column is full, the board will not be modified.
 *
 * If a game piece is placed, check if that addition to the game board made
 * four in a row for the current player.
 *
 * params:
 * board: the game board
 * col: the column to place a piece in
 * currentPlayer: the current player
 *
 * returns:
 * true if four in a row was made, false otherwise
 */
bool placePiece(int board[ROWS][COLS], int col, int currentPlayer)
{
    bool connectedFour = false;
    bool emptyCellFound = false;
    int cellValue = 0;
    unsigned int row = 0;
    
    /* Start searching from the bottom of the column for an empty cell */
    for (row = ROWS - 1; row >= 0 && !emptyCellFound; row--)
    {
        if (board[row][col] == EMPTY_CELL)
        {
            emptyCellFound = true;
        }
    }
    
    if (emptyCellFound)
    {
        row++;      // row was subtracted one extra at the end of the for loop
        
        if (currentPlayer == PLAYER_1)
        {
            cellValue = PLAYER_1_CELL;
        }
        else
        {
            cellValue = PLAYER_2_CELL;
        }
        
        board[row][col] = cellValue;
        
        /* Only need to check if they add to 3, since current row and column
           counts as 1 */
        connectedFour =
                // check vertical four in a row
                (count(board, row + 1, col, 1, 0, cellValue)
                    + count(board, row - 1, col, -1, 0, cellValue) == 3)
                // check horizontal four in a row
                || (count(board, row, col + 1, 0, 1, cellValue)
                    + count(board, row, col - 1, 0, -1, cellValue) == 3)
                // check left diagonal four in a row
                || (count(board, row + 1, col + 1, 1, 1, cellValue)
                    + count(board, row - 1, col - 1, -1, -1, cellValue) == 3)
                // check right diagonal four in a row
                || (count(board, row + 1, col - 1, 1, -1, cellValue)
                    + count(board, row -1, col + 1, -1, 1, cellValue) == 3);
    }
    
    return connectedFour;
}


/*
 * Recursive function to count number of pieces in a row.
 *
 * params:
 * board: the game board
 * row: the current row in the game board
 * col: the current column in the game board
 * rowAdd: used to get the next row to check in the game board
 * colAdd: used to get the next row to check in the game board
 * cellValue: the player piece that is being counted
 *
 * returns:
 * number of player pieces found in a row
 */
int count(int board[ROWS][COLS], int row, int col,
        int rowAdd, int colAdd, int cellValue)
{
    // check for out of bounds indices
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS)
    {
        return 0;
    }
    else if (board[row][col] != cellValue)
    {
        return 0;
    }
    else
    {
        return 1 + count(board, row + rowAdd, col + colAdd,
                rowAdd, colAdd, cellValue);
    }
}


/*
 * Determine if the board is full.
 *
 * Since the board must be filled bottom up (since gravity), only
 * need to check if the entire top row of the board is full.
 *
 * params:
 * board: the game board
 */
bool isBoardFull(int board[ROWS][COLS])
{
    bool isFull = true;
    unsigned int col = 0;
    
    for (col = 0; col < COLS && isFull; col++)
    {
        if (board[TOP_ROW][col] == EMPTY_CELL)
        {
            isFull = false;
        }
    }
    
    return isFull;
}


/*
 * Set the current player to the next player.
 *
 * params:
 * currentPlayerPtr: a pointer to the current player
 */
void switchPlayer(int *currentPlayerPtr)
{
    if (*currentPlayerPtr == PLAYER_1)
    {
        *currentPlayerPtr = PLAYER_2;
    }
    else
    {
        *currentPlayerPtr = PLAYER_1;
    }
}


/*
 * Display the connect four game board with its pieces.
 * The column numbers are labeled above the game board.
 *
 * params:
 * board: the game board
 */
void displayBoard(int board[ROWS][COLS])
{
    unsigned int row = 0;
    unsigned int col = 0;
    
    printf("   ");
    for (col = 0; col < COLS; col++)
    {
        printf("%d     ", col + 1);
    }
    printf("\n");
    
    for (col = 0; col < COLS; col++)
    {
        printf(" _____");
    }
    printf("\n");
    
    for (row = 0; row < ROWS; row++)
    {
        for (col = 0; col < COLS; col++)
        {
            printf("|     ");
        }
        printf("|\n");
        
        for (col = 0; col < COLS; col++)
        {
            printf("|  ");
            
            if (board[row][col] == PLAYER_1_CELL)
            {
                printColor(COLOR_BLUE);
                printf("O  ");
                printColor(COLOR_RESET);
            }
            else if (board[row][col] == PLAYER_2_CELL)
            {
                printColor(COLOR_RED);
                printf("O  ");
                printColor(COLOR_RESET);
            }
            else
            {
                printf("   ");
            }
        }
        printf("|\n");
        
        for (col = 0; col < COLS; col++)
        {
            printf("|_____");
        }
        printf("|\n");
    }
    printf("\n\n");
}


/*
 * Print an ANSI color code.
 *
 * params:
 * colorString: the color code to printColor
 */
void printColor(char *colorString)
{
    printf(colorString);
}


/*
 * Prompt the user to choose their opponent (human or computer).
 * The user is continually prompted until a valid input is made.
 *
 * If the user's input was successfully read (i.e. fgets does not return NULL),
 * check if the user's input ends with the newline character. If it does not,
 * then the local input buffer was not large enough to hold the user's input
 * and the input is assumed to be invalid. If this is the case, then the
 * standard input stream (stdin) will still have the remainder of the user input
 * that must be discarded manually.
 *
 * returns:
 * the user's choice (will be either HUMAN or COMPUTER)
 */
int chooseOpponent()
{
    long int choice = 0;            // long int so it can be used in parseInt()
    bool validChoice = false;
    char input[BUFFER_SIZE] = {0};
    char *returnPtr = NULL;
    unsigned int inputLen = 0;
    
    printf("Choose an opponent:\n%d - human\n%d - computer\n\n",
            HUMAN, COMPUTER);
    
    do
    {
        printf("Enter choice: ");
        
        returnPtr = fgets(input, BUFFER_SIZE, stdin);
        
        if (returnPtr != NULL)
        {
            inputLen = strlen(input);
            
            // no need to bounds check, already done at returnPtr != NULL
            if (input[inputLen - 1] != '\n')
            {
                clearStdinBuffer();
            }
            else
            {
                // if user input is a valid integer
                if (parseInt(input, &choice))
                {
                    if (choice == HUMAN || choice == COMPUTER)
                    {
                        validChoice = true;
                    }
                    else
                    {
                        printf("Integer must be %d or %d\n", HUMAN, COMPUTER);
                    }
                }
            }
        }
    }
    while (!validChoice);
    
    return choice;
}


/*
 * Attempt to convert a string into an integer.
 * Leading and/or trailing whitespace is ignored.
 *
 * If the remainder of the string after being processed by strtol() points to
 * the same memory address as the original string, then none of the original
 * string was successfully converted.
 * Function strtol() automatically ignores leading whitespace, but trailing
 * whitespace must be checked for manually.
 *
 * Postcondition: the contents at numberPtr are only modified if the original
 *                string is successfully converted to a valid integer.
 *
 * params:
 * string: the string to be parsed
 * numberPtr: a pointer to the where the parsed integer will be stored
 *
 * returns:
 * true if the string was successfully converted to an integer, false otherwise
 */
bool parseInt(const char *string, long int *numberPtr)
{
    bool validInteger = false;
    long int parsedInteger = 0;
    char *remainder = NULL;
    
    parsedInteger = strtol(string, &remainder, 0);
    
    if (string != remainder)
    {
        if (isWhitespace(remainder))
        {
            *numberPtr = parsedInteger;
            validInteger = true;
        }
    }
    
    return validInteger;
}


/*
 * Determine if a string contains only whitespace.
 * An empty string counts as being only whitespace.
 *
 * params:
 * string: the string to check for whitespace
 *
 * returns:
 * true if the string contains only whitespace, false otherwise
 */
bool isWhitespace(const char *string)
{
    bool whitespace = true;
    
    while (*string != '\0' && whitespace)
    {
        if (!isspace(*string))
        {
            whitespace = false;
        }
        
        string++;           // move to next character
    }
    
    return whitespace;
}


/*
 * Clear the standard input stream (stdin) buffer.
 *
 * This function assumes there are characters in stdin so that the user
 * will not be prompted to input a character.
 */
void clearStdinBuffer()
{
    char c = 0;
    
    do
    {
        c = getchar();
    }
    while (c != EOF && c != '\n');
}


/*
 * Show how to play connect four and win the game.
 */
void displayRules()
{
    printf("Welcome to Connect Four\n\n"
            "The goal of this game is to get four in a row.\nYou will drop "
            "pieces in any column you like.\nFour in a row can be achieved "
            "vertically, horizontally, or diagonally.\nThe first player to "
            "get four in a row wins the game.\nThe game ends in a tie if "
            "the board becomes full before either player wins.\n"
            "Quit the game at any time by pressing ctrl+c\n\n");
}
