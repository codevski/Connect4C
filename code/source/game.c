/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1
* Full Name        : Saso Petrovski
* Student Number   : S3435996
* Course Code      : COSC1076
* Program Code     : BP096
* Start up code provided by Paul Miller
***********************************************************************/
#include "game.h"
#define KRED  "\x1B[31m"

/**
 * @file game.c contains the functions that relate to the management of
 * the game.
 **/

/**
 * This requirement requires you to understand a little more about pointers.
 * We want you to understand that all pointers just point to another memory
 * address whether they are a single pointer, a pointer to a pointer, etc.
 *
 * In this example, we want you to swap the pointers for two players.
 * This will be called from \ref play_game with a call such as
 * swap(&current, &other) and at the end of this function, current and
 * other's pointers will be swapped.
 * For example, if current points to the human player and other points to
 * the computer player, at the end of this function, the player they point
 * to will have been swapped.
 *
 * @param current the current player who has just completed their turn
 * @param other the next player whose turn it will be
 **/
static void swap_players(struct player ** current, struct player ** other)
{
    /* implement a classic swap using a temporary pointer */

	struct player * temp;
	temp = *current;

	*current = *other;
	*other = temp;

}

/**
 * This is the heart of the game.
 *
 * Firstly, you need to initialise the game by calling functions written
 * for requirement 3. The rest of this function is then managing the game
 * loop.
 *
 * Each player takes a turn to drop a token into a column on the game
 * board. The task that needs to be performed will be different depending
 * on whether this is a human or a computer player.
 *
 * Regardless of the player type, you will need to display the board as it
 * was before the player makes their move. If the current player is a
 * computer player, we just need to select a column at random and drop a
 * token into that column. If there is no room, try another column.
 *
 * If the current player is a human player, your program will need to ask
 * the user what column they wish to drop a token in. This input should be
 * validated to check that it is numeric and within the range of allowed
 * columns.
 *
 * Once a valid move has been entered, your program should update the
 * gameboard. It should then check if the game has been won lost or drawn
 * by calling and the change the current player.
 *
 * This function also checks if the game has been won, lost or drawn by
 * calling \ref test_for_winner(), and if the game is over, returns the
 * winner to main or NULL if the game was a draw.

 * @param human a pointer to details about the human player
 * @param computer a pointer to details about the computer player
 **/
struct player * play_game(struct player * human ,
        struct player* computer)
{
    int x, input;
	/* declaration that allocates the board for the game */
    enum cell_contents board[BOARDHEIGHT][BOARDWIDTH];

    /* Getting the player name */
	get_human_player(human);
    get_computer_player(computer);

    /* Setting up the board */
    initialise_board(board);


    /* Calling function to set the colour for human and computer players */
    set_colour(human,computer);

	/* Start taking turns making sure whoever is white goes first */
    if(human->thiscolor == C_WHITE)
    {
    	printf("Your colour is \x1B[37mWHITE\x1B[0m, you go first!\n");
    	display_board(board);
    	input = take_turn(human, board);
    	swap_players(&human, &computer);

    }
    else
    {
    	take_turn(computer, board);
    	printf("Your colour is \x1B[31mRED\x1B[0m\n\n");
    }
    display_board(board);
    do
    {
        /* If user ctrl+D its caught and returns NULL to the calling function */
    	if(input == RTM)
        {
        	return NULL;
        }
    	swap_players(&human, &computer);
        input = take_turn(computer, board);
        display_board(board);
    }while((x = test_for_winner(board)) == G_NO_WINNER);

    /* If test for winner returns value other than no winner check status */
    if (x == G_WHITE)
    {
    	if(human->thiscolor == C_WHITE)
    	{
    		return human;
    	}
    	else
    		return computer;
    }
    if (x == G_RED)
    {
    	if(human->thiscolor == C_RED)
    	{
    		return human;
    	}
    	else
    		return computer;
    }

    return G_DRAW;
}

/**
 * In this requirement you are required to test what the game's current
 * state is.
 * Possible game states are defined by the game_state enumeration:
 * enum game_state
 * {
 *    G_NO_WINNER=-1,
 *    G_DRAW,
 *    G_RED,
 *    G_WHITE
 * };
 *
 * Most of these states should be self-explanatory but let's go through
 * their meaning.
 *
 *    &bull; G_NO_WINNER: the game is still in progress and therefore there
 *    is no winner yet.
 *
 *    &bull; G_DRAW: neither player has won the game but there are no more
 *    spaces left for a player to make a move.
 *
 *    &bull; G_RED / G_WHITE: the player whose token is the specified
 *    colour has won the game.
 *
 * Your task in this function is to iterate over the 2-dimensional array
 * (the board) looking for four in a row in any direction – if you find
 * this, return the appropriate value of either G_RED or G_WHITE.
 *
 * Next, test for a draw. If none of these cases hold, return G_NO_WINNER.
 * @param board the gameboard to test for a winner
 **/
