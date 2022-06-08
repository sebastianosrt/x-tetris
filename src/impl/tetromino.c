/*
 * @file tetromino.c
 * @brief implementation of the functions definited in tetromino.h
 */
#include "../headers/tetromino.h"

void moveDown(Tetromino* t) {
    t->y++;
}

void moveLeft(Tetromino* t) {
    t->x--;
}

void moveRight(Tetromino* t) {
    t->x++;
}

void moveT(int key, Tetromino* t) {
    switch(key) {
        case KEY_LEFT:
            moveLeft(t);
            break;
        case KEY_RIGHT:
            moveRight(t);
            break;
        case KEY_UP:
            rotate(t);
            break;
        default:
            break;
    }
}

void rotate(Tetromino* t) {
    rotateMatrix(t->grid);
}

void rotateMatrix(int grid[4][4]) {
    int i, j, tmp;
    for (i = 0; i < SHAPE_BLOCKS; i++) {
        for (j = i; j < SHAPE_BLOCKS; j++) {
            tmp = grid[i][j];
            grid[i][j] = grid[j][i];
            grid[j][i] = tmp;
        }
    }
    for (i = 0; i < SHAPE_BLOCKS; i++) {
        for (j = 0; j < SHAPE_BLOCKS/2; j++) {
            tmp = grid[i][j];
            grid[i][j] = grid[i][SHAPE_BLOCKS - 1 - j];
            grid[i][SHAPE_BLOCKS - 1 - j] = tmp;
        }
    }
}

void saveTetromino(Tetromino* t, int mat[MAT_H][MAT_W]) {
    int i, j;
    for (i = 0; i < SHAPE_BLOCKS; i++) {
        for (j = 0; j < SHAPE_BLOCKS; j++) {
            if (t->grid[i][j] != 0) {
                mat[t->y+i][t->x+j] = t->grid[i][j];
            }
        }
    }
}