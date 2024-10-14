#ifndef GAME_COMPONENTS_H
#define GAME_COMPONENTS_H

#include <iostream>
#include <ncurses.h>
#include <ctime>

using namespace std;

// Position data type for the cell
struct Pos
{
    int x, y;

    // Sets both x and y of a cell
    void set_pos(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    // Returns if two pos are equal
    bool operator==(const Pos &other) const
    {
        return x == other.x && y == other.y;
    }
};

// Implements the cell structure
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
        pos.set_pos(x, y);
        this->symbol = symbol;
        isOccupied = (symbol == ' ') ? false : true;
    }

    // Returns the position of a cell in the grid
    Pos get_pos()
    {
        return pos;
    }

    // Returns the character in the cell
    char get_symbol()
    {
        return symbol;
    }

    // Returns the occupied state of the cell
    bool is_occupied()
    {
        return isOccupied;
    }

    // Sets the x and y coordinates of the cell
    void set_pos(int x, int y)
    {
        pos.set_pos(x, y);
    }

    // Sets the x coordinate of the cell
    void set_x(int x)
    {
        pos.x = x;
    }

    // Sets the y coordinate of the cell
    void set_y(int y)
    {
        pos.y = y;
    }

    // Sets the symbol in the cell
    void set_symbol(char symbol)
    {
        this->symbol = symbol;
    }

    // Sets the occupied state of the cell
    void set_occupied(bool flag)
    {
        isOccupied = flag;
    }
};

// Implements a 1D list
template <typename type>
class List
{
    struct Node
    {
        type data;
        Node *next;
    };
    Node *head;
    Node *tail;
    int size;

public:
    List()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    // Appends an element to end
    void add(type data)
    {
        Node *newNode = new Node;
        newNode->data = data;
        newNode->next = nullptr;
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // Inserts an element at index
    void add(type data, int index)
    {
        if (index < 0 || index > size)
            throw std::out_of_range("Index out of range");

        Node *newNode = new Node;
        newNode->data = data;
        if (index == 0)
        {
            newNode->next = head;
            head = newNode;
        }
        else if (index == size - 1)
        {
            add(data);
            size--;
        }
        else
        {
            Node *current = head;
            for (int i = 0; i < index - 1; i++)
                current = current->next;
            newNode->next = current->next;
            current->next = newNode;
        }
        size++;
    }

    // Returns if the list is empty
    bool isEmpty()
    {
        return head == nullptr;
    }

    // Removes and returns the last element in the list
    type pop()
    {
        if (isEmpty())
            throw std::out_of_range("List is empty");

        type data;

        if (head == tail)
        {
            data = head->data;
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            Node *current = head;

            while (current->next != tail)
                current = current->next;

            data = tail->data;
            delete tail;
            tail = current;
            tail->next = nullptr;
        }

        size--;
        return data;
    }

    // Removes and returns an element at index
    type pop(int index)
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of range");

        type data;

        if (index == 0)
        {
            Node *temp = head;
            data = head->data;
            head = head->next;
            if (head == nullptr)
                tail = nullptr;
            delete temp;
        }
        else if (index == size - 1)
        {
            data = pop();
            return data;
        }
        else
        {
            Node *current = head;
            for (int i = 0; i < index - 1; i++)
                current = current->next;

            Node *temp = current->next;
            data = temp->data;
            current->next = temp->next;

            if (temp == tail)
                tail = current;

            delete temp;
        }

        size--;
        return data;
    }

    // Removes the first occurence of an element
    void remove(type value)
    {
        if (isEmpty())
            throw std::out_of_range("List is empty");

        Node *current = head;
        Node *previous = nullptr;

        // If the element to remove is the head
        if (head->data == value)
        {
            head = head->next;
            if (head == nullptr)
                tail = nullptr;
            delete current;
            size--;
            return;
        }

        // Traverse the list to find the element
        while (current != nullptr && current->data != value)
        {
            previous = current;
            current = current->next;
        }

        // If the element is not found
        if (current == nullptr)
            throw std::invalid_argument("Element not found in the list");

        previous->next = current->next;

        if (current == tail)
            tail = previous;

        delete current;
        size--;
    }

