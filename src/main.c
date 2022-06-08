/**
 * @file main.c
 * @brief 
 * @author Sebastiano Sartor
 * @mainpage X-Tetris
 * @section Intro
 * X-Tetris in C
 * @section Dependencies
 *
 * <ul>
 *      <li>MinGW (for windows users)</li>
 *      <li>ncurses <a href="https://e-l.unifi.it/pluginfile.php/805205/mod_resource/content/0/ncurses%20installation%20-%20en.pdf">tutorial</a></li>
 * </ul>
 *
 * @section How to run the game
 * <ol>
 *      <li>
 *          <span>Download the repository</span>
 *          <code>git clone https://github.com/sebastianosrt/x-tetris</code>
 *      </li>
 *      <br />
 *      <li>
 *          <span>Compile and execute the game</span>
 *      </li>
 *      <li>
 *          <code>cd x-tetris</code>
 *          <code>make</code>
 *          <code>./x-tetris</code>
 *      </li>
 * </ol>
 *
 * @section Commands
 * <br />
 *
 * <ul>
 *     <li><code>ESC</code>: end the match</li>
 *     <li><code>UP</code>: rotate tetromino</li>
 *     <li><code>LEFT</code>: move left</li>
 *     <li><code>RIGHT</code>: move right</li>
 *     <li><code>TAB</code>: switch tetromino</li>
 * </ul>
 *
 */

#include "headers/game.h"

int main(int argc, char** argv) {
    int mod = 0;

    init();

    do {
        mod = menu();
        play();
        switch (mod) {
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
    } while(mod != 3);

    endgame();
 
    return 0;
}