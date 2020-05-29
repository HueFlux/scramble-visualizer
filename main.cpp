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
    auto start = std::chrono::high_resolution_clock::now();
    Cube rubiks_cube;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Cube construction time: " << duration.count() << " microseconds\n";
    return;
    std::string algorithm;
    algorithm = rubiks_cube.superflipAlgorithm();

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