    // Removes all occurences of an element
    void remove_all(type value)
    {
        if (isEmpty())
            throw std::out_of_range("List is empty");

        Node *current = head;
        Node *previous = nullptr;

        while (current != nullptr)
        {
            if (current->data == value)
            {
                Node *temp = current;

                if (current == head)
                {
                    head = current->next;
                    if (head == nullptr)
                        tail = nullptr;
                }
                else
                {
                    previous->next = current->next;
                    if (current == tail)
                        tail = previous;
                }

                current = current->next;
                delete temp;
                size--;
            }
            else
            {
                previous = current;
                current = current->next;
            }
        }
    }

    // Returns an element at an index
    type at(int index)
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of range");

        Node *current = head;
        for (int i = 0; i < index; i++)
            current = current->next;

        return current->data;
    }

    // Returns if an element is present in the list
    bool contains(type element)
    {
        Node *current = head;
        while (current != nullptr)
        {
            if (current->data == element)
                return true;
            current = current->next;
        }
        return false;
    }

    // Prints elements of list
    void print()
    {
        Node *current = head;
        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

// Implements a 2D list for the maze game
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
    Node *current;
    Pos currentPos;
    int size;

public:
    TwoDlist()
    {
        head = nullptr;
        current = nullptr;
        currentPos.set_pos(0, 0);
    }

    void set_size(int size)
    {
        this->size = size;
    }

    // Adds an element to right of current pointer
    void add_right(char symbol)
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
            current->cell.set_y(current->cell.get_pos().y + 1);
            current = newNode;
        }
    }

    // Adds an element to down of current pointer
    void add_down(char symbol)
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
            current->cell.set_x(current->cell.get_pos().x + 1);
            current = newNode;
        }
    }

    // Moves the current pointer to the given coordinates
    void move_to(int x, int y)
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

    // Places a character at given coordinates
    void place_char(Pos pos, char symbol)
    {
        move_to(pos.x, pos.y);
        current->cell.set_symbol(symbol);
    }

    void print_list()
    {
        if (head == nullptr)
            return;

        Node *row = head;
        int x = 0, y = 0;
        while (row != nullptr) // Traverse rows
        {
            x = 0;
            Node *current = row;
            if (row == head)
            {
                for (int i = 0; i < size + 2; i++)
                    printw(" # ");
                printw("\n");
            }
            while (current != nullptr) // Traverse columns
            {
                if (current == row)
                    printw(" # ");
                printw(" %c", current->cell.get_symbol());
                printw(" ");

                if (x == size - 1)
                    printw(" # ");
                current = current->right;
                x++;
            }
            printw("\n");
            if (y == size - 1)
            {
                for (int i = 0; i < size + 2; i++)
                    printw(" # ");
                printw("\n");
            }
            row = row->down; // Move down to the next row
            y++;
        }
        refresh();
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
        grid.set_size(size);

        for (int i = 0; i < size; i++)
        {
            grid.add_down('.');
            for (int j = 0; j < size - 1; j++)
                grid.add_right('.');
            grid.move_to(i, 0);
        }
    }

    void initialize_grid(int level)
    {
        srand(time(nullptr));
        switch (level)
        {
        case 1:
            int no_coins = 3;
            int no_bombs = 3;

            Pos door;
            door.set_pos(rand() % size, rand() % size);
            grid.place_char(door, 'D');

            Pos key;
            do
            {
                key.set_pos(rand() % size, rand() % size);
            } while (key == door);
            grid.place_char(key, 'K');

            Pos player;
            do
            {
                player.set_pos(rand() % size, rand() % size);
            } while (player == key || player == door);
            grid.place_char(player, 'P');

            List<Pos> coins;
            List<Pos> bombs;

            for (int i = 0; i < no_coins; i++)
            {
                Pos coin;
                do
                {
                    coin.set_pos(rand() % size, rand() % size);
                } while (coin == door || coin == key || coin == player || coins.contains(coin));
                coins.add(coin);
                grid.place_char(coin, 'C');
            }

            for (int i = 0; i < no_bombs; i++)
            {
                Pos bomb;
                do
                {
                    bomb.set_pos(rand() % size, rand() % size);
                } while (bomb == door || bomb == key || bomb == player || bombs.contains(bomb) || coins.contains(bomb));
                bombs.add(bomb);
                grid.place_char(bomb, 'B');
            }
        }
    }

    void print()
    {
        grid.print_list();
    }
};

#endif