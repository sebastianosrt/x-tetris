/**
 * @file main.c
 * @brief 
 * @author Sebastiano Sartor
 * @mainpage X-Tetris
 * @section Intro
 * X-Tetris game implementantion in C
 * @section Dependencies
 *
 * <ul>
 *      <li>MinGW (for windows users)</li>
 *      <li>ncurses <a href="https://e-l.unifi.it/pluginfile.php/805205/mod_resource/content/0/ncurses%20installation%20-%20en.pdf">tutorial</a></li>
 * </ul>
 *
 * @section Installation
 * <ol>
 *      <li>
 *          Download the repository
 *          <br />
 *          <code>git clone https://github.com/Filibertoo/tetris</code>
 *      </li>
 *      <li>
 *          Install every dependecies
 *      </li>
 *      <li>
 *          Go into the repository folder and then change directory
 *          <br />
 *          <code>cd src</code>
 *      </li>
 *      <li>
 *          Compile and run the game
 *          <br />
 *          <code>gcc main.c -o main -lncurses -ansi && ./main</code>
 *      </li>
 * </ol>
 *
 * @section Commands
 * Here the complete list of commands for the game. First of all you can select the game mode moving your selection with <code>W</code> key (up) or <code>D</code> key (down) and confirm with <code>ENTER</code>
 * <br />
 * When u join the game, here is a list of complete commands:
 *
 * <ul>
 *      <li><code>ESC</code>: exit from the gamemode select or close the "game"</li>
 *      <li><code>W</code>: rotate tetramino</li>
 *      <li><code>A</code>: move left</li>
 *      <li><code>D</code>: move rigth</li>
 *      <li><code>SPACE</code>: switch tetramino</li>
 *      <li><code>ENTER</code>: insert tetramino in the map</li>
 * </ul>
 *
 * If you selected multiplayer, the commands for the other player are the <b>same</b>.
 */

// libs
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include "constants.h"
#include "types.h"
#include "utils.c"

// function declarations
void init();
void printBanner();
void printGameOver();
int menu();
void clearScreen();
void singlePlayer();
void initTetrominos();
void initMatrix();
void initColors();
void printTetromino(Tetromino t, WINDOW* window);
void play();
int tetrominosStock();
void printPoints(WINDOW* win);
void printPointsMultiPlayer(WINDOW* win);
void gameOver();
void gameOverMultiplayer();
void printGameOverPlayer1Wins();
void printGameOverPlayer2Wins();
void draw();
/**
 * @brief refreshes a game window
 * 
 * @param win the window
 * @param t a tetromino
 * @param mat the matrix
 */
void refreshWindow(WINDOW* window, Tetromino t, int mat[MAT_H][MAT_W]);

void playerVsPlayer();
void playerVsCpu();

// static variables
static int win_width, win_height; // the window dimensions
static int mat[MAT_H][MAT_W]; // the game field matrix
static int mat2[MAT_H][MAT_W]; // the game field matrix for multiplayer
static int points = 0;
static int points2 = 0;
static Tetromino* pieces;

// game
int main(int argc, char** argv) {
    int mod = 0;

    init();

    do {
        mod = menu(); // get the game mode
        clearScreen();
        switch (mod) { // load the game mode
            case 0:
                singlePlayer();
                break;
            case 1:
                playerVsPlayer();
                break;
            case 2:
                playerVsCpu();
                break;
            default:
                break;
        }
    } while(true);

    endwin();
 
    return 0;
}

// function definitions
void init() {
    initscr();
    cbreak();
    noecho();
    getmaxyx(stdscr, win_width, win_height); // get the rows and columns of the window
    curs_set(0);
    initColors();
}

