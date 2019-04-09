#include "cube.hpp"

/* Integer values used to represent sticker colors
 * 0 = None
 * 1 = White
 * 2 = Yellow
 * 3 = Green
 * 4 = Blue
 * 5 = Orange
 * 6 = Red
 */

// Intializes the Cube face matrices to the standard Rubik's Cube
// color scheme with White on the top face and Green on the front face
Cube::Cube() :
    U_stickers {{
      {1, 1, 1},
      {1, 1, 1},
      {1, 1, 1}
    }},

    D_stickers {{
      {2, 2, 2},
      {2, 2, 2},
      {2, 2, 2}
    }},

    F_stickers {{
      {3, 3, 3},
      {3, 3, 3},
      {3, 3, 3}
    }},

    B_stickers {{
      {4, 4, 4},
      {4, 4, 4},
      {4, 4, 4}
    }},

    L_stickers {{
      {5, 5, 5},
      {5, 5, 5},
      {5, 5, 5}
    }},

    R_stickers {{
      {6, 6, 6},
      {6, 6, 6},
      {6, 6, 6}
    }}
{}

void Cube::RotateMatrixClockwise(std::array<std::array<int, N>, N> &mat) {
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
void Cube::RotateMatrixCounterClockwise(std::array<std::array<int, N>, N> &mat) {
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

void Cube::UMove() {
    RotateMatrixClockwise(U_stickers);

    // Rotate the first row of stickers for the F, R, B and L faces clockwise
    // relative to U face of cube
    std::array<int, N> temp = F_stickers[0];
    F_stickers[0] = R_stickers[0];
    R_stickers[0] = B_stickers[0];
    B_stickers[0] = L_stickers[0];
    L_stickers[0] = temp;
}

void Cube::UPrimeMove() {
    RotateMatrixCounterClockwise(U_stickers);

    // Rotate the first row of stickers for the F, R, B and L faces
    // counter-clockwise relative to U face of cube
    std::array<int, N> temp = F_stickers[0];
    F_stickers[0] = L_stickers[0];
    L_stickers[0] = B_stickers[0];
    B_stickers[0] = R_stickers[0];
    R_stickers[0] = temp;
}

void Cube::DMove() {
    RotateMatrixClockwise(D_stickers);

    // Rotate the last row of stickers for the F, R, B and L faces clockwise
    // relative to D face of cube
    std::array<int, N> temp = F_stickers[N-1];
    F_stickers[N-1] = L_stickers[N-1];
    L_stickers[N-1] = B_stickers[N-1];
    B_stickers[N-1] = R_stickers[N-1];
    R_stickers[N-1] = temp;
}

void Cube::DPrimeMove() {
    RotateMatrixCounterClockwise(D_stickers);

    // Rotate the first row of stickers for the F, R, B and L faces
    // counter-clockwise relative to D face of cube
    std::array<int, N> temp = F_stickers[N-1];
    F_stickers[N-1] = R_stickers[N-1];
    R_stickers[N-1] = B_stickers[N-1];
    B_stickers[N-1] = L_stickers[N-1];
    L_stickers[N-1] = temp;
}

void Cube::FMove() {

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
