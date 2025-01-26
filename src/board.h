#ifndef BOARD_H
#define BOARD_H

typedef struct {
    int rows;
    int cols;
    int mines;
    int **board;
    int **revealed;
    int **flags;
} Board;

Board* create_board(int rows, int cols, int mines);
void free_board(Board *board);
void print_board(Board *board);
void place_mines(Board *board, int first_row, int first_col);
void reveal_cell(Board *board, int row, int col);
void toggle_flag(Board *board, int row, int col);

#endif // BOARD_H