void printBanner() {
    mvprintw(0, 0, "@@@  @@@             @@@@@@@  @@@@@@@@  @@@@@@@  @@@@@@@   @@@   @@@@@@   \n");
    mvprintw(1, 0, "@@@  @@@             @@@@@@@  @@@@@@@@  @@@@@@@  @@@@@@@@  @@@  @@@@@@@   \n");
    mvprintw(2, 0, "@@!  !@@               @@!    @@!         @@!    @@!  @@@  @@!  !@@       \n");
    mvprintw(3, 0, "!@!  @!!               !@!    !@!         !@!    !@!  @!@  !@!  !@!       \n");
    mvprintw(4, 0, " !@@!@!   @!@!@!@!@    @!!    @!!!:!      @!!    @!@!!@!   !!@  !!@@!!    \n");
    mvprintw(5, 0, "  @!!!    !!!@!@!!!    !!!    !!!!!:      !!!    !!@!@!    !!!   !!@!!!   \n");
    mvprintw(6, 0, " !: :!!                !!:    !!:         !!:    !!: :!!   !!:       !:!  \n");
    mvprintw(7, 0, ":!:  !:!               :!:    :!:         :!:    :!:  !:!  :!:      !:!   \n");
    mvprintw(8, 0, " ::  :::                ::     :: ::::     ::    ::   :::   ::  :::: ::   \n");
    mvprintw(9, 0, " :   ::                 :     : :: ::      :      :   : :  :    :: : :    \n");
    refresh();
}

void printGameOver() {
    char str[12];
    mvprintw(0, 0, " @@@@@@@@   @@@@@@   @@@@@@@@@@   @@@@@@@@      @@@@@@   @@@  @@@  @@@@@@@@  @@@@@@@ ");
    mvprintw(1, 0, "@@@@@@@@@  @@@@@@@@  @@@@@@@@@@@  @@@@@@@@     @@@@@@@@  @@@  @@@  @@@@@@@@  @@@@@@@@");
    mvprintw(2, 0, "!@!        !@!  @!@  !@! !@! !@!  !@!          !@!  @!@  !@!  @!@  !@!       !@!  @!@");
    mvprintw(3, 0, "!@! @!@!@  @!@!@!@!  @!! !!@ @!@  @!!!:!       @!@  !@!  @!@  !@!  @!!!:!    @!@!!@! ");
    mvprintw(4, 0, "!!! !!@!!  !!!@!!!!  !@!   ! !@!  !!!!!:       !@!  !!!  !@!  !!!  !!!!!:    !!@!@!  ");
    mvprintw(5, 0, ":!!   !!:  !!:  !!!  !!:     !!:  !!:          !!:  !!!  :!:  !!:  !!:       !!: :!! ");
    mvprintw(6, 0, ":!:   !::  :!:  !:!  :!:     :!:  :!:          :!:  !:!   ::!!:!   :!:       :!:  !:!");
    mvprintw(7, 0, " ::: ::::  ::   :::  :::     ::    :: ::::     ::::: ::    ::::     :: ::::  ::   :::");
    mvprintw(8, 0, " :: :: :    :   : :   :      :    : :: ::       : :  :      :      : :: ::    :   : :");
    
    snprintf(str, 12, "POINTS: %d", points);
    mvprintw(10, 0, str);
    mvprintw(12, 0, "PRESS ANY KEY TO CONTINUE");
    refresh();
}
                                                                                                                
