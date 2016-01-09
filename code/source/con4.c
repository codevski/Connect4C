/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1
* Full Name        : Saso Petrovski
* Student Number   : S3435996
* Course Code      : COSC1076
* Program Code     : BP096
* Start up code provided by Paul Miller
***********************************************************************/
#include "con4.h"

/**
 * @mainpage COSC1076 - Assignment 1 documentation.
 *
 * This is the main html documentation of assignment 1 for COSC1076 -
 * Advanced Programming Techniques for semester 2, 2015. You will find
 * here a description of the functions that you need to implement for
 * your assignment.
 *
 * Please note that this should not be your first stop when starting
 * your assignment. Please read the assignment 1 specifications that
 * are available on blackboard before reading this documentation. The
 * purpose of this documentation is to clarify the actual individual
 * requirements.
 *
 * This site presents you with the documentation for each function
 * that you need to implement broken down by the file that they exist
 * in. Please go to the <b>Files</b> tab and click on the file you wish to
 * get more information about and then click on that file. An
 * explanation of each function implemented in that file will be
 * displayed.
 **/

/**
 * @file con4.c contains the main function which is the entry point into the
 * application and manages the main memory.
 **/

/**
 * the entry point into the game. You should display the main menu and
 * respond to user requests.
 *
 * The main menu should look like this:
 * Welcome to connect 4
 *  \n\--------------------
 * 1. Play Game
 * 2. Display High Scores
 * 3. Quit
 * Please enter your choice:
 *
 * This menu should also be redisplayed when the program returns from
 * running an option.
 **/
int main(void)
{
    /* the scoreboard for keeping track of winners */
    scoreboard scores;
    /* the two players and a pointer to who won the last game */
    struct player human_player, computer_player, *winner;

    /* My variables */
    int choice;
    /*char h_colour[NAMELEN], c_colour[NAMELEN];*/
    char* prompt = "Please enter your choice:\n";

    /* with each of the comments below, insert the code that performs
     * this function
     */

    /* initialise the scoreboard */
    init_scoreboard(scores);

    /*display menu and get menu choice until the user chooses to quit */
    do {
      printf("\nWelcome to connect 4\n");
      printf("--------------------\n");
      printf("1. Play Game\n");
      printf("2. Display High Scores\n");
      printf("3. Quit\n");
      /*scanf("%d", &choice); <- To Delete*/
      getInteger(&choice, 2, prompt, 1, 3);

      switch(choice)
      {
        case 1:
        	/* play a game option */
        	srand(time(NULL));
        	winner = play_game(&human_player, &computer_player);

        	if(winner == G_DRAW)
        	{
        		/* if there was a draw, alert the user to this fact */
        		printf("\nNo Winner - Back to Menu\n");
        	}
        	else
        	{
    		    /* if there was not a draw, add player to the scoreboard in
    		     * order by number of tokens in play
    		     */
        		add_to_scoreboard(scores, winner);
        		/* let the user know who won */
        		printf("Player %s Won!\n", winner->name);
        	}
          break;
        case 2:
        	/* display the scoreboard option */
        	display_scores(scores);
          break;
        case 3:
        	/* quit the program option */
        	printf("Exiting\n");
        	exit(0);
          break;
        default: printf("Invalid Choice\n");
          break;
      }

    } while(choice != 3);
    return EXIT_SUCCESS;
}
