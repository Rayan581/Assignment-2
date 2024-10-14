#ifndef GAME_COMPONENTS_H
#define GAME_COMPONENTS_H

#include <iostream>

using namespace std;

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

class Cell
{
private:
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
    bool is_occupied()
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

class TwoDlist
{
private:
    struct Node
    {
        Cell cell;
        Node *left;
        Node *right;
        Node *up;
        Node *down;
    };
    Node *head;
    Node *tail;
    Node *current;
    Pos currentPos;
    int size;

public:
    TwoDlist()
    {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
        currentPos.setPos(0, 0);
    }

    void setSize(int size)
    {
        this->size;
    }

    // Adds an element to right of current pointer
    void addRight(char symbol)
    {
        Node *newNode = new Node;
        newNode->cell = Cell(currentPos.x + 1, currentPos.y, symbol);
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->up = nullptr;
        newNode->down = nullptr;

        // If the list is empty, set the newNode as the head, tail, and current
        if (current == nullptr)
        {
            head = newNode;
            tail = newNode;
            current = newNode;
        }
        else
        {
            // Link the new node to the current node
            newNode->left = current;
            newNode->right = current->right;
            current->right = newNode;

            if (newNode->right != nullptr)
                newNode->right->left = newNode;

            newNode->up = (current->up != nullptr) ? current->up->right : nullptr;
            if (newNode->up != nullptr)
                newNode->up->down = newNode;

            newNode->down = (current->down != nullptr) ? current->down->right : nullptr;
            if (newNode->down != nullptr)
                newNode->down->up = newNode;
            current->cell.setX(current->cell.getPos().x + 1);
            current = newNode;
        }
    }

    // Adds an element to down of current pointer
    void addDown(char symbol)
    {
        Node *newNode = new Node;
        newNode->cell = Cell(currentPos.x, currentPos.y - 1, symbol);
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->up = nullptr;
        newNode->down = nullptr;

        // If the list is empty, set the newNode as the head, tail, and current
        if (current == nullptr)
        {
            head = newNode;
            tail = newNode;
            current = newNode;
        }
        else
        {
            // Link the new node to the current node
            newNode->up = current;
            newNode->down = current->down;
            current->down = newNode;

            if (newNode->down != nullptr)
                newNode->down->up = newNode;

            newNode->left = (current->left != nullptr) ? current->left->down : nullptr;
            if (newNode->left != nullptr)
                newNode->left->right = newNode;

            newNode->right = (current->right != nullptr) ? current->right->down : nullptr;
            if (newNode->right != nullptr)
                newNode->right->left = newNode;
            current->cell.setY(current->cell.getPos().y - 1);
            current = newNode;
        }
    }

    void moveTo(int x, int y)
    {
        Node *temp = head;

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (i == x && j == y)
                {
                    current = temp;
                    currentPos.x = x;
                    currentPos.y = y;
                    return;
                }
                if (temp->right)
                    temp = temp->right;
            }
            temp = head;
            for (int j = 0; j <= i; j++)
                if (temp->down)
                    temp = temp->down;
        }
    }

    void printList()
    {
        if (head == nullptr)
            return;

        Node *row = head;
        while (row != nullptr) // Traverse rows
        {
            Node *current = row;
            while (current != nullptr) // Traverse columns
            {
                cout << "[ " << current->cell.getSymbol() << " ]";
                current = current->right;
            }
            cout << endl;
            row = row->down; // Move down to the next row
        }
    }
};

class Grid
{
private:
    TwoDlist grid;
    int size;

public:
    Grid(int size)
    {
        this->size = size;
        grid.setSize(size);

        for (int i = 0; i < size; i++)
        {
            grid.addDown(' ');
            for (int j = 0; j < size - 1; j++)
                grid.addRight(' ');
            grid.moveTo(i, 0);
        }
    }

    void print()
    {
        grid.printList();
    }
};

#endif