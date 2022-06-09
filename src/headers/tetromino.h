/**
 * @file tetromino.h
 * @brief this file contains the Tetromino type and the declarations of the functions used to move it across the board
 */
#include <ncurses.h>
#include "constants.h"

/**
 * @struct Tetromino
 * @brief tetromino type
 */
typedef struct {
    /** @param type the tetromino's unique number */
    int type;
    /** @param color the tetromino's color */
    int color;
    /** @param stock the remaining pieces */
    int stock;
    /** @param x the number of columns from the left of the field to the start of the tetromino */
    int x;
    /** @param y the number of rows from the top of the field to the start of the tetromino */
    int y;
    /** @param grid the representation of the tetromino */
    int grid[4][4];
} Tetromino;

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
 * @brief moves a tetromino
 * 
 * @param key the direction
 * @param t the tetromino to move
 */
void moveT(int key, Tetromino* t);

/**
 * @brief rotates a tetromino 90 degrees clockwise
 *
 * @param t a tetromino
 */
void rotate(Tetromino* t);

/**
 * @brief rotates 90° clockwise a matrix
 * 
 * @param grid a matrix 
 */
void rotateMatrix(int grid[4][4]);

/**
 * @brief saves a tetromino into the matrix
 * 
 * @param t a tetromino
 * @param mat the matrix
 */
void saveTetromino(Tetromino* t, int mat[MAT_H][MAT_W]);