void printGameOverPlayer1Wins() {
    char str[12];
    mvprintw(0, 0, "@@@@@@@   @@@        @@@@@@   @@@ @@@  @@@@@@@@  @@@@@@@        @@@     @@@  @@@  @@@  @@@  @@@  @@@   @@@@@@   ");
    mvprintw(1, 0, "@@@@@@@@  @@@       @@@@@@@@  @@@ @@@  @@@@@@@@  @@@@@@@@      @@@@     @@@  @@@  @@@  @@@  @@@@ @@@  @@@@@@@   ");
    mvprintw(2, 0, "@@!  @@@  @@!       @@!  @@@  @@! !@@  @@!       @@!  @@@     @@@!!     @@!  @@!  @@!  @@!  @@!@!@@@  !@@       ");
    mvprintw(3, 0, "!@!  @!@  !@!       !@!  @!@  !@! @!!  !@!       !@!  @!@       !@!     !@!  !@!  !@!  !@!  !@!!@!@!  !@!       ");
    mvprintw(4, 0, "@!@@!@!   @!!       @!@!@!@!   !@!@!   @!!!:!    @!@!!@!        @!@     @!!  !!@  @!@  !!@  @!@ !!@!  !!@@!!    ");
    mvprintw(5, 0, "!!@!!!    !!!       !!!@!!!!    @!!!   !!!!!:    !!@!@!         !@!     !@!  !!!  !@!  !!!  !@!  !!!   !!@!!!   ");
    mvprintw(6, 0, "!!:       !!:       !!:  !!!    !!:    !!:       !!: :!!        !!:     !!:  !!:  !!:  !!:  !!:  !!!       !:!  ");
    mvprintw(7, 0, ":!:        :!:      :!:  !:!    :!:    :!:       :!:  !:!       :!:     :!:  :!:  :!:  :!:  :!:  !:!      !:!   ");
    mvprintw(8, 0, " ::        :: ::::  ::   :::     ::     :: ::::  ::   :::       :::      :::: :: :::    ::   ::   ::  :::: ::   ");
    mvprintw(9, 0, " :        : :: : :   :   : :     :     : :: ::    :   : :        ::       :: :  : :    :    ::    :   :: : :    ");
    
    snprintf(str, 12, "POINTS: %d", points);
    mvprintw(11, 0, str);
    mvprintw(13, 0, "PRESS ANY KEY TO CONTINUE");
    refresh();
}

void printGameOverPlayer2Wins() {
    char str[12];
    mvprintw(0, 0, "@@@@@@@   @@@        @@@@@@   @@@ @@@  @@@@@@@@  @@@@@@@       @@@@@@      @@@  @@@  @@@  @@@  @@@  @@@   @@@@@@   ");
    mvprintw(1, 0, "@@@@@@@@  @@@       @@@@@@@@  @@@ @@@  @@@@@@@@  @@@@@@@@     @@@@@@@@     @@@  @@@  @@@  @@@  @@@@ @@@  @@@@@@@   ");
    mvprintw(2, 0, "@@!  @@@  @@!       @@!  @@@  @@! !@@  @@!       @@!  @@@          @@@     @@!  @@!  @@!  @@!  @@!@!@@@  !@@       ");
    mvprintw(3, 0, "!@!  @!@  !@!       !@!  @!@  !@! @!!  !@!       !@!  @!@         @!@      !@!  !@!  !@!  !@!  !@!!@!@!  !@!       ");
    mvprintw(4, 0, "@!@@!@!   @!!       @!@!@!@!   !@!@!   @!!!:!    @!@!!@!         !!@       @!!  !!@  @!@  !!@  @!@ !!@!  !!@@!!    ");
    mvprintw(5, 0, "!!@!!!    !!!       !!!@!!!!    @!!!   !!!!!:    !!@!@!         !!:        !@!  !!!  !@!  !!!  !@!  !!!   !!@!!!   ");
    mvprintw(6, 0, "!!:       !!:       !!:  !!!    !!:    !!:       !!: :!!       !:!         !!:  !!:  !!:  !!:  !!:  !!!       !:!  ");
    mvprintw(7, 0, ":!:        :!:      :!:  !:!    :!:    :!:       :!:  !:!     :!:          :!:  :!:  :!:  :!:  :!:  !:!      !:!   ");
    mvprintw(8, 0, " ::        :: ::::  ::   :::     ::     :: ::::  ::   :::     :: :::::      :::: :: :::    ::   ::   ::  :::: ::   ");
    mvprintw(9, 0, " :        : :: : :   :   : :     :     : :: ::    :   : :     :: : :::       :: :  : :    :    ::    :   :: : :    ");
    
    snprintf(str, 12, "POINTS: %d", points2);
    mvprintw(11, 0, str);
    mvprintw(13, 0, "PRESS ANY KEY TO CONTINUE");
    refresh();
}

