#include "cube.hpp"
#include <iostream>
#include <cctype>
#include <vector>
#include <chrono>

int main() {
    Cube rubiks_cube;

    std::string algorithm;
    // algorithm = rubiks_cube.superflipAlgorithm();
    rubiks_cube.applyAlgorithm(algorithm);

    while (true) {
        std::cout << '\n';
        rubiks_cube.printCube();
        std::cout << '\n';

        std::cout << "Enter a move or algorithm to execute ('Q' to quit, '\\' to reset): ";
        std::getline(std::cin, algorithm);

        if (std::toupper(algorithm[0]) == 'Q') {
            break;
        }
        if (algorithm[0] == '\\') {
            rubiks_cube.reset();
            continue;
        }
        if(!rubiks_cube.applyAlgorithm(algorithm)) {
            std::cout << "\033[1;31mInvalid move(s).\033[0m" << '\n';
        }
    }
    
    return 0;
}
