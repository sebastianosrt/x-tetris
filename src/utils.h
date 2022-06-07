#include "types.h"
#include "constants.h"
#include <curses.h>

/**
 * @brief moves a tetromino one unit down
 *
 * @param t a tetromino
 */
void moveDown(Tetromino* t);

/**
 * @brief moves a tetromino one unit left
 *
 * @param t a tetromino
 */
void moveLeft(Tetromino* t);

/**
 * @brief moves a tetromino one unit right
 *
 * @param t a tetromino
 */
void moveRight(Tetromino* t);

/**
 * @brief rotates a matrix 90 degrees clockwise
 *
 * @param grid a matrix
 */
void rotateMatrix(int grid[4][4]);

/**
 * @brief rotates a tetromino 90 degrees clockwise
 *
 * @param t a tetromino
 */
void rotate(Tetromino* t);

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
 * @brief saves a tetromino into the matrix
 * 
 * @param t a tetromino
 * @param mat the matrix
 */
void saveTetromino(Tetromino* t, int mat[MAT_H][MAT_W]);

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
 * @brief prints the game fiels
 * 
 * @param mat the matrix
 * @param win the window
 */
void printField(int mat[MAT_H][MAT_W], WINDOW* win);

/**
 * @brief inverts n rows
 * 
 * @param mat the matrix
 * @param n the number of rows to invert
 */
void invertRows(int mat[MAT_H][MAT_W], int n);

/**
 * @brief moves a piece
 * 
 * @param key the direction
 * @param t the tetromino to move
 */
void moveT(int key, Tetromino* t);