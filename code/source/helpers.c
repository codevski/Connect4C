#include "helpers.h"
#define LENGTH_INT 1
#define LENGTH 20

/**
 * @file helpers.c contains various functions that help in the
 * implementation of the program. You should put functions you create
 * here unless they logically belong to another module (such as
 * player, board or game
 **/

void read_rest_of_line(void)
{
    int ch;
    while(ch = getc(stdin), ch!=EOF && ch != '\n')
        ; /* gobble each character */
    /* reset the error status of the stream */
    clearerr(stdin);
}

/* This Function Written by Steven Burrows and adapted by Sash Petrovski */
int getInteger(int* integer, unsigned length, char* prompt, int min, int max)
{
	int finished = FALSE;
	char tempString[LENGTH_INT + 2];
	int tempInteger = 0;
	char* endPtr;

	do
	{
		printf("%s", prompt);

		/* check if the user ctrl+D */
		if(fgets(tempString, LENGTH_INT + 2, stdin) == NULL)
		{
			printf("\nReturn to menu");
			return RTM;
		}
		else
			if(tempString[0] == '\n')
			{
				printf("Return to Menu\n");
				return RTM;
			}

		if (tempString[strlen(tempString) - 1] != '\n')
		{
			printf("Input was too long.\n");
			read_rest_of_line();
		}
		else
		{
			tempString[strlen(tempString) - 1] = '\0';
			tempInteger = (int) strtol(tempString, &endPtr, 10);

			if (strcmp(endPtr, "") != 0)
			{
				printf("Input was not numeric.\n");
			}
			else if (tempInteger < min || tempInteger > max)
			{
				printf("Input was not within range %d - %d.\n", min, max);
			}
			else
			{
				finished = TRUE;
			}
		}
	} while (finished == FALSE);

	*integer = tempInteger;
	return TRUE;
}

/* This Function Written by Steven Burrows and adapted by Sash Petrovski */
int getString(char* string)
{
   int finished = FALSE;
   char tempString[LENGTH];

   /* Continue to interact with the user until the input is valid. */
   do
   {
      /* Accept input. "+2" is for the \n and \0 characters. */
      fgets(tempString, LENGTH + 2, stdin);

      /* A string that doesn't have a newline character is too long. */
      if (tempString[strlen(tempString) - 1] != '\n')
      {
    	  printf("Input was too long. Please try again!\n");
    	  read_rest_of_line();
      }
      else
      {
         finished = TRUE;
      }
   } while (finished == FALSE);

   /* Overwrite the \n character with \0. */
   tempString[strlen(tempString) - 1] = '\0';

   /* Make the result string available to calling function. */
   strcpy(string, tempString);

   return TRUE;
}
