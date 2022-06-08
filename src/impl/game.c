/*
 * @file game.c
 * @brief this file contains the implementation of the functions declared in game.h
 */
#include "../headers/game.h"

/* static variables */
static int mat[MAT_H][MAT_W]; /* the game field matrix */
static int mat2[MAT_H][MAT_W]; /* the game field matrix for multiplayer */
static int points = 0;
static int points2 = 0;
static Tetromino* pieces;

void init() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    initColors();
    srand(time(NULL));
}

void initColors() {
    start_color();
    init_pair(100, COLOR_WHITE, COLOR_WHITE);
    init_pair(1, COLOR_CYAN, COLOR_CYAN);
    init_pair(2, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(3, COLOR_RED, COLOR_RED);
    init_pair(4, COLOR_GREEN, COLOR_GREEN);
    init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
}

void initMatrix() {
    int i, j;
    for (i = 0; i < MAT_H; i++) {
        for (j = 0; j < MAT_W; j++) {
            if (j == 0 || j == MAT_W-1 || i == MAT_H-1) {
                mat[i][j] = -1;
                mat2[i][j] = -1;
            }
            else {
                mat[i][j] = 0;
                mat2[i][j] = 0;
            }
        }
    }
}

void initTetrominos() {
    pieces =(Tetromino*) malloc(sizeof(Tetromino) * 5);

    pieces[0] =(Tetromino) {
        .stock = PIECES_STOCK,
        .color = COLOR_CYAN,
        .type = 1,
        .x = MAT_W / 2 - 2,
        .y = -1,
        .grid = {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 1, 1, 1, 1 },
            { 0, 0, 0, 0 }
        }
    };
    pieces[1] =(Tetromino) {
        .stock = PIECES_STOCK,
        .color = COLOR_YELLOW,
        .type = 2,
        .x = MAT_W / 2 - 2,
        .y = -1,
        .grid = {
            { 0, 0, 0, 0 },
            { 0, 2, 2, 0 },
            { 0, 2, 2, 0 },
            { 0, 0, 0, 0 }
        }
    };
    pieces[2] =(Tetromino) {
        .stock = PIECES_STOCK,
        .color = COLOR_RED,
        .type = 3,
        .x = MAT_W / 2 - 2,
        .y = -1,
        .grid = {
            { 0, 0, 0, 0 },
            { 3, 0, 0, 0 },
            { 3, 3, 3, 0 },
            { 0, 0, 0, 0 }
        }
    };
    pieces[3] =(Tetromino) {
        .stock = PIECES_STOCK,
        .color = COLOR_CYAN,
        .type = 4,
        .x = MAT_W / 2 - 2,
        .y = -1,
        .grid = {
            { 0, 0, 0, 0 },
            { 4, 4, 0, 0 },
            { 0, 4, 4, 0 },
            { 0, 0, 0, 0 }
        }
    };
    pieces[4] =(Tetromino) {
        .stock = PIECES_STOCK,
        .color = COLOR_MAGENTA,
        .type = 5,
        .x = MAT_W / 2 - 2,
        .y = -1,
        .grid = {
            { 0, 0, 0, 0 },
            { 0, 5, 0, 0 },
            { 5, 5, 5, 0 },
            { 0, 0, 0, 0 }
        }
    };
}

void endgame() {
    endwin();
}

int menu() {
    WINDOW* menu = newwin(8, 50, 12, 0);
    int key, highlight = 0;
    char* choices[MENU_CHOICES] = {"Single player", "Player VS Player", "Player VS CPU", "Exit"};
    int i = 0;

    printBanner();
    box(menu, 0, '+');
    keypad(menu, true);
    wrefresh(menu);

    mvwprintw(menu, 0, 3, " ! SELECT A GAME MODE ! ");
    do {
        for (i = 0; i < MENU_CHOICES; i++) {
            if (i == highlight)
                wattron(menu, A_REVERSE);
            mvwprintw(menu, i + 2, 2, "%s", choices[i]);
            wattroff(menu, A_REVERSE);
        }
        key = wgetch(menu);
        switch(key) {
            case KEY_UP:
                highlight--;
                if (highlight == -1)
                    highlight = 3;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == MENU_CHOICES)
                    highlight = 0;
                break;
            default:
                break;
        }

    } while(key != ENTER);

    return highlight;
}

