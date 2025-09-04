# Minesweeper Project

A C implementation of the classic Minesweeper game with customizable boards, difficulty levels, file-based game loading, and high score tracking. Includes unit tests for core functionality.

## Features

- Select difficulty level or create a custom board with a chosen number of rows, columns, and mines.

- Display and interact with the board.

- Place and remove flags on cells.

- Automatic mine placement, avoiding the first revealed cell.

- Save and read top scores from a file.

- Load a game from a file, including board dimensions and a sequence of commands.

- Unit tests to verify core functionality.

## Functions Overview
### Game Functions

void run_game_custom(int rows, int cols, int mines)
Runs the game with custom board dimensions and number of mines.

int run_from_file(const char *filename)
Loads a game from a file, reading board dimensions, mine count, and a sequence of commands.

### Utility Functions (utils.c / utils.h)

void read_scores()
Reads and displays the top 5 scores from scores.txt.

void save_score(const char *name, int score)
Saves a player’s score to scores.txt.

int check_win(Board *board)
Checks if the player has won by revealing all non-mine cells.

int calculate_score(Board *board, int difficulty)
Calculates the player’s score based on revealed cells and difficulty level.

## Test Descriptions and Results

test_create_board()

Description: Creates a 3x3 board with 1 mine and verifies initialization.

Expected Result: Test passed: create_board

test_place_mines()

Description: Places 1 mine on a 3x3 board, avoiding the first cell.

Expected Result: Test passed: place_mines

test_reveal_cell()

Description: Reveals the first cell on a 3x3 board with 1 mine.

Expected Result: Test passed: reveal_cell

test_toggle_flag()

Description: Places and removes a flag on a cell.

Expected Result: Test passed: toggle_flag

## Summary

- All implemented functionalities:

- Difficulty selection

- Board creation and display

- Mine placement

- Cell reveal and flagging

- Score management and saving to file

- Loading game from a file

- Challenges and Solutions:

- Makefile indentation errors: Replaced spaces with tabs in Vim to fix missing separator errors.

- Dynamic column alignment for boards >9 columns: Used maximum digit calculation and %*d formatting in print_board.

## Conclusions:

- Modular design improves maintainability and extendibility.

- Unit tests ensure key functions work correctly.

- Dynamic alignment ensures boards of any size are displayed neatly.
