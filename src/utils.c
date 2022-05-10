#include "utils.h"
#include "math.h"

void moveDown(Tetromino* t) {
    t->y++;
}

void moveLeft(Tetromino* t) {
    t->x--;
}

void moveRight(Tetromino* t) {
    t->x++;
}

void rotateMatrix(int grid[4][4]) {
    int i, j, tmp;
    // transposed matrix
    for (i = 0; i < SHAPE_BLOCKS; i++) {
        for (j = i; j < SHAPE_BLOCKS; j++) {
            tmp = grid[i][j];
            grid[i][j] = grid[j][i];
            grid[j][i] = tmp;
        }
    }
    // horizontal flip
    for (i = 0; i < SHAPE_BLOCKS; i++) {
        for (j = 0; j < SHAPE_BLOCKS/2; j++) {
            tmp = grid[i][j];
            grid[i][j] = grid[i][SHAPE_BLOCKS - 1 - j];
            grid[i][SHAPE_BLOCKS - 1 - j] = tmp;
        }
    }
}

void rotate(Tetromino* t) {
    rotateMatrix(t->grid);
}

int checkCollision(Tetromino* t, int dir, int mat[MAT_H][MAT_W]) {
    int i, j;
    int grid[4][4];
    switch(dir) {
        case KEY_LEFT:
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    if (t->grid[j][i] != 0 && (mat[t->y + j][t->x + i - 1] == -1 || mat[t->y + j][t->x + i - 1] > 0)) {
                        return 1;
                    }
                }
            }
            break;
        case KEY_RIGHT:
            for (i = 3; i >= 0; i--) {
                for (j = 3; j >= 0; j--) {
                    if (t->grid[j][i] != 0 && (mat[t->y + j][t->x + i + 1] == -1 || mat[t->y + j][t->x + i + 1] > 0)) {
                        return 1;
                    }
                }
            }
            break;
        case KEY_DOWN:
            for (i = 3; i >= 0; i--) {
                for (j = 3; j >= 0; j--) {
                    if (t->grid[j][i] != 0 && (mat[t->y + j + 1][t->x + i] == -1 || mat[t->y + j + 1][t->x + i] > 0)) {
                        return 1;
                    }
                }
            }
            break;
        case KEY_UP:
            // copy the grid
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    grid[i][j] = t->grid[i][j];
                }
            }
            // rotate it
            rotateMatrix(grid);
            // check
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    if (grid[i][j] != 0 && t->y+i < MAT_H && t->x+j < MAT_W && (mat[t->y + i][t->x + j] == -1 || mat[t->y + i][t->x + j] > 0)) {
                        return 1;
                    }
                }
            }
            break;
        default:
            break;
    }
    return 0;
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

int checkRows(int mat[MAT_H][MAT_W]) {
    int points = 0;
    int i, j;
    int mult = 0;
    for (i = 0; i < MAT_H-1; i++) {
        int complete = 1;
        for (j = 0; j < MAT_W && complete; j++)
            if (mat[i][j] == 0)
                complete = 0;
        if (complete) {
            clearRow(mat, i);
            mult++;
            switch (mult) {
                case 1:
                    points = 1;
                    break;
                case 2:
                    points = 3;
                    break;
                case 3:
                    points = 6;
                    break;            
                case 4:
                    points = 12;
                    break;
                default:
                    break;
            }
        }
    }
    return points;
}

int checkRowsMultiplayer(int mat[MAT_H][MAT_W], int mat2[MAT_H][MAT_W]) {
    int points = 0;
    int i, j;
    int mult = 0;
    for (i = 0; i < MAT_H-1; i++) {
        int complete = 1;
        for (j = 0; j < MAT_W && complete; j++)
            if (mat[i][j] == 0)
                complete = 0;
        if (complete) {
            clearRow(mat, i);
            mult++;
            switch (mult) {
                case 1:
                    points = 1;
                    break;
                case 2:
                    points = 3;
                    break;
                case 3:
                    points = 6;
                    invertRows(mat2, 3);
                    break;            
                case 4:
                    invertRows(mat2, 4);
                    points = 12;
                    break;
                default:
                    break;
            }
        }
    }
    return points;
}

void invertRows(int mat[MAT_H][MAT_W], int n) {
    int i, j;
    for (i = MAT_H-1; i >= MAT_H-1-n; i--) {
        for (j = 0; j < MAT_W; j++) {
            if (mat[i][j] > 0)
                mat[i][j] = 0;
            else if (mat[i][j] == 0)
                mat[i][j] = 1;
        }
    }
}

void clearRow(int mat[MAT_H][MAT_W], int col) {
    int i, j;
    for (i = 1; i < MAT_W-1; i++)
        mat[col][i] = 0;
    for (i = col-1; i >= 0; i--) {
        for (j = 1; j < MAT_W-1; j++) {
            mat[i+1][j] = mat[i][j];
            mat[i][j] = 0;
        }
    }    
}

int boardFull(int mat[MAT_H][MAT_W]) {
    int i;
    for (i = MAT_W / 2 - 4; i <= MAT_W / 2 + 4; i++) {
        if (mat[3][i] > 0)
            return 1;
    }
    return 0;
}

void printField(int mat[MAT_H][MAT_W], WINDOW* win) {
    int i, j;
    for (i = 0; i < MAT_H; i++) {
        for (j = 0; j < MAT_W; j++) {
            if (mat[i][j] == -1) {
                wattron(win, COLOR_PAIR(100));
                mvwaddstr(win, i, j*2, "  ");
                wattroff(win, COLOR_PAIR(100));
            }
            if (mat[i][j] > 0) {
                wattron(win, COLOR_PAIR(mat[i][j]));
                mvwaddstr(win, i, j*2, "##");
                wattroff(win, COLOR_PAIR(mat[i][j]));
            }
        }
    }
}