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
        std::cout << std::endl;
        rubiks_cube.printCube(true);
        std::cout << std::endl;

        std::cout << "Enter a move or algorithm to execute (Q to quit): ";
        std::getline(std::cin, algorithm);

        if (std::toupper(algorithm[0]) == 'Q') {
            break;
        }
        if(!rubiks_cube.applyAlgorithm(algorithm)) {
            std::cout << "Invalid move(s)." << std::endl;
        }
    }
}
