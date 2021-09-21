#include <iostream>
#include <vector>
#include "programs.h"

void getInput (int *l, int *w, int *h) { // Pass by Pointer
    std::vector<std::string> thingsToAskFor = { "length", "width", "height" };
    int temp;
    for (int i = 0; i < thingsToAskFor.size(); i++) {
        std::cout << "enter the " << thingsToAskFor.at(i) << " of the building: ";
        std::cin >> temp; 
        switch (i) {
            case 0:
                *l = temp;
                break;
            case 1:
                *w = temp;
                break;
            case 2:
                *h = temp;
                break;
            default:
                std::cout << "This is literally supposed to be impossible. HOW" << std::endl;
        }
    }
}

int calcCubicFeet(int &l, int &w, int &h) { // Pass by Reference
    return l * w * h;
}

void printOutVolume(int &v) { // My choice (Pass by Reference)
    std::cout << "The volume of the building is " << v << std::endl;
}

void mainOne() {
    int length = 0;
    int width = 0;
    int height = 0;
    int volume = 0;

    getInput(&length, &width, &height);
    volume = calcCubicFeet(length, width, height);
    printOutVolume(volume);
}

