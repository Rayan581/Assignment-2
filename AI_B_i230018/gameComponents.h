#ifndef GAME_COMPONENTS_H
#define GAME_COMPONENTS_H

#include <iostream>

using namespace std;

class Cell
{
private:
    // Position data type for the cell
    struct Pos
    {
        int x, y;

        // Sets both x and y of a cell
        void setPos(int x, int y)
        {
            this->x = x;
            this->y = y;
        }
    };

    Pos pos;
    char symbol;
    bool isOccupied;

public:
    Cell() {}
    Cell(int x, int y, char symbol)
    {
        pos.setPos(x, y);
        this->symbol = symbol;
        isOccupied = (symbol == ' ') ? false : true;
    }

    // Returns the position of a cell in the grid
    Pos getPos()
    {
        return pos;
    }

    // Returns the character in the cell
    char getSymbol()
    {
        return symbol;
    }

    // Returns the occupied state of the cell
    bool isOccupied()
    {
        return isOccupied;
    }

    // Sets the x and y coordinates of the cell
    void setPos(int x, int y)
    {
        pos.setPos(x, y);
    }

    // Sets the x coordinate of the cell
    void setX(int x)
    {
        pos.x = x;
    }

    // Sets the y coordinate of the cell
    void setY(int y)
    {
        pos.y = y;
    }

    // Sets the occupied state of the cell
    void setOccupied(bool flag)
    {
        isOccupied = flag;
    }
};

#endif