#include <iostream>
#include "gameComponents.h"

using namespace std;

int main()
{
    initscr();            // Start ncurses mode
    cbreak();             // Disable line buffering
    noecho();             // Don't echo input to the screen
    keypad(stdscr, TRUE); // Enable function keys

    Grid grid(10);
    grid.initialize_grid(1);

    grid.print();

    endwin();

    return 0;
}