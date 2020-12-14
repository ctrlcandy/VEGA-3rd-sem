#include <iostream>
#include "BST.h"

int main() {
    BST n;
    n.insert(55);
    n.insert(58);
    n.insert(52);

    n.remove(52);
    n.insert(52);
    n.remove(52);
    n.insert(52);

    n.insert(8);
    n.insert(100);
    n.insert(10);

    std::cout << n.find(100);

    return 0;
}
