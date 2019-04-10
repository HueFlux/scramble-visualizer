#include "cube.hpp"
#include <iostream>
#include <iomanip>

/* Char values used to represent sticker colors
 * 'N' = None
 * 'W' = White
 * 'Y' = Yellow
 * 'G' = Green
 * 'B' = Blue
 * 'O' = Orange
 * 'R' = Red
 */

// Intializes the Cube face matrices to the standard Rubik's Cube
// color scheme with White on the top face and Green on the front face
Cube::Cube() :
    U_stickers {{
      {'W', 'W', 'W'},
      {'W', 'W', 'W'},
      {'W', 'W', 'W'}
    }},

    D_stickers {{
      {'Y', 'Y', 'Y'},
      {'Y', 'Y', 'Y'},
      {'Y', 'Y', 'Y'}
    }},

    F_stickers {{
      {'G', 'G', 'G'},
      {'G', 'G', 'G'},
      {'G', 'G', 'G'}
    }},

    B_stickers {{
      {'B', 'B', 'B'},
      {'B', 'B', 'B'},
      {'B', 'B', 'B'}
    }},

    L_stickers {{
      {'O', 'O', 'O'},
      {'O', 'O', 'O'},
      {'O', 'O', 'O'}
    }},

    R_stickers {{
      {'R', 'R', 'R'},
      {'R', 'R', 'R'},
      {'R', 'R', 'R'}
    }}
{}

void Cube::RotateMatrixClockwise(std::array<std::array<char, N>, N> &mat) {
    // Consider all squares one by one
    for (int x = 0; x < N / 2; x++) {
        // Consider elements in group of 4 in
        // current square
        for (int y = x; y < N-x-1; y++) {
            // store current cell in temp variable
            int temp = mat[x][y];

            // move values from left to top
            mat[x][y] = mat[N-1-y][x];

            // move values from bottom to left
            mat[N-1-y][x] = mat[N-1-x][N-1-y];

            // move values from right to bottom
            mat[N-1-x][N-1-y] = mat[y][N-1-x];

            // assign temp to right
            mat[y][N-1-x] = temp;
        }
    }
}

// https://www.geeksforgeeks.org/inplace-rotate-square-matrix-by-90-degrees/
void Cube::RotateMatrixCounterClockwise(std::array<std::array<char, N>, N> &mat) {
    // Consider all squares one by one
    for (int x = 0; x < N / 2; x++) {
        // Consider elements in group of 4 in
        // current square
        for (int y = x; y < N-x-1; y++) {
            // store current cell in temp variable
            int temp = mat[x][y];

            // move values from right to top
            mat[x][y] = mat[y][N-1-x];

            // move values from bottom to right
            mat[y][N-1-x] = mat[N-1-x][N-1-y];

            // move values from left to bottom
            mat[N-1-x][N-1-y] = mat[N-1-y][x];

            // assign temp to left
            mat[N-1-y][x] = temp;
        }
    }
}

std::array<char, N> Cube::GetColumnValues(std::array<std::array<char, N>, N> &mat, int col) {
    std::array<char, N> column_array = {};
    for (int i = 0; i < N; i++) {
        column_array[i] = mat[i][col];
    }
    return column_array;
}

std::array<char, N> Cube::GetColumnValuesReverse(std::array<std::array<char, N>, N> &mat, int col) {
    std::array<char, N> column_array = {};
    for (int i = 0; i < N; i++) {
        column_array[i] = mat[N-1-i][col];
    }
    return column_array;
}

std::array<char*, N> Cube::GetColumnPointers(std::array<std::array<char, N>, N> &mat, int col) {
    std::array<char*, N> column_array = {};
    for (int i = 0; i < N; i++) {
        column_array[i] = &mat[i][col];
    }
    return column_array;
}

std::array<char*, N> Cube::GetColumnPointersReverse(std::array<std::array<char, N>, N> &mat, int col) {
    std::array<char*, N> column_array = {};
    for (int i = 0; i < N; i++) {
        column_array[i] = &mat[N-1-i][col];
    }
    return column_array;
}

void Cube::CopyValues(std::array<char*, N> pointers, const std::array<char, N>& values) {
    for(int i = 0; i < N; i++) {
        *pointers[i] = values[i];
    }
}

void Cube::UMove() {
    RotateMatrixClockwise(U_stickers);

    // Rotate the first row of stickers for the F, R, B and L faces clockwise
    // relative to U face of cube
    std::array<char, N> temp = F_stickers[0];
    F_stickers[0] = R_stickers[0];
    R_stickers[0] = B_stickers[0];
    B_stickers[0] = L_stickers[0];
    L_stickers[0] = temp;
}

void Cube::UPrimeMove() {
    RotateMatrixCounterClockwise(U_stickers);

    // Rotate the first row of stickers for the F, R, B and L faces
    // counter-clockwise relative to U face of cube
    std::array<char, N> temp = F_stickers[0];
    F_stickers[0] = L_stickers[0];
    L_stickers[0] = B_stickers[0];
    B_stickers[0] = R_stickers[0];
    R_stickers[0] = temp;
}

void Cube::DMove() {
    RotateMatrixClockwise(D_stickers);

    // Rotate the last row of stickers for the F, R, B and L faces clockwise
    // relative to D face of cube
    std::array<char, N> temp = F_stickers[N-1];
    F_stickers[N-1] = L_stickers[N-1];
    L_stickers[N-1] = B_stickers[N-1];
    B_stickers[N-1] = R_stickers[N-1];
    R_stickers[N-1] = temp;
}

void Cube::DPrimeMove() {
    RotateMatrixCounterClockwise(D_stickers);

    // Rotate the first row of stickers for the F, R, B and L faces
    // counter-clockwise relative to D face of cube
    std::array<char, N> temp = F_stickers[N-1];
    F_stickers[N-1] = R_stickers[N-1];
    R_stickers[N-1] = B_stickers[N-1];
    B_stickers[N-1] = L_stickers[N-1];
    L_stickers[N-1] = temp;
}

void Cube::FMove() {
    RotateMatrixClockwise(F_stickers);

    // Rotate the appropriat row/column of stickers for the U, R, D, and L
    // faces clockwise relative to F face of cube
    std::array<char, N> temp = U_stickers[N-1];
    U_stickers[N-1] = GetColumnValuesReverse(L_stickers, N-1);
    CopyValues(GetColumnPointers(L_stickers, N-1), D_stickers[0]);
    D_stickers[0] = GetColumnValuesReverse(R_stickers, N-1);
    CopyValues(GetColumnPointers(R_stickers, 0), temp);
}

void Cube::FPrimeMove() {

}

void Cube::BMove() {

}

void Cube::BPrimeMove() {

}

void Cube::RMove() {

}

void Cube::RPrimeMove() {

}

void Cube::LMove() {

}

void Cube::LPrimeMove() {

}

void Cube::PrintCube() const {
    for (int i = 0; i < N; i++) {
        std::cout << std::setw(6) << " ";
        for (int j = 0; j < N; j++) {
            std::cout << U_stickers[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << L_stickers[i][j] << " ";
        }
        for (int j = 0; j < N; j++) {
            std::cout << F_stickers[i][j] << " ";
        }
        for (int j = 0; j < N; j++) {
            std::cout << R_stickers[i][j] << " ";
        }
        for (int j = 0; j < N; j++) {
            std::cout << B_stickers[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < N; i++) {
        std::cout << std::setw(6) << " ";
        for (int j = 0; j < N; j++) {
            std::cout << D_stickers[i][j] << " ";
        }
        std::cout << std::endl;
    }

}
