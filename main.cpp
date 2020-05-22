#include "cube.hpp"
#include <iostream>
#include <cctype>

void simulateRubiksCube();

int main() {
    simulateRubiksCube();
    return 0;
}

void simulateRubiksCube() {
    Cube rubiks_cube;
    std::string algorithm;

    while (true) {
        std::cout << '\n';
        rubiks_cube.printCube();
        std::cout << '\n';

        std::cout << "Enter a move or algorithm to execute (Q to quit): ";
        std::getline(std::cin, algorithm);

        if (std::toupper(algorithm[0]) == 'Q') {
            break;
        }
        if(!rubiks_cube.applyAlgorithm(algorithm)) {
            std::cout << "\033[1;31mInvalid move(s).\033[0m" << '\n';
        }
    }
}
