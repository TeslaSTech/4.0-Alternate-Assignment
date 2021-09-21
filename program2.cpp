#include <iostream>
#include "programs.h"

void fillName(std::string *n) {
    std::cout << "Please enter a name." << std::endl;
    std::cin >> *n;
}

void printBackwardsName(std::string &n) {
    for (int i = n.length() - 1; i >= 0; i--) {
        std::cout << n.at(i);
    }
    std::cout << std::endl;
}

void mainTwo() {
    std::string name;

    fillName(&name);
    printBackwardsName(name);

}