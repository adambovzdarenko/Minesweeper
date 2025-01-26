#include <stdio.h>
#include "board.h"
#include "utils.h"

void test_create_board() {
    Board *board = create_board(3, 3, 1);
    if (board == NULL) {
        printf("Test failed: create_board returned NULL\n");
        return;
    }

    if (board->rows != 3 || board->cols != 3 || board->mines != 1) {
        printf("Test failed: board dimensions or mine count incorrect\n");
        free_board(board);
        return;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board->board[i][j] != 0 || board->revealed[i][j] != 0 || board->flags[i][j] != 0) {
                printf("Test failed: board initialization incorrect\n");
                free_board(board);
                return;
            }
        }
    }

    free_board(board);
    printf("Test passed: create_board\n");
}

void test_place_mines() {
    Board *board = create_board(3, 3, 1);
    place_mines(board, 0, 0);

    int mine_count = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board->board[i][j] == -1) {
                mine_count++;
            }
        }
    }

    if (mine_count != 1) {
        printf("Test failed: mine count incorrect\n");
        free_board(board);
        return;
    }

    free_board(board);
    printf("Test passed: place_mines\n");
}

void test_reveal_cell() {
    Board *board = create_board(3, 3, 1);
    place_mines(board, 0, 0);

    reveal_cell(board, 0, 0);

    if (!board->revealed[0][0]) {
        printf("Test failed: cell not revealed\n");
        free_board(board);
        return;
    }

    free_board(board);
    printf("Test passed: reveal_cell\n");
}

void test_toggle_flag() {
    Board *board = create_board(3, 3, 1);

    toggle_flag(board, 0, 0);
    if (!board->flags[0][0]) {
        printf("Test failed: flag not toggled\n");
        free_board(board);
        return;
    }

    toggle_flag(board, 0, 0);
    if (board->flags[0][0]) {
        printf("Test failed: flag not untoggled\n");
        free_board(board);
        return;
    }

    free_board(board);
    printf("Test passed: toggle_flag\n");
}

void run_tests() {
    test_create_board();
    test_place_mines();
    test_reveal_cell();
    test_toggle_flag();
    // Add more tests here
}

int main() {
    run_tests();
    return 0;
}