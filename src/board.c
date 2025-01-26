#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

Board* create_board(int rows, int cols, int mines) {
    Board *board = malloc(sizeof(Board));
    board->rows = rows;
    board->cols = cols;
    board->mines = mines;
    board->board = calloc(rows, sizeof(int*));
    board->revealed = calloc(rows, sizeof(int*));
    board->flags = calloc(rows, sizeof(int*));

    for (int i = 0; i < rows; i++) {
        board->board[i] = calloc(cols, sizeof(int));
        board->revealed[i] = calloc(cols, sizeof(int));
        board->flags[i] = calloc(cols, sizeof(int));
    }

    return board;
}

void free_board(Board *board) {
    for (int i = 0; i < board->rows; i++) {
        free(board->board[i]);
        free(board->revealed[i]);
        free(board->flags[i]);
    }
    free(board->board);
    free(board->revealed);
    free(board->flags);
    free(board);
}

void print_board(Board *board) {
    // Calculate the number of digits in the maximum row index
    int max_row_digits = snprintf(NULL, 0, "%d", board->rows - 1) + 1;

    // Print column headers with the same width as the row numbers
    printf("%*s", max_row_digits, " ");
    for (int j = 0; j < board->cols; j++) {
        printf("%*d ", max_row_digits, j);
    }
    printf("\n");

    for (int i = 0; i < board->rows; i++) {
        printf("%*d ", max_row_digits, i);
        for (int j = 0; j < board->cols; j++) {
            if (board->flags[i][j]) {
                printf("%*s ", max_row_digits, "F");
            } else if (!board->revealed[i][j]) {
                printf("%*s ", max_row_digits, ".");
            } else if (board->board[i][j] == -1) {
                printf("%*s ", max_row_digits, "*");
            } else {
                printf("%*d ", max_row_digits, board->board[i][j]);
            }
        }
        printf("\n");
    }
}

void place_mines(Board *board, int first_row, int first_col) {
    srand(time(NULL));
    int mines_placed = 0;

    while (mines_placed < board->mines) {
        int row = rand() % board->rows;
        int col = rand() % board->cols;

        if (row == first_row && col == first_col) continue;
        if (board->board[row][col] == -1) continue;

        board->board[row][col] = -1;
        mines_placed++;
    }

    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            if (board->board[i][j] == -1) continue;

            int count = 0;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < board->rows && nj >= 0 && nj < board->cols && board->board[ni][nj] == -1) {
                        count++;
                    }
                }
            }
            board->board[i][j] = count;
        }
    }
}

void reveal_cell(Board *board, int row, int col) {
    if (row < 0 || row >= board->rows || col < 0 || col >= board->cols || board->revealed[row][col]) return;

    board->revealed[row][col] = 1;

    if (board->board[row][col] == -1) return;

    if (board->board[row][col] == 0) {
        for (int di = -1; di <= 1; di++) {
            for (int dj = -1; dj <= 1; dj++) {
                reveal_cell(board, row + di, col + dj);
            }
        }
    }
}

void toggle_flag(Board *board, int row, int col) {
    if (board->revealed[row][col]) return;
    board->flags[row][col] = !board->flags[row][col];
}