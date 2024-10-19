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

    Pos() {}

    // Intializes the position with the given x and y coordinates
    Pos(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

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

    // Returns if two pos are not equal
    bool operator!=(const Pos &other) const
    {
        return x != other.x || y != other.y;
    }

    // Print the position
    void print() const
    {
        printw("(%d, %d)", x, y);
    }
};

// Implements the cell structure
class Cell
{
private:
    Pos pos;
    char symbol;
    bool is_hidden;

public:
    Cell() {}
    Cell(int x, int y, char symbol)
    {
        pos.set_pos(x, y);
        this->symbol = symbol;
        is_hidden = false;
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
    bool hidden_status()
    {
        return is_hidden;
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
        if (symbol == 'K' || symbol == 'D')
            is_hidden = true;
    }

    // Sets the occupied state of the cell
    void set_hidden(bool flag)
    {
        is_hidden = flag;
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
        while (current != nullptr && !(current->data == value))
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

    // Clears the list
    void clear()
    {
        while (!isEmpty())
            pop();
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

// Implements a stack
template <typename type>
class MutatedStack
{
private:
    struct Node
    {
        type data;
        Node *next;
    };
    Node *top;
    int size;

public:
    MutatedStack()
    {
        top = nullptr;
        size = 0;
    }

    // Pushes an element onto the stack
    void push(type data)
    {
        Node *newNode = new Node;
        newNode->data = data;
        newNode->next = top;
        top = newNode;
        size++;
    }

    // Returns if the stack is empty
    bool isEmpty()
    {
        return top == nullptr;
    }

    // Pops and returns the top element from the stack
    type pop()
    {
        if (isEmpty())
            return type();

        type data = top->data;
        Node *temp = top;
        top = top->next;
        delete temp;
        size--;
        return data;
    }

    // Returns the top element from the stack
    type peek()
    {
        if (isEmpty())
            return type();

        return top->data;
    }

    // Returns if the stack contains the given element
    bool contains(type element)
    {
        Node *current = top;
        while (current != nullptr)
        {
            if (current->data == element)
                return true;
            current = current->next;
        }
        return false;
    }

    // Removes the given element from the stack
    void remove(type element)
    {
        if (isEmpty())
            return;

        if (top->data == element)
        {
            pop();
            return;
        }

        Node *current = top;
        Node *previous = nullptr;

        while (current->next != nullptr && current->next->data != element)
        {
            previous = current;
            current = current->next;
        }

        if (current->next == nullptr)
            return;

        previous->next = current->next;
        delete current;
        size--;
    }

    // Clears the stack
    void clear()
    {
        while (!isEmpty())
            pop();
    }

    // Returns the number of elements in the stack
    int get_size()
    {
        return size;
    }

    // Prints the elements in the stack
    void print()
    {
        Node *current = top;
        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

// Prints the stack containing position objects
template <>
void MutatedStack<Pos>::print()
{
    Node *current = top;
    while (current != nullptr)
    {
        current->data.print();
        printw(" ");
        current = current->next;
    }
    printw("\n");
}

#include <iostream>
#include <ncurses.h> // Assuming you're using ncurses
using namespace std;

// Implements a queue
template <typename type>
class MutatedQueue
{
private:
    struct Node
    {
        type data;
        Node *next;
    };
    Node *front;
    Node *rear;
    int size;

public:
    MutatedQueue()
    {
        front = nullptr;
        rear = nullptr;
        size = 0;
    }

    // Enqueues an element (adds to the rear)
    void enqueue(type data)
    {
        Node *newNode = new Node;
        newNode->data = data;
        newNode->next = nullptr;

        if (isEmpty())
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }

        size++;
    }

    // Returns if the queue is empty
    bool isEmpty()
    {
        return front == nullptr;
    }

    // Dequeues and returns the front element from the queue
    type dequeue()
    {
        if (isEmpty())
            return type();

        type data = front->data;
        Node *temp = front;
        front = front->next;
        if (front == nullptr)
            rear = nullptr;

        delete temp;
        size--;
        return data;
    }

    // Removes the last element from the queue
    type pop()
    {
        if (isEmpty())
            return type();

        type data = rear->data;
        Node *temp = rear;

        if (front == rear)
        {
            front = nullptr;
            rear = nullptr;
        }
        else
        {
            Node *current = front;
            while (current->next != rear)
                current = current->next;

            rear = current;
            rear->next = nullptr;
        }

        delete temp;
        size--;
        return data;
    }

    // Returns the front element
    type peek_front()
    {
        if (isEmpty())
            return type();

        return front->data;
    }

    // Returns the rear element
    type peek_rear()
    {
        if (isEmpty())
            return type();

        return rear->data;
    }

    // Returns if the queue contains the given element
    bool contains(type element)
    {
        Node *current = front;
        while (current != nullptr)
        {
            if (current->data == element)
                return true;
            current = current->next;
        }
        return false;
    }

    // Removes the given element from the queue
    void remove(type element)
    {
        if (isEmpty())
            return;

        if (front->data == element)
        {
            dequeue();
            return;
        }

        Node *current = front;
        Node *previous = nullptr;

        while (current->next != nullptr && current->next->data != element)
        {
            previous = current;
            current = current->next;
        }

        if (current->next == nullptr)
            return;

        previous->next = current->next;
        if (current == rear)
            rear = previous;
        delete current;
        size--;
    }

    // Clears the queue
    void clear()
    {
        while (!isEmpty())
            dequeue();
    }

    // Returns the number of elements in the queue
    int get_size()
    {
        return size;
    }

    // Prints the elements in the queue
    void print()
    {
        Node *current = front;
        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

// Prints the queue containing the position objects
template <>
void MutatedQueue<Pos>::print()
{
    Node *current = front;
    while (current != nullptr)
    {
        current->data.print();
        printw(" ");
        current = current->next;
    }
    printw("\n");
}

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
        newNode->cell = Cell(currentPos.x, currentPos.y + 1, symbol);
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

    // Clear the list
    void clear()
    {
        Node *current = head;
        Node *row = head;

        while (row != nullptr)
        {
            Node *temp = row;
            row = row->down;
            while (temp != nullptr)
            {
                Node *next = temp->right;
                delete temp;
                temp = next;
            }
        }
        head = nullptr;
        current = nullptr;
        currentPos.set_pos(0, 0);
        size = 0;
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

    char get_char(Pos pos)
    {
        move_to(pos.x, pos.y);
        return current->cell.get_symbol();
    }

    // Hides or unhides the character at given coordinates
    void toggle_hide(Pos pos)
    {
        move_to(pos.x, pos.y);
        current->cell.set_hidden(true);
    }

    // Prints the 2D list
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
                if (!current->cell.hidden_status())
                    printw(" %c", current->cell.get_symbol());
                else if (current->cell.get_symbol() == 'P')
                    printw(" %c", current->cell.get_symbol());
                else
                    printw(" .");
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

class Player
{
private:
    Pos pos;
    bool key_state;
    MutatedQueue<Pos> collectedCoins;
    int moves;
    int undos;
    int score;
    int distance;

    struct Move
    {
        Pos previous;
        Pos current;
    };

    MutatedStack<Move> moves_stack;

public:
    Player()
    {
        key_state = false;
        pos.set_pos(0, 0);
        moves = 0;
        undos = 0;
        score = 0;
    }

    // Sets the position of the player
    void set_pos(Pos pos)
    {
        this->pos = pos;
    }

    // Returns the position of the player
    Pos get_pos()
    {
        return pos;
    }

    // Returns if the player has the key
    bool has_key()
    {
        return key_state;
    }

    // Sets the key status
    void key_status(bool status)
    {
        key_state = status;
    }

    // Adds a coin to the inventory
    void add_coin(Pos pos)
    {
        collectedCoins.enqueue(pos);
    }

    // Returns the number of coins collected by the player
    int get_coins()
    {
        return collectedCoins.get_size();
    }

    // Returns the number of moves
    int get_moves()
    {
        return moves;
    }

    // Sets the number of moves
    void set_moves(int moves)
    {
        this->moves = moves;
    }

    // Returns the number of undos
    int get_undos()
    {
        return undos;
    }

    // Sets the number of undos
    void set_undos(int undos)
    {
        this->undos = undos;
    }

    // Returns the score
    int get_score()
    {
        return score;
    }

    // Checks if the coins stack contains the given stack
    bool find_in_coins(Pos pos)
    {
        if (collectedCoins.peek_rear() == pos)
        {
            collectedCoins.pop();
            return true;
        }
        return false;
    }

    // Sets the score
    void set_score(int score)
    {
        if (score < 0)
            score = 0;
        this->score = score;
    }

    // Returns the distance
    int get_distance()
    {
        return distance;
    }

    // Sets the distance
    void set_distance(int distance)
    {
        this->distance = distance;
    }

    // Adds the move to the moves list
    void add_move(Pos previous, Pos current)
    {
        Move move;
        move.previous = previous;
        move.current = current;
        moves_stack.push(move);
    }

    // Returns last move's position
    Pos get_last_move_pos()
    {
        if (moves_stack.isEmpty())
            return Pos(-1, -1);

        return moves_stack.peek().previous;
    }

    // Removes last move from the moves list and returns
    Pos pop_last_move_pos()
    {
        if (moves_stack.isEmpty())
            return Pos(-1, -1);

        return moves_stack.pop().previous;
    }

    Pos get_last_coin()
    {
        if (collectedCoins.isEmpty())
            return Pos(-1, -1);

        return collectedCoins.peek_rear();
    }

    // Returns if the moves stack is empty
    bool is_move_empty()
    {
        return moves_stack.isEmpty();
    }

    // Prints the positions of the collected coins
    void print_coins()
    {
        collectedCoins.print();
    }

    // Calculates the score after game end
    void calculate_score()
    {
        score += moves;
    }
};

class Grid
{
private:
    TwoDlist grid;
    Pos door;
    Pos key;
    Player player;
    List<Pos> coins;
    List<Pos> bombs;
    int size;

public:
    Grid()
    {
        size = 10;
        grid.set_size(size);
    }

    // Initializes the grid with player position, key and door positions, and coins and bombs positions based on current player level
    void initialize_grid(int level)
    {
        srand(time(nullptr));

        int no_coins = 0;
        int no_bombs = 0;

        switch (level)
        {
        case 1:
        {
            // Sets the number of coins and bombs to 3
            no_coins = 3;
            no_bombs = 3;

            // Grant 6 undo moves
            player.set_undos(6);
            break;
        }
        }

        // Generates a 2D list of given size
        for (int i = 0; i < size; i++)
        {
            grid.add_down('.');
            for (int j = 0; j < size - 1; j++)
                grid.add_right('.');
            grid.move_to(i, 0);
        }

        // Generate position of door
        door.set_pos(rand() % size, rand() % size);
        grid.place_char(door, 'D');

        // Generate position of key
        do
        {
            key.set_pos(rand() % size, rand() % size);
        } while (key == door);
        grid.place_char(key, 'K');

        // Generate position of player
        do
        {
            player.set_pos(Pos(rand() % size, rand() % size));
        } while (player.get_pos() == key || player.get_pos() == door);
        grid.place_char(player.get_pos(), 'P');

        // Generate positions of coins
        for (int i = 0; i < no_coins; i++)
        {
            Pos coin;
            do
            {
                coin.set_pos(rand() % size, rand() % size);
            } while (coin == door || coin == key || coin == player.get_pos() || coins.contains(coin));
            coins.add(coin);
            grid.place_char(coin, 'C');
        }

        // Generate positions of bombs
        for (int i = 0; i < no_bombs; i++)
        {
            Pos bomb;
            do
            {
                bomb.set_pos(rand() % size, rand() % size);
            } while (bomb == door || bomb == key || bomb == player.get_pos() || bombs.contains(bomb) || coins.contains(bomb));
            bombs.add(bomb);
            grid.place_char(bomb, 'B');
        }

        calculate_init_moves(level);
    }

    // Sets the size of the grid
    void set_size(int size)
    {
        this->size = size;
        grid.set_size(size);
    }

    // Initially gives moves to the player
    void calculate_init_moves(int level)
    {
        // Calculate distance to the key
        int key_distance = 0;
        int dx = abs(player.get_pos().x - key.x);
        int dy = abs(player.get_pos().y - key.y);
        key_distance = dx + dy;

        // Calculate distance to the door
        int door_distance = 0;
        dx = abs(player.get_pos().x - door.x);
        dy = abs(player.get_pos().y - door.y);
        door_distance = dx + dy;

        // Calculate total distance
        int total_distance = key_distance + door_distance;

        // Calculate total moves accorging to total distance and difficulty level
        int total_moves = total_distance + ((size * size) / (level * level * 5));

        player.set_moves(total_moves);
    }

    // Moves the player up
    bool move_up()
    {

        if (player.get_pos().x - 1 >= 0)
        {
            if (player.get_pos().x - 1 == player.get_last_move_pos().x && player.get_pos().y == player.get_last_move_pos().y)
                return false;

            Pos previous = player.get_pos();

            grid.place_char(player.get_pos(), '.');
            player.set_pos(Pos(player.get_pos().x - 1, player.get_pos().y));
            grid.place_char(player.get_pos(), 'P');
            player.set_moves(player.get_moves() - 1);

            Pos current = player.get_pos();
            player.add_move(previous, current);
        }

        return true;
    }

    // Moves the player down
    bool move_down()
    {

        if (player.get_pos().x + 1 < size)
        {
            if (player.get_pos().x + 1 == player.get_last_move_pos().x && player.get_pos().y == player.get_last_move_pos().y)
                return false;

            Pos previous = player.get_pos();

            grid.place_char(player.get_pos(), '.');
            player.set_pos(Pos(player.get_pos().x + 1, player.get_pos().y));
            grid.place_char(player.get_pos(), 'P');
            player.set_moves(player.get_moves() - 1);

            Pos current = player.get_pos();
            player.add_move(previous, current);
        }

        return true;
    }

    // Moves the player left
    bool move_left()
    {

        if (player.get_pos().y - 1 >= 0)
        {
            if (player.get_pos().x == player.get_last_move_pos().x && player.get_pos().y - 1 == player.get_last_move_pos().y)
                return false;

            Pos previous = player.get_pos();

            grid.place_char(player.get_pos(), '.');
            player.set_pos(Pos(player.get_pos().x, player.get_pos().y - 1));
            grid.place_char(player.get_pos(), 'P');
            player.set_moves(player.get_moves() - 1);

            Pos current = player.get_pos();
            player.add_move(previous, current);
        }

        return true;
    }

    // Moves the player right
    bool move_right()
    {

        if (player.get_pos().y + 1 < size)
        {
            cout << "Hello" << endl;
            if (player.get_pos().x == player.get_last_move_pos().x && player.get_pos().y + 1 == player.get_last_move_pos().y)
                return false;

            Pos previous = player.get_pos();

            grid.place_char(player.get_pos(), '.');
            player.set_pos(Pos(player.get_pos().x, player.get_pos().y + 1));
            grid.place_char(player.get_pos(), 'P');
            player.set_moves(player.get_moves() - 1);

            Pos current = player.get_pos();
            player.add_move(previous, current);
        }

        return true;
    }

    // Checks the collision of player with other things
    void check_collision()
    {
        collect_key();
        collect_coin();
        hit_bomb();
        check_moves();
    }

    // Tells if the player is getting closer to goal or not
    void getting_closer()
    {
        int previous_distance = player.get_distance();

        int x = 0, y = 0;

        !(player.has_key()) ? (x = key.x, y = key.y) : (x = door.x, y = door.y);
        int dx = abs(x - player.get_pos().x);
        int dy = abs(y - player.get_pos().y);

        int current_distance = dx + dy;
        player.set_distance(current_distance);

        printw("Hint: ");
        if (current_distance < previous_distance)
            printw("Getting Closer!\n");
        else
            printw("Further Away!\n");
    }

    // Checks if the player has reached the key
    void collect_key()
    {
        if (player.get_pos() == key)
        {
            player.key_status(true);
            grid.toggle_hide(player.get_pos());
            grid.place_char(key, 'P');
        }
    }

    // Checks if the player has collected a coin
    void collect_coin()
    {
        if (coins.contains(player.get_pos()))
        {
            player.add_coin(player.get_pos());
            player.set_score(player.get_score() + 2); // Add 2 score for each coin
            coins.remove(player.get_pos());
            grid.place_char(player.get_pos(), 'P');
        }
    }

    // Undo the last move
    void undo_move(bool gameOver)
    {
        if (player.get_undos() > 0 || gameOver || 1)
        {
            Pos previous = player.pop_last_move_pos();

            if (previous == Pos(-1, -1))
                return;

            Pos current = player.get_pos();
            player.set_pos(previous);
            player.set_undos(player.get_undos() - 1);

            if (player.find_in_coins(current)) // If there was a coin, place if back
            {
                coins.add(current);
                grid.place_char(current, 'C');
            }
            else // Else place a space
            {
                if (grid.get_char(current) != 'B') // If there was not a bomb
                    grid.place_char(current, '.');
            }

            player.set_moves(player.get_moves() + 1); // Return the last move used to the player
            grid.place_char(previous, 'P');
        }
    }

    // Checks if the player has the key and reached the door
    bool win_game()
    {
        if (player.has_key() && player.get_pos() == door)
        {
            grid.toggle_hide(player.get_pos());
            return true;
        }
        return false;
    }

    // Revert the grid to original state after the game has ended
    void revert_grid()
    {
        while (!player.is_move_empty())
            undo_move(true);
        grid.place_char(key, 'K');
        grid.place_char(door, 'D');
    }

    // Game over function
    void game_over(const char *message)
    {
        printw("\n");
        clear();
        printw("%s\n", message);
        printw("Collected Coins:");
        printw("\t\tRemaining Moves: %d\n", player.get_moves());
        player.print_coins();

        if (message == "Congratulations! You have reached the door!")
            player.calculate_score();
        printw("Score: ");
        printw("%d\n", player.get_score());
        revert_grid();
        printw("Original State of the game:\n");
        display_grid();
        printw("Press any key to exit...");
        getch();
        endwin();
        exit(0);
    }

    // Checks if the player has reached a bomb
    void hit_bomb()
    {
        if (bombs.contains(player.get_pos()))
        {
            grid.place_char(player.get_pos(), 'B');
            game_over("Hit Bomb!");
        }
    }

    // Checks if there are no moves left
    void check_moves()
    {
        if (player.get_moves() == 0)
            game_over("No More Moves!");
    }

    // Displays the player stats
    void display_stats(int level)
    {
        if (level == 1)
            printw("Mode: Easy");
        else if (level == 2)
            printw("Mode: Medium");
        else if (level == 3)
            printw("Mode: Hard");

        printw("\n");
        printw("Remaining Moves: ");
        printw("%d", player.get_moves());
        printw("\tRemaining Undos: ");
        printw("%d", player.get_undos());
        printw(" (Press U to use)");
        printw("\n");
        printw("Score: ");
        printw("%d", player.get_score());
        printw("\tKey Status: ");
        if (player.has_key())
            printw("True");
        else
            printw("False");
        printw("\n");
        getting_closer();
    }

    // Displays the game grid
    void display_grid()
    {
        grid.print_list();
    }
};

class Game
{
private:
    Grid grid;
    int level;

public:
    Game(int _level)
    {
        level = _level;
        grid.initialize_grid(level);
        grid.display_stats(level);
        grid.display_grid();
    }

    // Moves the player based on the player input
    bool move_player()
    {
        int playerInput = getch();
        bool moved = true;

        switch (playerInput)
        {
        case 'w':
            moved = grid.move_up();
            break;

        case 's':
            moved = grid.move_down();
            break;

        case 'a':
            moved = grid.move_left();
            break;

        case 'd':
            moved = grid.move_right();
            break;
        case 'u':
            grid.undo_move(false);
            break;
        }

        grid.check_collision();
        if (grid.win_game())
        {
            grid.game_over("Congratulations! You have reached the door!");
            return false;
        }

        return moved;
    }

    // Runs the main game loop
    void game_loop()
    {
        while (true)
        {
            bool moved = move_player();
            clear();

            grid.display_stats(level);
            grid.display_grid();

            // If last move was not possible, display error message
            if (!moved)
            {
                printw("Cannot move to the last position!\n");
                printw("Use undo feature to move to the last position!\n");
            }
        }
    }
};

#endif