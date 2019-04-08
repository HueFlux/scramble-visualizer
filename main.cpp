#include "cube.hpp"
#include <iostream>

using namespace std;

// Prints out matrix mat with spaces in between elements
// and each row on a new line
void printMatrix(const std::array<std::array<int, N>, N> &mat) {
    for (auto& row : mat) {
        for (auto& i : row) {
            cout << i << " ";
        }
        cout << endl;
    }
}

void PrintMatrixRotations(Cube &cube, std::array<std::array<int, N>, N> &mat) {
    cout << "Original Matrix:" << endl;
    printMatrix(mat);

    cube.RotateMatrixClockwise(mat);
    cout << "Matrix rotated 90 degrees clockwise:" << endl;
    printMatrix(mat);

    cube.RotateMatrixCounterClockwise(mat);
    cout << "Previous Matrix rotated 90 degrees counter-clockwise:" << endl;
    printMatrix(mat); // Should be identical to original matrix

}

int main() {
    Cube rubiks_cube;

    std::array<std::array<int, 3>, 3> matrix = {{
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9}
    }};

    PrintMatrixRotations(rubiks_cube, matrix);

    return 0;
}
