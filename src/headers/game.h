/*
 * @file game.h
 * @brief this file contains the function declarations for the game
 */
#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include "print.h"

/*
 * @brief initializes the game
 */
void init();
/*
 * @brief initializes the colors
 */
void initColors();
/*
 * @brief initializes the game board
 */
void initMatrix();
/*
 * @brief initializes the tetrominos
 */
void initTetrominos();
/*
 * @brief ends the game
 */
void endgame();

/*
 * @brief shows the menu
 */
int menu();
/*
 * @brief initializes a game
 */
void play();
/*
 * @brief single player mode
 */
void singlePlayer();
/*
 * @brief 2 playes mode
 */
void playerVsPlayer();
/*
 * @brief player vs CPU mode
 */
void playerVsCpu();
/*
 * @brief shows the gameover screen for the single player mode
 */
void gameOver();
/*
 * @brief shows the gameover screen for the 2 player mode
 */
void gameOverMultiplayer();