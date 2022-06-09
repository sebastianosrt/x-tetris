/**
 * @file main.c
 * @brief main file of the game
 * @author Sebastiano Sartor
 * @mainpage X-Tetris
 * @section Intro
 * X-Tetris in game written in ANSI C
 * @section Dependencies
 *
 * <ul>
 *      <li>MinGW (for windows users)</li>
 *      <li>Ncurses: <a href="https://e-l.unifi.it/pluginfile.php/805205/mod_resource/content/0/ncurses%20installation%20-%20en.pdf">how to install</a></li>
 *      <li>Make</li>
 * </ul>
 *
 * @section HOW How to run the game
 * <ol>
 *      <li>
 *          <span>Download the repository:</span>
 *          <br>
 *          <code>git clone https://github.com/sebastianosrt/x-tetris</code>
 *      </li>
 *      <li>
 *          <span>Compile and execute the game</span>
 *          <br>
 *          <code>cd x-tetris</code>
 *          <br>
 *          <code>make</code> 
 *      </li>
 * </ol>
 *
 * @section Commands
 *
 * <ul>
 *     <li><code>KEY UP</code>: rotate tetromino/move up in the menu</li>
 *     <li><code>KEY DOWN</code>: place the tetromino/move down in the menu</li>
 *     <li><code>KEY LEFT</code>: move left</li>
 *     <li><code>KEY RIGHT</code>: move right</li>
 *     <li><code>TAB</code>: switch tetromino</li>
 *     <li><code>Q</code>: end the match</li>
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