void play() {
    clearScreen();
    initTetrominos();
    initMatrix();
}

int playTurn(int mat[MAT_H][MAT_W], Tetromino* t, int* pieceIndex, WINDOW* win, WINDOW* pointsWin) {
    int key;
    *t = pieces[*pieceIndex];
    wtimeout(win, -1);

    refreshWindow(win, *t, mat);
    do {
        while (t->stock == 0) {
            (*pieceIndex)++;
            if (*pieceIndex > 4)
                *pieceIndex = 0;
            *t = pieces[*pieceIndex];
        }
        refreshWindow(win, *t, mat);
        key = wgetch(win);

        if (key == KEY_TAB) {
            do {
                (*pieceIndex)++;
                if (*pieceIndex > 4)
                    *pieceIndex = 0;
                *t = pieces[*pieceIndex];
            } while(t->stock == 0);
            refreshWindow(win, *t, mat);
        }
    } while(key == KEY_TAB);
    if (key != 'q') {
        pieces[*pieceIndex].stock--;
        do {
            moveDown(t);
            wtimeout(win, 100);
            key = wgetch(win);
            if (!checkCollision(t, key, mat))
                moveT(key, t);
            refreshWindow(win, *t, mat);
        } while(!checkCollision(t, KEY_DOWN, mat) && key != 'q');
        saveTetromino(t, mat);
    }

    return key == 'q' ? 1 : 0;
}

void singlePlayer() {
    WINDOW* gameWindow = newwin(MAT_H*2, MAT_W*2, 0, 0);
    WINDOW* pointsWindow = newwin(50, 50, 0, MAT_W*2);
    int exit = 0;
    int i = 0, j = 0;
    int pieceIndex = 0;
    Tetromino t;

    points = 0;
    keypad(gameWindow, true);
    do {
        points += checkRows(mat);
        printPoints(pieces, pointsWindow, points);
        exit = playTurn(mat, &t, &pieceIndex, gameWindow, pointsWindow);
    } while(!boardFull(mat) && tetrominosStock(pieces) > 0 && !exit);
    clearWindow(gameWindow);
    clearWindow(pointsWindow);
    gameOver();
}

void playerVsPlayer() {
    WINDOW* gameWindow = newwin(MAT_H*2, MAT_W*2, 0, 0);
    WINDOW* pointsWindow = newwin(50, 45, 0, MAT_W*2);
    WINDOW* gameWindow2 = newwin(MAT_H*2, MAT_W*2, 0, MAT_W*2 + 48);
    int exit = 0;
    int i = 0, j = 0;
    int pieceIndex1 = 0, pieceIndex2 = 0;
    Tetromino t1, t2;
    int turn = 0;

    for (i = 0; i < 5; i++)
        pieces[i].stock = PIECES_STOCK*2;
    points = 0;
    points2 = 0;

    keypad(gameWindow, true);
    keypad(gameWindow2, true);

    refreshWindow(gameWindow, t1, mat);
    refreshWindow(gameWindow2, t2, mat2);
    printPointsMultiPlayer(pieces, pointsWindow, points, points2);
    do {
        if (!turn) {
            exit = playTurn(mat, &t1, &pieceIndex1, gameWindow, pointsWindow);
            printPointsMultiPlayer(pieces, pointsWindow, points, points2);
            points += checkRowsMultiplayer(mat, mat2);
            turn = 1;
        } else {
            exit = playTurn(mat2, &t2, &pieceIndex2, gameWindow2, pointsWindow);
            printPointsMultiPlayer(pieces, pointsWindow, points, points2);
            points2 += checkRowsMultiplayer(mat2, mat);
            turn = 0;
        }
    } while(!boardFull(mat) && !boardFull(mat2) && tetrominosStock(pieces) > 0 && !exit);
    clearWindow(gameWindow);
    clearWindow(gameWindow2);
    clearWindow(pointsWindow);
    gameOverMultiplayer();
}

