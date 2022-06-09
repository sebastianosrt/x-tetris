/**
 * @file game.h
 * @brief this file contains the declarations of the main functions of the game
 */
#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include "print.h"

/**
 * @brief initializes the game
 */
void init();
/**
 * @brief initializes the colors
 */
void initColors();
/**
 * @brief initializes the game board
 */
void initMatrix();
/**
 * @brief initializes the tetrominos
 */
void initTetrominos();
/**
 * @brief ends the game
 */
void endgame();

/**
 * @brief shows the menu
 * 
 * @return returns the index of the selected mode
 */
int menu();
/**
 * @brief initializes a game
 */
void play();
/**
 * @brief plays a turn
 * 
 * @param mat the game board matrix
 * @param t a tetromino
 * @param pieceIndex pointer to the index of the tetromino
 * @param win the game window
 * @param pointsWin the points window
 * @return returns 1 if exit is pressed
 */
int playTurn(int mat[MAT_H][MAT_W], Tetromino* t, int* pieceIndex, WINDOW* win, WINDOW* pointsWin);
/**
 * @brief single player mode
 */
void singlePlayer();
/**
 * @brief 2 playes mode
 */
void playerVsPlayer();
/**
 * @brief player vs CPU mode
 */
void playerVsCpu();
/**
 * @brief shows the gameover screen for the single player mode
 */
void gameOver();
/**
 * @brief shows the gameover screen for the 2 player mode
 */
void gameOverMultiplayer();