enum game_state test_for_winner(
        enum cell_contents board[][BOARDWIDTH])
{
    /* default return value  - delete this comment and the return statement
     * below and replace them with the game logic for deciding whether a
     * game has been won and who the winner is
     */

	int i, j;

	/* Check for C_RED Winner */
	for(i = 0; i < BOARDHEIGHT; i++)
		{
			for(j = 0; j < BOARDWIDTH; j++)
			{
				/* Check Vertical w/boundary check */
				if ((board[i][j]==C_RED)&&(board[i+1][j]==C_RED)&&
						(board[i+1][j]==C_RED)&&(board[i+2][j]==C_RED)&&
						(board[i+2][j]==C_RED)&&(board[i+3][j]==C_RED)&&
						(i+3 < BOARDHEIGHT))
				{
						return G_RED;
				}
				if ((board[i][j]==C_WHITE)&&(board[i+1][j]==C_WHITE) &&
						(board[i+1][j]==C_WHITE)&&(board[i+2][j]==C_WHITE)&&
						(board[i+2][j]==C_WHITE)&&(board[i+3][j]==C_WHITE)&&
						(i+3 < BOARDHEIGHT))
				{
						return G_WHITE;
				}
				/* Check Horizontal w/boundary check */
				if ((board[i][j]==C_RED)&&(board[i][j+1]==C_RED) &&
						(board[i][j+1]==C_RED)&&(board[i][j+2]==C_RED)&&
						(board[i][j+2]==C_RED)&&(board[i][j+3]==C_RED)&&
						(j+3 <BOARDWIDTH))
				{
						return G_RED;
				}
				if ((board[i][j]==C_WHITE)&&(board[i][j+1]==C_WHITE) &&
						(board[i][j+1]==C_WHITE)&&(board[i][j+2]==C_WHITE)&&
						(board[i][j+2]==C_WHITE)&&(board[i][j+3]==C_WHITE)&&
						(j+3 <BOARDWIDTH))
				{
						return C_WHITE;
				}
				/* Slope Left w/boundary check */
				if ((board[i][j] == C_RED) &&(board[i+1][j+1] == C_RED)&&
						(board[i+1][j+1] == C_RED)&&(board[i+2][j+2] == C_RED)&&
						(board[i+2][j+2] == C_RED)&&(board[i+3][j+3] == C_RED)&&
						(i+3 < BOARDHEIGHT))
				{
					return G_RED;
				}
				if ((board[i][j] == C_WHITE) &&(board[i+1][j+1] == C_WHITE)&&
						(board[i+1][j+1] == C_WHITE)&&(board[i+2][j+2] == C_WHITE)&&
						(board[i+2][j+2] == C_WHITE)&&(board[i+3][j+3] == C_WHITE)&&
						(i+3 < BOARDHEIGHT))
				{
					return C_WHITE;
				}
				/* Slope Right w/boundary check */
				if ((board[i][j] == C_RED) &&(board[i+1][j-1] == C_RED)&&
						(board[i+1][j-1] == C_RED)&&(board[i+2][j-2] == C_RED)&&
						(board[i+2][j-2] == C_RED)&&(board[i+3][j-3] == C_RED)&&
						(i+3 < BOARDHEIGHT))
				{
					return G_RED;
				}
				if ((board[i][j] == C_WHITE) &&(board[i+1][j-1] == C_WHITE)&&
						(board[i+1][j-1] == C_WHITE)&&(board[i+2][j-2] == C_WHITE)&&
						(board[i+2][j-2] == C_WHITE)&&(board[i+3][j-3] == C_WHITE)&&
						(i+3 < BOARDHEIGHT))
				{
					return C_WHITE;
				}
			}
		}

	/* If there are any spots left on the board continue game */
	for(i = 0; i < BOARDHEIGHT; i++)
	{
		for(j = 0; j < BOARDWIDTH; j++)
		{
			if (board[i][j] == C_EMPTY)
			{
				return G_NO_WINNER;
			}
		}
	}

    return G_DRAW;
}

void set_colour(struct player * human , struct player* computer)
{
    /* Setting a colour for Human and Computer */
	int random;
    char h_colour[NAMELEN], c_colour[NAMELEN];

	random = rand() % 3 + 1;
	if (random >= 2)
	{
		human->thiscolor = C_RED;
		strcpy(h_colour, "Red");
		computer->thiscolor = C_WHITE;
		strcpy(c_colour, "White");
	}
	else
	{
		human->thiscolor = C_WHITE;
		strcpy(h_colour, "White");
		computer->thiscolor = C_RED;
		strcpy(c_colour, "Red");
	}
}