void playerVsCpu() {
    WINDOW* gameWindow = newwin(MAT_H*2, MAT_W*2, 0, 0);
    WINDOW* pointsWindow = newwin(50, 45, 0, MAT_W*2);
    WINDOW* gameWindow2 = newwin(MAT_H*2, MAT_W*2, 0, MAT_W*2 + 48);
    int key;
    int i = 0, j = 0;
    int pieceIndex1 = 0, pieceIndex2 = 0;
    Tetromino t1, t2;
    int turn = 0;

    for (i = 0; i < 5; i++)
        pieces[i].stock = PIECES_STOCK*2;
    points = 0;
    points2 = 0;

    keypad(gameWindow, true);
    keypad(gameWindow2, true);

    refreshWindow(gameWindow, t1, mat);
    refreshWindow(gameWindow2, t2, mat2);
    do {
        if (!turn) {
            t1 = pieces[pieceIndex1];
            wtimeout(gameWindow, -1);

            do {
                while (t1.stock == 0) {
                    pieceIndex1++;
                    if (pieceIndex1 > 4)
                        pieceIndex1 = 0;
                    t1 = pieces[pieceIndex1];
                }
                refreshWindow(gameWindow, t1, mat);
                printPointsMultiPlayer(pieces, pointsWindow, points, points2);
                key = wgetch(gameWindow);

                if (key == KEY_TAB) {
                    do {
                        pieceIndex1++;
                        if (pieceIndex1 > 4)
                            pieceIndex1 = 0;
                        t1 = pieces[pieceIndex1];
                    } while(t1.stock == 0);
                }
            } while(key == KEY_TAB);
            pieces[pieceIndex1].stock--;

            do {
                moveDown(&t1);
                wtimeout(gameWindow, 100);
                key = wgetch(gameWindow);
                if (!checkCollision(&t1, key, mat))
                    moveT(key, &t1);
                refreshWindow(gameWindow, t1, mat);
            } while(!checkCollision(&t1, KEY_DOWN, mat) && key != 'q');
            saveTetromino(&t1, mat);
            points += checkRowsMultiplayer(mat, mat2);
            printPointsMultiPlayer(pieces, pointsWindow, points, points2);

            turn = 1;
        } else {
            do {
                pieceIndex2 = rand() % 4;
            } while (pieces[pieceIndex2].stock == 0);
            t2 = pieces[pieceIndex2];
            pieces[pieceIndex2].stock--;            
            refreshWindow(gameWindow2, t2, mat2);
            printPointsMultiPlayer(pieces, pointsWindow, points, points2);
            int dirs[3] = {KEY_LEFT, KEY_RIGHT, KEY_UP};

            do {
                moveDown(&t2);
                key = dirs[rand() % 3];
                if (!checkCollision(&t2, key, mat2))
                    moveT(key, &t2);
                refreshWindow(gameWindow2, t2, mat2);
            } while(!checkCollision(&t2, KEY_DOWN, mat2) && key != 'q');
            saveTetromino(&t2, mat2);
            points2 += checkRowsMultiplayer(mat2, mat);
            printPointsMultiPlayer(pieces, pointsWindow, points, points2);
            
            turn = 0;
        }
    } while(!boardFull(mat) && !boardFull(mat2) && tetrominosStock(pieces) > 0 && key != 'q');
    clearWindow(gameWindow);
    clearWindow(gameWindow2);
    clearWindow(pointsWindow);
    gameOverMultiplayer();
}

void gameOver() {
    WINDOW* win = newwin(1, 1, 20, 20);
    int key = 0;
    printGameOver(points);
    keypad(win, true);
    do {
        key = wgetch(win);
    } while(key == 0);
    clearScreen();
}

void gameOverMultiplayer() {
    WINDOW* win = newwin(1, 1, 20, 20);
    int key = 0;
    
    keypad(win, true);
    if (points > points2)
        printGameOverPlayer1Wins(points);
    else if (points2 > points)
        printGameOverPlayer2Wins(points2);
    else
        printDraw();
    do {
        key = wgetch(win);
    } while(key == 0);
    clearScreen();
}