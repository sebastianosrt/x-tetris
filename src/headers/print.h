#include "tetromino.h"

/**
 * @brief prints the game banner
 */
void printBanner();
/**
 * @brief prints the game over banner for single player mode
 * 
 * @param points the points accumulated during the game
 */
void printGameOver(int points);
/**
 * @brief prints the banner "player 1 wins"
 * 
 * @param points the points accumulated during the game
 */
void printGameOverPlayer1Wins(int points);
/**
 * @brief prints the banner "player 2 wins"
 * 
 * @param points the points accumulated during the game
 */
void printGameOverPlayer2Wins(int points);
/**
 * @brief prints the banner "draw"
 */
void printDraw();
/**
 * @brief prints the tetromino into the game board
 * 
 * @param t the tetromino
 * @param window the window that contains the game board
 */
void printTetromino(Tetromino t, WINDOW* window);
/**
 * @brief prints the points
 * 
 * @param pieces an array containing the 4 tetrominos
 * @param win the window that contains the game board
 * @param points the player's points
 */
void printPoints(Tetromino* pieces, WINDOW* win, int points);
/**
 * @brief prints the points
 * 
 * @param pieces an array containing the 4 tetrominos
 * @param win the window that contains the game board
 * @param p the player 1 points
 * @param p2 the player 2 points
 */
void printPointsMultiPlayer(Tetromino* pieces, WINDOW* win, int p, int p2);
/**
 * @brief prints the game field
 * 
 * @param mat the matrix
 * @param win the window
 */
void printField(int mat[MAT_H][MAT_W], WINDOW* win);