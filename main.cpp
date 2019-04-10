#include "cube.hpp"
#include <iostream>

using namespace std;

// Prints out matrix mat with spaces in between elements
// and each row on a new line
void PrintMatrix(const std::array<std::array<char, N>, N> &mat) {
    for (auto& row : mat) {
        for (auto& i : row) {
            cout << i << " ";
        }
        cout << endl;
    }
}

void PrintMatrixRotations(Cube &cube, std::array<std::array<char, N>, N> &mat) {
    cout << "Original Matrix:" << endl;
    PrintMatrix(mat);

    cube.RotateMatrixClockwise(mat);
    cout << "Matrix rotated 90 degrees clockwise:" << endl;
    PrintMatrix(mat);

    cube.RotateMatrixCounterClockwise(mat);
    cout << "Previous Matrix rotated 90 degrees counter-clockwise:" << endl;
    PrintMatrix(mat); // Should be identical to original matrix

}

int main() {
    Cube rubiks_cube;

    std::array<std::array<char, 3>, 3> matrix = {{
      {'A', 'B', 'C'},
      {'D', 'E', 'F'},
      {'G', 'H', 'I'}
    }};

    // PrintMatrixRotations(rubiks_cube, matrix);

    rubiks_cube.FMove();
    rubiks_cube.FPrimeMove();
    rubiks_cube.PrintCube();

    return 0;
}
