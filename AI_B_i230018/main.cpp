#include <iostream>
#include "gameComponents.h"

using namespace std;

int main()
{
    // Grid grid(10);

    // grid.print();

    List<int> list;

    list.add(1);
    list.add(1);
    list.add(1);
    list.add(2);
    list.add(3, 2);

    list.print();

    return 0;
}