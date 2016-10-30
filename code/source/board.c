#include "board.h"
#include "player.h"

/**
 * @file board.c contains implementations of functions related to the game
 * board.
 **/

/**
 * @param board the board to reset the contents of
 **/
void initialise_board(enum cell_contents board[][BOARDWIDTH])
{
	int i, j;

	printf("Game Board Initilised!\n");

	for(i = 0; i < BOARDHEIGHT; i++)
	{
		for(j = 0; j < BOARDWIDTH; j++)
		{
			board[i][j] = C_EMPTY;
		}
	}

}

/**
 * In this requirement you are required to display the game board.
 * The game board should be displayed as shown on the first page of the
 * assignment specification.
 * @param board the board to display
 **/
void display_board(enum cell_contents board[][BOARDWIDTH])
{
	int i, j;
	printf("\n 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n");
	for(i = 0; i < BOARDHEIGHT; i++)
	{
		printf("----------------------------------\n");
		for(j = 0; j < BOARDWIDTH; j++)
		{
			switch(board[i][j])
			{
			case C_EMPTY: printf("   |");
			break;
			case C_RED: printf(" %s |", RED_TOKEN);
			break;
			case C_WHITE: printf(" %s |", WHITE_TOKEN);
			break;
			}
		}
		printf("\n");
	}
	printf("-----------------------------------\n");
}
