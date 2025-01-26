#ifndef UTILS_H
#define UTILS_H

#include "board.h"  // Include board.h to define the Board type

void read_scores();
void save_score(const char *name, int score);
int check_win(Board *board);
int calculate_score(Board *board, int difficulty);

#endif // UTILS_H