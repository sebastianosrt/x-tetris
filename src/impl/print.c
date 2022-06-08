#include "../headers/print.h"

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

void printGameOver(int points) {
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
                                                                                                                
void printGameOverPlayer1Wins(int points) {
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

void printGameOverPlayer2Wins(int points) {
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
    
    snprintf(str, 12, "POINTS: %d", points);
    mvprintw(11, 0, str);
    mvprintw(13, 0, "PRESS ANY KEY TO CONTINUE");
    refresh();
}

void printDraw() {
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

void printPoints(Tetromino* pieces, WINDOW* win, int points) {
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

void printPointsMultiPlayer(Tetromino* pieces, WINDOW* win, int p, int p2) {
    int i, j, k, x = 4;
    char str[15];

    mvwaddstr(win, 0, x, "POINTS:");
    snprintf(str, 15, "  %d : %d", p, p2);
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