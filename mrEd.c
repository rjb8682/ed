#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char * argv[]) {

	int RUNNING = 1;
	int startingSize = 80;
	size_t amountRead;

	char * input = (char *) malloc(startingSize);

	while(RUNNING) {

		amountRead = getline(&input, &amountRead, stdin);

		if (strcmp(input, "Q\n") == 0) {      // Hard Quit

			break;

		} else if (strcmp(input, "i\n") == 0) {    // Input mode

			printf("Entering input mode.\n");

			while (1) {

				getline(&input, &amountRead, stdin);

				if (strcmp(input, ".\n") == 0) {

					printf("Exiting input mode.\n");
					break;

				}

			}

		} else if (strcmp(input, "a\n") == 0) {

			printf("Entering append mode.\n");

			while (1) {

				getline(&input, &amountRead, stdin);

				if (strcmp(input, ".\n") == 0) {

					printf("Exiting append mode.\n");
					break;
					
				}

			}

		} else if (strcmp(input, ".\n") == 0) {

			printf("Printing current line.\n");

		} else if (strcmp(input, "+\n") == 0 || strcmp(input, "\n") == 0) {

			printf("Advancing to next line and printing that line.\n");

		} else if (strcmp(input, "-\n") == 0) {

			printf("Moving to previous line and printin that line.\n");

		} else if (strcmp(input, "$\n") == 0) {

			printf("Move to very last line and print it.\n");

		} else if (strcmp(input, "d\n") == 0) {

			printf("Delete the current line.\n");

		} else if (strcmp(input, ".=\n") == 0) {

			printf("Printing current line number.\n");

		} else if (strcmp(input, "$=\n") == 0) {

			printf("Printing number of the last line.\n");

		} else if (strcmp(input, "p\n") == 0) {

			printf("Printing contents of buffer.\n");

		} else if (strcmp(input, "w\n") == 0) {

			printf("Write to file. DONT FORGET TO MAKE IS ASK FOR A FILE\n");

		} else if (strcmp(input, "q\n") == 0) {

			printf("Safe Quiting\n");
			break;

		}

	}

	free(input);

}