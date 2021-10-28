#include <curses.h>

void init();
void printBanner();
int menu();

static int win_width, win_height;

int main(int argc, char** argv) {
    int mod = 0;
    
    init();
    printBanner();
    refresh();

    mod = menu();

    clear();
    printw("%d", mod);
    printw("Premi un tasto qualsiasi per chiudere...");
    getch();
    endwin();
 
    return 0;
}

void init() {
    initscr();
    cbreak();
    noecho();
    getmaxyx(stdscr, win_width, win_height);
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
    const int MAX_CHOICES = 3;
    char* choices[MAX_CHOICES] = {"Single player", "Player VS Player", "Player VS CPU"};
    int i = 0;

    box(menu, 0, '+');
    keypad(menu, true);
    wrefresh(menu);

    mvwprintw(menu, 0, 3, " ! SELECT A GAME MODE ! ");
    while(key != 10) {
        for (i = 0; i < MAX_CHOICES; i++) {
            if (i == highlight)
                wattron(menu, A_REVERSE);
            mvwprintw(menu, i + 2, 2, "%s", choices[i]);
            wattroff(menu, A_REVERSE);
        }
        key = wgetch(menu);
        switch(key) {
            case KEY_UP:
                if (highlight > 0)
                   highlight--;
                break;
            case KEY_DOWN:
                if (highlight < MAX_CHOICES-1)
                    highlight++;
                break;
            default:
                break;
        }

    }

    return highlight;
}