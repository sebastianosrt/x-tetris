struct tetromino {
    int color;
    int type;
    int stock;
    int x;
    int y;
    int grid[4][4];
};
typedef struct tetromino Tetromino;