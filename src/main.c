#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>  // Include unistd.h for getopt and optarg
#include "board.h"
#include "game.h"

int main(int argc, char *argv[]) {
    int difficulty = 1; // Default difficulty
    char *filename = NULL;

    int opt;
    while ((opt = getopt(argc, argv, "f:d:")) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;
                break;
            case 'd':
                difficulty = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-f filename] [-d difficulty]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    if (filename) {
        return run_from_file(filename);
    } else {
        printf("1 - Easy\n");
        printf("2 - Medium\n");
        printf("3 - Hard\n");
        printf("4 - Custom\n");
        printf("Enter your choice (1, 2, 3, or 4): ");
        scanf("%d", &difficulty);

        int rows, cols, mines;

        switch (difficulty) {
            case 1:
                rows = 9; cols = 9; mines = 10;
                break;
            case 2:
                rows = 16; cols = 16; mines = 40;
                break;
            case 3:
                rows = 16; cols = 30; mines = 99;
                break;
            case 4:
                printf("Enter number of rows: ");
                scanf("%d", &rows);
                printf("Enter number of columns: ");
                scanf("%d", &cols);
                printf("Enter number of mines: ");
                scanf("%d", &mines);
                break;
            default:
                fprintf(stderr, "Invalid difficulty level. Defaulting to Easy (1).\n");
                rows = 9; cols = 9; mines = 10;
                break;
        }

        // Validate the number of mines
        if (mines >= rows * cols) {
            fprintf(stderr, "Number of mines cannot be greater than or equal to the number of cells. Defaulting to Easy (1).\n");
            rows = 9; cols = 9; mines = 10;
        }

        run_game_custom(rows, cols, mines);
    }

    return 0;
}
