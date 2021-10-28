struct coord {
    int x;
    int y;
};
typedef struct coord Coord;

struct tetromino {
    int color;
    int type;
    int stock;
    Coord shape[SHAPE_COORDS_COUNT];
};
typedef struct tetromino Tetromino;