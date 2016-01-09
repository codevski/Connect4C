/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1
* Full Name        : Saso Petrovski
* Student Number   : S3435996
* Course Code      : COSC1076
* Program Code     : BP096
* Start up code provided by Paul Miller
***********************************************************************/
#include "scoreboard.h"

/**
 * @param board the scoreboard to initialise
 **/
void init_scoreboard(scoreboard board)
{
	int i;

	printf("Score Board initialised\n");

	for(i = 0; i < SCOREBOARDSIZE; i++)
	{
		strcpy(board[i].name, "");
		board[i].counters = (unsigned) 0;

	}
}

/** For this requirement, you will need to display the scores in the
 * order they are scored in the scoreboard array.
 *
 * The display should look as follows:
 * Player               |Score
 * ---------------------------------------------
 * Barney               |17
 * Magi                 |15
 * Red                  |10
 * Computer             |8
 * Computer             |7
 * Computer             |6
 * Paul                 |4
 * Fred                 |4
 * Muaddib              |4
 * Zafiqa               |4
 *
 * @param board the scoreboard to display
 **/
void display_scores(const scoreboard board)
{
  int i;

  printf("%s%20s\n", "Player", "|Score");
  printf("%s", "------------------------------------------------\n");
  for(i = 0; i < SCOREBOARDSIZE; i++)
  {
	  /* Only to print values that exist and not empty space */
	  if(strlen(board[i].name) > 0)
	  {
		  printf("%-20s|%-20d\n", board[i].name,board[i].counters);
	  }
  }
}

/** When the game ends, you need to return the appropriate game state
 * back to main. You will then need to insert the winner's score
 * sorted in order by the number of counters that they played in the
 * game. You should only store the top ten scores and so when a new score
 * is entered on a full scoreboard, the lowest score simply drops off the
 * bottom of the board.
 *
 * Both scoreboard and score are typedefs (aliases) of other types.
 *
 * Scoreboard is defined as: typedef struct player
 *
 * scoreboard[SCOREBOARDSIZE]; and score is defined as:
 *
 * typedef struct player score;
 *
 * In other words, a scoreboard is an array of struct player of
 * SCOREBOARDSIZE (10) and a score is another name of a player struct.
 * This has been done so we can reuse the type and it simplifies the
 * maintenance of the code.
 *
 * @param board the scoreboard to add the score to @param sc the score
 * to add to the scoreboard
 **/
 BOOLEAN add_to_scoreboard(scoreboard board, const score * sc)
 {
    /* placeholder return value - delete this and insert logic for
     * inserting in sorted order by number of counters in play at the
     * time the player won.  Remember that empty slots in the
     * scoreboard are signified by names which are equivalent to the
     * empty string.
     */
	 int i, min = 1, spot;

	 /* Logic to add to scoreboard */
	 for(i=0; i < SCOREBOARDSIZE; i++)
	 {
		 /* Logic to find smallest number */
		 if(board[i].counters <= min)
		 {
			 min = board[i].counters;
			 spot = i;
		 }

		 /* Look for a spot if found add to scoreboard */
		 if(board[i].counters == 0)
		 {
			 strcpy(board[i].name, sc->name);
			 board[i].counters = sc->counters;
			 sort_scoreboard(board);
			 return TRUE;
		 }

	 }
	 /* If scoreboard replace the smallest score with current score */
	 if(sc->counters > min)
	 {
		 printf("ELSEELS3333E\n");
		 board[spot] = *sc;
		 sort_scoreboard(board);
		 return TRUE;
	 }

    return FALSE;
}

/** When the game ends and attempts to add to the scoreboard this function
 * is called to sort the scoreboard from highest to lowest. The logic taken
 * from lecture and in swap player helped in a way.
 *
 * @param board so it rearrange the scoreboard.
 */
 int sort_scoreboard(scoreboard board)
 {
 	int i,j;
 	score temp;

 	for(i=0; i < (SCOREBOARDSIZE-1); i++)
 		 {
 			 for(j = i + 1; j < SCOREBOARDSIZE; j++)
 			 {
 				 if(board[i].counters < board[j].counters)
 				 {
 					 temp = board[i];
 					 board[i] = board[j];
 					 board[j] = temp;
 				 }
 			 }
 		 }
 	return EXIT_SUCCESS;
 }
