#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "board.h"

typedef struct {
    char name[20];
    int score;
} Score;

// Comparison function for qsort
int compare_scores(const void *a, const void *b) {
    return ((Score *)b)->score - ((Score *)a)->score;
}

void read_scores() {
    FILE *file = fopen("../data/scores.txt", "r");
    if (!file) {
        perror("Failed to open scores file");
        return;
    }

    Score scores[5];
    int count = 0;
    while (count < 5 && fscanf(file, "%s %d", scores[count].name, &scores[count].score) == 2) {
        count++;
    }

    fclose(file);

    qsort(scores, count, sizeof(Score), compare_scores);

    printf("Top 5 Scores:\n");
    for (int i = 0; i < count; i++) {
        printf("%s: %d\n", scores[i].name, scores[i].score);
    }
}

void save_score(const char *name, int score) {
    FILE *file = fopen("../data/scores.txt", "a");
    if (!file) {
        perror("Failed to open scores file");
        return;
    }

    fprintf(file, "%s %d\n", name, score);
    fclose(file);
}

int check_win(Board *board) {
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            if (board->board[i][j] != -1 && !board->revealed[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

int calculate_score(Board *board, int difficulty) {
    int revealed_cells = 0;
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            if (board->revealed[i][j]) {
                revealed_cells++;
            }
        }
    }
    return revealed_cells * difficulty;
}