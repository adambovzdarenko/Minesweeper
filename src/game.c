#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "game.h"
#include "utils.h"

void run_game(int difficulty) {
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
        default:
            fprintf(stderr, "Invalid difficulty level\n");
            exit(EXIT_FAILURE);
    }

    run_game_custom(rows, cols, mines);
}

void run_game_custom(int rows, int cols, int mines) {
    Board *board = create_board(rows, cols, mines);
    int first_move = 1;
    int game_over = 0;
    int won = 0;

    while (!game_over) {
        print_board(board);
        char command;
        int row, col;
        printf("Enter command (f x y or r x y): ");
        scanf(" %c %d %d", &command, &row, &col);

        if (first_move) {
            place_mines(board, row, col);
            first_move = 0;
        }

        if (command == 'f') {
            toggle_flag(board, row, col);
        } else if (command == 'r') {
            reveal_cell(board, row, col);
            if (board->board[row][col] == -1) {
                game_over = 1;
            } else {
                won = check_win(board);
                if (won) game_over = 1;
            }
        }
    }

    print_board(board);
    if (won) {
        printf("Congratulations! You won!\n");
        int score = calculate_score(board, 1); // Assuming difficulty 1 for simplicity
        char name[20];
        printf("Enter your name: ");
        scanf("%s", name);
        save_score(name, score);
        read_scores();
    } else {
        printf("Game over! You hit a mine.\n");
    }

    free_board(board);
}

int run_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return -1;
    }

    int rows, cols, mines;
    fscanf(file, "%d %d %d", &rows, &cols, &mines);

    Board *board = create_board(rows, cols, mines);

    // Read the board layout from the file
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char cell;
            fscanf(file, " %c", &cell);
            if (cell == '*') {
                board->board[i][j] = -1;
            } else {
                board->board[i][j] = cell - '0';
            }
        }
    }

    int correct_steps = 0;
    int total_points = 0;
    int game_result = 1; // 1 for win, 0 for loss

    char command;
    int row, col;
    while (fscanf(file, " %c %d %d", &command, &row, &col) == 3) {
        if (command == 'f') {
            toggle_flag(board, row, col);
        } else if (command == 'r') {
            reveal_cell(board, row, col);
            if (board->board[row][col] == -1) {
                game_result = 0;
                break;
            } else {
                if (check_win(board)) {
                    break;
                }
            }
            correct_steps++;
            total_points += calculate_score(board, 1); // Assuming difficulty 1 for simplicity
        }
    }

    fclose(file);
    free_board(board);

    printf("Correct steps: %d\n", correct_steps);
    printf("Total points: %d\n", total_points);
    printf("Game result: %d\n", game_result);

    return game_result;
}