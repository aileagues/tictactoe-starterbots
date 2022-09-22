#include <stdbool.h>  		/* For "bool" type instead of "_Bool" */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>		/* For isspace() */
#include <string.h>
#include <time.h>


/* ----------------------------------------------------------------
 * This is the TicTacToe starter bot in C for the AI League.
 *
 * It should be enhanced by reimplementing the genMove() function
 * to create more intelligent moves than pure random.
 * ---------------------------------------------------------------- */


/* ----------------------------------------------------------------
 * Global variables
 */


#define BUFSIZE   1024
#define MAXTOKENS  100


/* Change these to fit your own code. */

/* Settings */
double time_per_move = 1.0;

/* Updates */
int board[9];  /* The board, written when it's updated. */
int to_move;   /* The side to move. Possible values: 1 or 2 */


/* ----------------------------------------------------------------
 *                         Settings functions
 */


/* Set the time per move, in seconds, from the AI League protocol.
 * Return true/false whether it worked or not.
 */
bool setTimePerMove(char *token)
{
    double val;
    if (sscanf(token, "%lf", &val) != 1) {
	return false;
    }

    time_per_move = val;
    return true;
}


/* ----------------------------------------------------------------
 *                         Update functions
 */


/* Set the board from the AI League protocol.
 *
 * Return true/false if it went well/bad.
 */
bool updateBoard(int numParams, char params[][BUFSIZE])
{
    if (numParams != 9) {
	return false;
    }

    for (int i = 0; i < 9; i++) {
	int val;
	if (sscanf(params[i], "%d", &val) != 1) {
	    return false;
	}
	board[i] = val;
    }

    return true;
}

/* Set the side to move from the AI League protocol.
 *
 * Return true/false if it went well/bad.
 */
bool setToMove(char token[])
{
    int val;
    if (sscanf(token, "%d", &val) != 1) {
	return false;
    }

    to_move = val;
    return true;
}


/* ----------------------------------------------------------------
 *                         Action functions
 */


/* IMPROVE THIS FUNCTION TO MAKE A BETTER BOT.
 */
char *genMove()
{
    return "random";
}


/* ================================================================
 *                         Main loop
 */


bool readLine(char buf[])
{
    char *chp = fgets(buf, BUFSIZE, stdin);
    return !!chp;
}

int splitLine(char buf[], char tokens[MAXTOKENS][BUFSIZE])
{
    int tokenIx = 0;
    char *chp = &buf[0];
    while (*chp != '\0') {
	/* Skip whitespace before the token. */
	while (isspace(*chp) && *chp != '\0') {
	    chp++;
	}

	/* Return in case there was trailing whitespace after the last token. */
	if (*chp == '\0') {
	    return tokenIx;
	}

	/* Collect the next token */
	char *tokp = tokens[tokenIx];
	while (!isspace(*chp) && *chp != '\0') {
	    *tokp++ = *chp++;
	}
	*tokp = '\0';
	tokenIx++;
    }

    return tokenIx;
}

int main()
{
    srand(time(NULL));

    /* Main loop for the AI League TicTacToe protocol. */
    char line[BUFSIZE];
    while (readLine(line)) {
	fprintf(stderr, "line: %s", line);

	char tokens[MAXTOKENS][BUFSIZE];
        int numTokens = splitLine(line, tokens);
        if (numTokens == 0) {
            continue;
	}

        if (!strcmp(tokens[0], "settings")) {
	    /* Settings are sent at the beginning of a game and stay constant over the game. */
	    /* Possible settings are "time_per_move". */
            if (numTokens < 2) {
                fprintf(stderr, "Too few parameters to settings: %d\n", numTokens);
                fflush(stderr);
		continue;
	    }

	    if (!strcmp(tokens[1], "time_per_move")) {
                setTimePerMove(tokens[2]); 
	    } 
	}

        else if (!strcmp(tokens[0], "update")) {
	    /* Updates are sent before every move. */
	    /* Possible updates are "board" and "tomove" */
            if (numTokens < 2) {
                fprintf(stderr, "Too few parameters to update: %d\n", numTokens);
                fflush(stderr);
		continue;
	    }

            if (!strcmp(tokens[1], "board")) {
                updateBoard(numTokens - 2, tokens + 2); 
	    } else if (!strcmp(tokens[1], "tomove")) {
                setToMove(tokens[2]); 
            } else {
                fprintf(stderr, "Unknown update command: %s\n", tokens[1]);
	    }

	} else if (!strcmp(tokens[0], "action")) {
	    /* Only action is "move". */

            if (numTokens < 2) {
                fprintf(stderr, "Too few action tokens: %d\n", numTokens);
		fflush(stderr);

		fprintf(stdout, "%s", ""); /* Just to give any reply */
		fflush(stdout);
		continue;
	    }

            if (!strcmp(tokens[1], "move")) {
                char *moveStr = genMove();
		printf("%s\n", moveStr);
	    } else {
                fprintf(stderr, "Unknown action command: %s\n", tokens[1]);
		fprintf(stdout, "%s", "");
	    }
	}

        fflush(stdout);
	fflush(stderr);
    }

    return 0;
}
