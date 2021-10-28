/*
    Sartor Sebastiano
    Matricola #891825
    A.S. 2021/2022
    Progetto X-Tetris 
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
int menu();
void singlePlayer();
void initTetrominos();
Tetromino selectTetromino();
void printTetromino();
void playerVsPlayer();
void playerVsCpu();

// static variables
static int win_width, win_height; // the window dimensions
static int mat[MAT_H][MAT_W] = {{0}}; // the game field matrix
static int points = 0;
// the tetrominos
static Tetromino t_blue;
static Tetromino t_yellow;
static Tetromino t_orange;
static Tetromino t_green;
static Tetromino t_pink;
static Tetromino* pieces;

// game
int main(int argc, char** argv) {
    int mod = 0;

    init();

    mod = menu(); // get the game mode
    clear(); // clear the screen
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

    endwin();
 
    return 0;
}

// function definitions
void init() {
    initscr();
    cbreak();
    noecho();
    getmaxyx(stdscr, win_width, win_height); // get the rows and columns of the window
    start_color();
    curs_set(0);
    printBanner();
    refresh();
}

void printBanner() {
    int x = 0, y = 0;
    mvprintw(y, x,     "@@@  @@@             @@@@@@@  @@@@@@@@  @@@@@@@  @@@@@@@   @@@   @@@@@@   \n");
    mvprintw(y + 1, x, "@@@  @@@             @@@@@@@  @@@@@@@@  @@@@@@@  @@@@@@@@  @@@  @@@@@@@   \n");
    mvprintw(y + 2, x, "@@!  !@@               @@!    @@!         @@!    @@!  @@@  @@!  !@@       \n");
    mvprintw(y + 3, x, "!@!  @!!               !@!    !@!         !@!    !@!  @!@  !@!  !@!       \n");
    mvprintw(y + 4, x, " !@@!@!   @!@!@!@!@    @!!    @!!!:!      @!!    @!@!!@!   !!@  !!@@!!    \n");
    mvprintw(y + 5, x, "  @!!!    !!!@!@!!!    !!!    !!!!!:      !!!    !!@!@!    !!!   !!@!!!   \n");
    mvprintw(y + 6, x, " !: :!!                !!:    !!:         !!:    !!: :!!   !!:       !:!  \n");
    mvprintw(y + 7, x, ":!:  !:!               :!:    :!:         :!:    :!:  !:!  :!:      !:!   \n");
    mvprintw(y + 8, x, " ::  :::                ::     :: ::::     ::    ::   :::   ::  :::: ::   \n");
    mvprintw(y + 9, x, " :   ::                 :     : :: ::      :      :   : :  :    :: : :    \n");
}

int menu() {
    WINDOW* menu = newwin(7, win_width, 12, 0);
    int key, highlight = 0;
    char* choices[MENU_CHOICES] = {"Single player", "Player VS Player", "Player VS CPU"};
    int i = 0;

    box(menu, 0, '+'); // draw the menu box
    keypad(menu, true);
    wrefresh(menu);

    mvwprintw(menu, 0, 3, " ! SELECT A GAME MODE ! ");
    while(key != ENTER) {
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

    }

    return highlight;
}

void singlePlayer() {
    clear();
    refresh();
    initTetrominos();
    selectTetromino();
}

void initTetrominos() {
    t_blue =(Tetromino) {
        .stock = PIECES_STOCK,
        .color = COLOR_CYAN,
        .type = 1,
        .shape = {
            { .x = 0, .y = 0 },
            { .x = 1, .y = 0 },
            { .x = 2, .y = 0 },
            { .x = 3, .y = 0 }
        }
    };
    t_yellow =(Tetromino) {
        .stock = PIECES_STOCK,
        .color = COLOR_YELLOW,
        .type = 2,
        .shape = {
            { .x = 0, .y = 0 },
            { .x = 1, .y = 0 },
            { .x = 0, .y = 1 },
            { .x = 1, .y = 1 }
        }
    };
    t_orange =(Tetromino) {
        .stock = PIECES_STOCK,
        .color = COLOR_RED,
        .type = 3,
        .shape = {
            { .x = 0, .y = 0 },
            { .x = 0, .y = 1 },
            { .x = 0, .y = 2 },
            { .x = 1, .y = 2 }
        }
    };
    t_green =(Tetromino) {
        .stock = PIECES_STOCK,
        .color = COLOR_CYAN,
        .type = 4,
        .shape = {
            { .x = 0, .y = 0 },
            { .x = 0, .y = 1 },
            { .x = 1, .y = 1 },
            { .x = 1, .y = 2 }
        }
    };
    t_pink =(Tetromino) {
        .stock = PIECES_STOCK,
        .color = COLOR_MAGENTA,
        .type = 5,
        .shape = {
            { .x = 0, .y = 0 },
            { .x = 1, .y = 0 },
            { .x = 2, .y = 0 },
            { .x = 1, .y = 1 }
        }
    };

    pieces =(Tetromino*) malloc(sizeof(Tetromino) * 5);
    pieces[0] = t_blue;
    pieces[1] = t_yellow;
    pieces[2] = t_orange;
    pieces[3] = t_green;
    pieces[4] = t_pink;
}

Tetromino selectTetromino() {
    WINDOW* selectWindow = newwin(10, 50, 0, 0);
    int key, highlight = 0;
    int i = 0;

    box(selectWindow, 0, 0);
    keypad(selectWindow, true);
    wrefresh(selectWindow);

    while(key != ENTER) {
        mvwprintw(selectWindow, 1, 1, " SELECT A PIECE ");
        mvwprintw(selectWindow, 5, 40, "->");
        mvwprintw(selectWindow, 5, 10, "<-");
        // print the piece
        printTetromino(highlight, selectWindow, 25, 5);
        // get the key
        key = wgetch(selectWindow);
        switch(key) {
            case KEY_LEFT:
                highlight--;
                if (highlight == -1)
                    highlight = PIECES - 1;
                break;
            case KEY_RIGHT:
                highlight++;
                if (highlight == PIECES)
                    highlight = 0;
                break;
            default:
                break;
        }
        wclear(selectWindow);
        box(selectWindow, 0, 0);
        wrefresh(selectWindow);
    }

    return pieces[highlight];
}

void printTetromino(int pieceIndex, WINDOW* window, int x, int y) {
    int i;

    Tetromino t = pieces[pieceIndex];
    init_pair(t.type, t.color, t.color);
    wattron(window, COLOR_PAIR(t.type));
    for (i = 0; i < SHAPE_COORDS_COUNT; i++) {
        mvwaddstr(window, t.shape[i].y + y - calcPieceHeight(t) / 2, (2*(t.shape[i].x + x)) - x - calcPieceWidth(t), "  ");

    }
    wattroff(window, COLOR_PAIR(t.type)); 
    wrefresh(window);
}

void playerVsPlayer() {

}

void playerVsCpu() {

}