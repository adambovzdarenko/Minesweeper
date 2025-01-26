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
        run_game(difficulty);
    }

    return 0;
}