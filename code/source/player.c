#include "player.h"
#include <time.h>

/**
 * @param human the human player to initialise
 **/
enum input_result get_human_player(struct player* human)
{
    /* placeholder return value. You should prompt the user
     * for their name and then initialise all other values in the
     * player struct to sensible values.
     */

     printf("Please enter player name:\n");

     getString(human->name);

     /* Set Values for human */
     human->counters = 0;
     human->type = HUMAN;

    return FAILURE;
}

/**
 * @param computer the computer player to initialise
 **/
enum input_result get_computer_player(struct player * computer)
{
    /* initialise all variables that are part of the struct to sensible
     * values */

	strcpy(computer->name, "Computer");
	computer->counters = 0;
	computer->type = COMPUTER;

    return FAILURE;
}

/**
 * In this requirement, you need to handle the taking of a turn - either
 * of a human or a computer player.
 *
 * For the human player, you will need to allow the user to enter the
 * column they wish to place a token in. You will need to validate what
 * the user enters, then place a token correctly in that column so that
 * it occupies the cell closest to the bottom of the board array for that
 * column.
 *
 * For the computer player, you will need to randomly generate a column
 * number to place a token in and if that column is full, generate a
 * different column number until a column number with some free space has
 * been found.
 *
 * @param current the current player
 * @param board the game board that we will attempt to insert a token into
 * @return enum @ref input_result indicating the state of user input (in
 * case this run involved user input
 **/
enum input_result take_turn(struct player * current,
        enum cell_contents board[][BOARDWIDTH])
{
    /*
     * Default return value - delete this comment and the return
     * value and replace it with appropriate logic to handle either
     * a human or computer turn including handling any input errors.
     */
	int i, j, input;
	int placed = 0;
	char* prompt = "Please enter a column in which to drop a token:\n";
	i = 1;

	j = BOARDHEIGHT;

	/* Human Control Logic */
	if(current->type == HUMAN)
	{
		input = getInteger(&i, 2, prompt, 1, 7);
		if (input == RTM)
		{
			return RTM;
		}
		do
		{
			if(board[0][i-1] != C_EMPTY)
			{
				getInteger(&i, 2, prompt, 1, 7);
				j = BOARDHEIGHT;
			}
			if(board[j-1][i-1] != C_EMPTY)
			{
				--j;
			}
			else if(board[j-1][i-1] == C_EMPTY)
			{
				board[j-1][i-1] = current->thiscolor;
				placed = 1;
			}
		}while(placed == 0);
		++current->counters;
	}
	else
	/* Computer Control Logic */
	{
		i = rand() % 7 + 1;
		do
		{
			if(board[0][i-1] != C_EMPTY)
			{
				i = rand() % 7 + 1;
				j = BOARDHEIGHT;
			}
			if(board[j-1][i-1] != C_EMPTY)
			{
				--j;
			}
			else if(board[j-1][i-1] == C_EMPTY)
			{
				board[j-1][i-1] = current->thiscolor;
				placed = 1;
			}
		}while(placed == 0);
		++current->counters;
	}
    return TRUE;
}
