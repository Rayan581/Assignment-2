#include <iostream>
#include "gameComponents.h"

using namespace std;

int main()
{
    initscr();            // Start ncurses mode
    cbreak();             // Disable line buffering
    noecho();             // Don't echo input to the screen

    Game game;
    game.game_loop();

    getch();
    endwin();

    return 0;
}