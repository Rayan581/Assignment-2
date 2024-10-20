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

    int level = 0;
    do
    {
        level = (getch() - '0');
        if (level < 1 || level > 3)
            printw("Invalid Input!\nInput again: ");
    } while (level < 1 || level > 3); // Input again if the input is invalid

    clear();

    Game game(level);
    game.game_loop(); // Run the main game loop

    getch();
    endwin();

    return 0;
}