void draw() {
    mvprintw(0, 0, "@@@@@@@   @@@@@@@    @@@@@@   @@@  @@@  @@@  ");
    mvprintw(1, 0, "@@@@@@@@  @@@@@@@@  @@@@@@@@  @@@  @@@  @@@  ");
    mvprintw(2, 0, "@@!  @@@  @@!  @@@  @@!  @@@  @@!  @@!  @@!  ");
    mvprintw(3, 0, "!@!  @!@  !@!  @!@  !@!  @!@  !@!  !@!  !@!  ");
    mvprintw(4, 0, "@!@  !@!  @!@!!@!   @!@!@!@!  @!!  !!@  @!@  ");
    mvprintw(5, 0, "!@!  !!!  !!@!@!    !!!@!!!!  !@!  !!!  !@!  ");
    mvprintw(6, 0, "!!:  !!!  !!: :!!   !!:  !!!  !!:  !!:  !!:  ");
    mvprintw(7, 0, ":!:  !:!  :!:  !:!  :!:  !:!  :!:  :!:  :!:  ");
    mvprintw(8, 0, " :::: ::  ::   :::  ::   :::   :::: :: :::   ");
    mvprintw(9, 0, ":: :  :    :   : :   :   : :    :: :  : :    ");    
    mvprintw(11, 0, "PRESS ANY KEY TO CONTINUE");
    refresh();
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

void initColors() {
    start_color();
    init_pair(100, COLOR_WHITE, COLOR_WHITE);
    init_pair(1, COLOR_CYAN, COLOR_CYAN);
    init_pair(2, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(3, COLOR_RED, COLOR_RED);
    init_pair(4, COLOR_GREEN, COLOR_GREEN);
    init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
}

int menu() {
    WINDOW* menu = newwin(7, win_width, 12, 0);
    int key, highlight = 0;
    char* choices[MENU_CHOICES] = {"Single player", "Player VS Player", "Player VS CPU"};
    int i = 0;

    printBanner();
    box(menu, 0, '+'); // draw the menu box
    keypad(menu, true);
    wrefresh(menu);

    mvwprintw(menu, 0, 3, " ! SELECT A GAME MODE ! ");
    do {
        // print the choices
        for (i = 0; i < MENU_CHOICES; i++) {
            if (i == highlight)
                wattron(menu, A_REVERSE);
            mvwprintw(menu, i + 2, 2, "%s", choices[i]);
            wattroff(menu, A_REVERSE);
        }
        key = wgetch(menu); // get the key
        switch(key) {
            case KEY_UP:
                highlight--;
                if (highlight == -1)
                    highlight = 2;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == 3)
                    highlight = 0;
                break;
            default:
                break;
        }

    } while(key != ENTER);

    return highlight;
}

void clearScreen() {
    clear();
    refresh();
}

void singlePlayer() {
    clearScreen();
    initTetrominos();
    initMatrix();
    play();
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

void refreshWindow(WINDOW* window, Tetromino t, int mat[MAT_H][MAT_W]) {
    wclear(window);
    printField(mat, window);
    printTetromino(t, window);
    wrefresh(window);
}

void printTetromino(Tetromino t, WINDOW* window) {
    int i, j;

    wattron(window, COLOR_PAIR(t.type));
    for (i = 0; i < SHAPE_BLOCKS; i++) {
        for (j = 0; j < SHAPE_BLOCKS; j++) {
            if (t.grid[i][j] > 0) {
                mvwaddstr(window, t.y + i, (t.x + j)*2, "##");
            }
        }
    }
    wattroff(window, COLOR_PAIR(t.type)); 
}

int tetrominosStock() {
    return pieces[0].stock + pieces[1].stock + pieces[2].stock + pieces[3].stock + pieces[4].stock;
}

void printPoints(WINDOW* win) {
    int i, j, k, x = 3;
    char str[15];

    snprintf(str, 15, "Points: %d", points);
    mvwaddstr(win, 0, x, str);
    mvwaddstr(win, 2, x, "Commands:");
    mvwaddstr(win, 3, x+1, "LEFT/RIGHT: move the piece horizontally");
    mvwaddstr(win, 4, x+1, "UP: rotate the piece");
    mvwaddstr(win, 5, x+1, "TAB: change piece");
    mvwaddstr(win, 6, x+1, "Q: exit");
    
    mvwaddstr(win, 8, x, "Stocks:");

    for (k = 0; k < 5; k++) {
        wattron(win, COLOR_PAIR(pieces[k].type));
        for (i = 0; i < SHAPE_BLOCKS; i++) {
            for (j = 0; j < SHAPE_BLOCKS; j++) {
                if (pieces[k].grid[i][j] > 0) {
                    mvwaddstr(win, i+8+k*3, j*2+4, "##");
                }
            }
        }
        wattroff(win, COLOR_PAIR(pieces[k].type));
        snprintf(str, 15, "%d pieces left", pieces[k].stock);
        mvwaddstr(win, 8+k*3+2, 14, str);

    }

    wrefresh(win);
}

void printPointsMultiPlayer(WINDOW* win) {
    int i, j, k, x = 4;
    char str[15];

    mvwaddstr(win, 0, x, "POINTS:");
    snprintf(str, 15, "  %d : %d", points, points2);
    mvwaddstr(win, 1, x, str);

    mvwaddstr(win, 3, x, "Commands:");
    mvwaddstr(win, 4, x+1, "LEFT/RIGHT: move the piece horizontally");
    mvwaddstr(win, 5, x+1, "UP: rotate the piece");
    mvwaddstr(win, 6, x+1, "TAB: change piece");
    mvwaddstr(win, 7, x+1, "Q: exit");
    
    mvwaddstr(win, 9, x, "Stocks:");

    for (k = 0; k < 5; k++) {
        wattron(win, COLOR_PAIR(pieces[k].type));
        for (i = 0; i < SHAPE_BLOCKS; i++) {
            for (j = 0; j < SHAPE_BLOCKS; j++) {
                if (pieces[k].grid[i][j] > 0) {
                    mvwaddstr(win, i+9+k*3, j*2+4, "##");
                }
            }
        }
        wattroff(win, COLOR_PAIR(pieces[k].type));
        snprintf(str, 15, "%d pieces left", pieces[k].stock);
        mvwaddstr(win, 9+k*3+2, 14, str);
    }

    wrefresh(win);
}

void gameOver() {
    WINDOW* win = newwin(1, 1, 20, 20);
    int key = 0;
    printGameOver();
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
        printGameOverPlayer1Wins();
    else if (points2 > points)
        printGameOverPlayer2Wins();
    else
        draw();
    do {
        key = wgetch(win);
    } while(key == 0);
    clearScreen();
}

void play() {
    WINDOW* gameWindow = newwin(MAT_H*2, MAT_W*2, 0, 0);
    WINDOW* pointsWindow = newwin(50, 50, 0, MAT_W*2);
    int key;
    int i = 0, j = 0;
    int pieceIndex = 0;
    Tetromino t;

    points = 0;
    keypad(gameWindow, true);
    do {
        t = pieces[pieceIndex];
        wtimeout(gameWindow, -1);

        do {
            while (t.stock == 0) {
                pieceIndex++;
                if (pieceIndex > 4)
                    pieceIndex = 0;
                t = pieces[pieceIndex];
            }
            refreshWindow(gameWindow, t, mat);
            printPoints(pointsWindow);
            key = wgetch(gameWindow);

            if (key == KEY_TAB) {
                do {
                    pieceIndex++;
                    if (pieceIndex > 4)
                        pieceIndex = 0;
                    t = pieces[pieceIndex];
                } while(t.stock == 0);
            }
        } while(key == KEY_TAB);
        pieces[pieceIndex].stock--;

        do {
            moveDown(&t);
            wtimeout(gameWindow, 100);
            key = wgetch(gameWindow);
            if (!checkCollision(&t, key, mat)) {
                switch(key) {
                    case KEY_LEFT:
                        moveLeft(&t);
                        break;
                    case KEY_RIGHT:
                        moveRight(&t);
                        break;
                    case KEY_UP:
                        rotate(&t);
                        break;
                    default:
                        break;
                }
            }
            refreshWindow(gameWindow, t, mat);
        } while(!checkCollision(&t, KEY_DOWN, mat) && key != 'q');
        saveTetromino(&t, mat);
        points += checkRows(mat);
        printPoints(pointsWindow);
    } while(!boardFull(mat) && tetrominosStock() > 0 && key != 'q');
    wclear(gameWindow);
    wclear(pointsWindow);
    wrefresh(gameWindow);
    wrefresh(pointsWindow);
    gameOver();
}

void playerVsPlayer() {
    WINDOW* gameWindow = newwin(MAT_H*2, MAT_W*2, 0, 0);
    WINDOW* pointsWindow = newwin(50, 45, 0, MAT_W*2);
    WINDOW* gameWindow2 = newwin(MAT_H*2, MAT_W*2, 0, MAT_W*2 + 48);
    int key;
    int i = 0, j = 0;
    int pieceIndex1 = 0, pieceIndex2 = 0;
    Tetromino t1, t2;
    int turn = 0;

    // init
    clearScreen();
    initTetrominos();
    for (i = 0; i < 5; i++)
        pieces[i].stock = PIECES_STOCK*2;
    initMatrix();
    points = 0;
    points2 = 0;

    // play
    keypad(gameWindow, true);
    keypad(gameWindow2, true);

    refreshWindow(gameWindow, t1, mat);
    refreshWindow(gameWindow2, t2, mat2);
    do {
        if (!turn) {
            // select piece
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
                printPointsMultiPlayer(pointsWindow);
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

            // play
            do {
                moveDown(&t1);
                wtimeout(gameWindow, 100);
                key = wgetch(gameWindow);
                if (!checkCollision(&t1, key, mat)) {
                    switch(key) {
                        case KEY_LEFT:
                            moveLeft(&t1);
                            break;
                        case KEY_RIGHT:
                            moveRight(&t1);
                            break;
                        case KEY_UP:
                            rotate(&t1);
                            break;
                        default:
                            break;
                    }
                }
                refreshWindow(gameWindow, t1, mat);
            } while(!checkCollision(&t1, KEY_DOWN, mat) && key != 'q');
            saveTetromino(&t1, mat);
            points += checkRowsMultiplayer(mat, mat2);
            printPointsMultiPlayer(pointsWindow);

            turn = 1;
        } else {
            // select piece
            t2 = pieces[pieceIndex2];
            wtimeout(gameWindow2, -1);

            do {
                while (t2.stock == 0) {
                    pieceIndex2++;
                    if (pieceIndex2 > 4)
                        pieceIndex2 = 0;
                    t2 = pieces[pieceIndex2];
                }
                refreshWindow(gameWindow2, t2, mat2);
                printPointsMultiPlayer(pointsWindow);
                key = wgetch(gameWindow2);

                if (key == KEY_TAB) {
                    do {
                        pieceIndex2++;
                        if (pieceIndex2 > 4)
                            pieceIndex2 = 0;
                        t2 = pieces[pieceIndex2];
                    } while(t2.stock == 0);
                }
            } while(key == KEY_TAB);
            pieces[pieceIndex2].stock--;

            // play
            do {
                moveDown(&t2);
                wtimeout(gameWindow2, 100);
                key = wgetch(gameWindow2);
                if (!checkCollision(&t2, key, mat2)) {
                    switch(key) {
                        case KEY_LEFT:
                            moveLeft(&t2);
                            break;
                        case KEY_RIGHT:
                            moveRight(&t2);
                            break;
                        case KEY_UP:
                            rotate(&t2);
                            break;
                        default:
                            break;
                    }
                }
                refreshWindow(gameWindow2, t2, mat2);
            } while(!checkCollision(&t2, KEY_DOWN, mat2) && key != 'q');
            saveTetromino(&t2, mat2);
            points2 += checkRowsMultiplayer(mat2, mat);
            printPointsMultiPlayer(pointsWindow);
            
            turn = 0;
        }
    } while(!boardFull(mat) && !boardFull(mat2) && tetrominosStock() > 0 && key != 'q');
    wclear(gameWindow);
    wclear(gameWindow2);
    wclear(pointsWindow);
    wrefresh(gameWindow);
    wrefresh(gameWindow2);
    wrefresh(pointsWindow);
    gameOverMultiplayer();
}

void playerVsCpu() {

}