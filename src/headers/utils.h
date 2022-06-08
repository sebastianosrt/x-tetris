#include "tetromino.h"

/*
 * @file utils.h
 * @brief this file contains the definitions of the utility functions
 */

/**
 * @brief checks if a tetromino can move or rotate
 *
 * @param t a tetromino
 * @param dir the piece's direction
 * @param mat the game's matrix
 * @return returns 0 if there is no collision, else returns 1
 */
int checkCollision(Tetromino* t, int dir, int mat[MAT_H][MAT_W]);

/**
 * @brief checks if a row is complete and clears it
 * 
 * @param mat the matrix
 * @return points
 */
int checkRows(int mat[MAT_H][MAT_W]);

/**
 * @brief checks if a row is complete and clears it
 * 
 * @param mat the matrix
 * @return points
 */
int checkRowsMultiplayer(int mat[MAT_H][MAT_W], int mat2[MAT_H][MAT_W]);

/**
 * @brief clears a row and shifts down the above ones
 * 
 * @param mat the matrix
 * @param col the column of the row to clear
 */
void clearRow(int mat[MAT_H][MAT_W], int col);

/**
 * @brief checks if it's possible to add a new piece
 * 
 * @param mat the matrix
 * @return 1 if the board is full, else 0
 */
int boardFull();

/**
 * @brief inverts n rows
 * 
 * @param mat the matrix
 * @param n the number of rows to invert
 */
void invertRows(int mat[MAT_H][MAT_W], int n);

/**
 * @brief clears and refreshes the screen
 */
void clearScreen();

/**
 * @brief refreshes a game window
 * 
 * @param win the window
 * @param t a tetromino
 * @param mat the matrix
 */
void refreshWindow(WINDOW* window, Tetromino t, int mat[MAT_H][MAT_W]);

/**
 * @brief returns the total number of tetrominos
 * 
 * @param pieces an array containing the 4 tetrominos
 */
int tetrominosStock(Tetromino* pieces);