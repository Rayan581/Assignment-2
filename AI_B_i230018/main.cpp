#include <iostream>
#include "gameComponents.h"

using namespace std;

int main()
{
    initscr(); // Start ncurses mode
    cbreak();  // Disable line buffering
    noecho();  // Don't echo input to the screen

    // Prompt the user to select the difficulty level
    printw("Select difficulty level:\n");
    printw("1. Easy\n");
    printw("2. Medium\n");
    printw("3. Hard\n");
    printw("Enter number to select: ");
    int level = (getch() - '0');
    clear();

    Game game(level);
    game.game_loop();

    getch();
    endwin();

    return 0;
}