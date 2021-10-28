#include "utils.h"

int calcPieceHeight(Tetromino t) {
    int h = 0, i = 0;
    for (i = 0; i < SHAPE_COORDS_COUNT; i++)
        if (t.shape[i].y > h)
            h = t.shape[i].y;
    return h+1;
}

int calcPieceWidth(Tetromino t) {
    int w = 0, i = 0;
    for (i = 0; i < SHAPE_COORDS_COUNT; i++)
        if (t.shape[i].x > w)
            w = t.shape[i].x;
    return w+1;
}