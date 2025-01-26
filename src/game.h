#ifndef GAME_H
#define GAME_H

void run_game(int difficulty);
int run_from_file(const char *filename);
void run_game_custom(int rows, int cols, int mines);

#endif // GAME_H
