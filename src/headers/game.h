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
 * 
 * @param mat the matrix to initialize
 */
void initMatrix(int mat[MAT_H][MAT_W]);
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
 * @return returns 1 if exit is pressed
 */
int playTurn(int mat[MAT_H][MAT_W], Tetromino* t, int* pieceIndex, WINDOW* win);
/**
 * @brief plays the cpu turn
 * 
 * @param mat the game board matrix
 * @param t a tetromino
 * @param win the game window
 */
void playTurnCPU(int mat[MAT_H][MAT_W], Tetromino* t, WINDOW* win);
/**
 * @brief single player mode
 */
void singlePlayer();
/**
 * @brief 2 players mode
 * 
 * @param cpu set at 1 to select player vs cpu mode
 */
void multiPlayer(int cpu);
/**
 * @brief shows the gameover screen for the single player mode
 * 
 * @param points the player's points
 */
void gameOver(int points);
/**
 * @brief shows the gameover screen for the 2 player mode
 * 
 * @param points the playes1's points
 * @param points2 the playes2's points
 */
void gameOverMultiplayer(int points, int points2);