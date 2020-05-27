#include "cube.hpp"
#include <iostream>
#include <cctype>
#include <vector>
#include <chrono>

void simulateRubiksCube();
std::string superflipAlgorithm(int size);

int main() {
    simulateRubiksCube();
    return 0;
}

void simulateRubiksCube() {
    Cube<5> rubiks_cube;
    std::string algorithm;
    algorithm = superflipAlgorithm(rubiks_cube.SIZE);

    std::cout << "Superflip algorithm: " << algorithm << "\n";

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
}

std::string superflipAlgorithm(int size) {
    if (size == 0) {
        return "";
    }
    std::vector<std::string> superflip_moves = {"U", "R2", "F", "B", "R", "B2", "R", "U2", "L", "B2", "R", "U'", "D'", "R2", "F", "R'", "L", "B2", "U2", "F2"};

    std::string superflip_algorithm = "";

    for (auto move : superflip_moves) {
        superflip_algorithm += move + " ";
    }

    for (int i = 2; i <= size/2; i++) {
        for (auto move : superflip_moves) {
            if (move.length() == 1) {
                superflip_algorithm += std::to_string(i) + move + "w";
            }
            else if (move.length() == 2) {
                superflip_algorithm += std::to_string(i) + move[0] + "w" + move[1];
            }
            superflip_algorithm += " ";
        }
    }

    return superflip_algorithm;
}
