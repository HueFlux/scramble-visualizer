#include "cube.hpp"
#include <iostream>
#include <iomanip>
#include <array>
#include <vector>
#include <cctype>
#include <string>
#include <algorithm>

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
Cube::Cube() {
    for (auto& sticker : U_stickers) {
        sticker.fill('W');
    }
    for (auto& sticker : D_stickers) {
        sticker.fill('Y');
    }
    for (auto& sticker : F_stickers) {
        sticker.fill('G');
    }
    for (auto& sticker : B_stickers) {
        sticker.fill('B');
    }
    for (auto& sticker : L_stickers) {
        sticker.fill('O');
    }
    for (auto& sticker : R_stickers) {
        sticker.fill('R');
    }

    moveToFunction["U"]  = [this] { this->UMove(); };
    moveToFunction["U'"] = [this] { this->UPrimeMove(); };
    moveToFunction["U2"] = [this] { this->U2Move(); };
    moveToFunction["D"]  = [this] { this->DMove(); };
    moveToFunction["D'"] = [this] { this->DPrimeMove(); };
    moveToFunction["D2"] = [this] { this->D2Move(); };
    moveToFunction["F"]  = [this] { this->FMove(); };
    moveToFunction["F'"] = [this] { this->FPrimeMove(); };
    moveToFunction["F2"] = [this] { this->F2Move(); };
    moveToFunction["B"]  = [this] { this->BMove(); };
    moveToFunction["B'"] = [this] { this->BPrimeMove(); };
    moveToFunction["B2"] = [this] { this->B2Move(); };
    moveToFunction["L"]  = [this] { this->LMove(); };
    moveToFunction["L'"] = [this] { this->LPrimeMove(); };
    moveToFunction["L2"] = [this] { this->L2Move(); };
    moveToFunction["R"]  = [this] { this->RMove(); };
    moveToFunction["R'"] = [this] { this->RPrimeMove(); };
    moveToFunction["R2"] = [this] { this->R2Move(); };
}

const Cube::FaceStickers& Cube::getUStickers() const {
    return U_stickers;
}

const Cube::FaceStickers& Cube::getDStickers() const {
    return D_stickers;
}

const Cube::FaceStickers& Cube::getFStickers() const {
    return F_stickers;
}

const Cube::FaceStickers& Cube::getBStickers() const {
    return B_stickers;
}

const Cube::FaceStickers& Cube::getLStickers() const {
    return L_stickers;
}

const Cube::FaceStickers& Cube::getRStickers() const {
    return R_stickers;
}

void Cube::rotateMatrixClockwise(Cube::FaceStickers &mat) {
    // Consider all squares one by one
    for (int x = 0; x < N/2; x++) {
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
void Cube::rotateMatrixCounterClockwise(Cube::FaceStickers &mat) {
    // Consider all squares one by one
    for (int x = 0; x < N/2; x++) {
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

void Cube::rotateMatrix180(Cube::FaceStickers &mat) {
    for (int i = 0; i < N/2; i++) {
		for (int j = 0; j < N; j++) {
			std::swap(mat[i][j], mat[N-i-1][N-j-1]);
        }
    }
    // Reverse middle row if matrix has odd dimensions
    if (N & 1) {
		for (int j = 0; j < N/2; j++)
			std::swap(mat[N/2][j], mat[N/2][N-j-1]);
	}
}

void Cube::rotateSliceX(int col) {
    std::array<char, N> temp = getColumnValues(U_stickers, col);
    copyValues(getColumnPointers(U_stickers, col), getColumnValues(F_stickers, col));
    copyValues(getColumnPointers(F_stickers, col), getColumnValues(D_stickers, col));
    copyValues(getColumnPointers(D_stickers, col), getColumnValuesReverse(B_stickers, N-1 - col));
    copyValues(getColumnPointersReverse(B_stickers, N-1 - col), temp);
}

void Cube::rotateSliceXPrime(int col) {
    std::array<char, N> temp = getColumnValues(U_stickers, col);
    copyValues(getColumnPointers(U_stickers, col), getColumnValuesReverse(B_stickers, N-1 - col));
    copyValues(getColumnPointersReverse(B_stickers, N-1 - col), getColumnValues(D_stickers, col));
    copyValues(getColumnPointers(D_stickers, col), getColumnValues(F_stickers, col));
    copyValues(getColumnPointers(F_stickers, col), temp);
}

void Cube::rotateSliceX2(int col) {
    std::array<char, N> temp = getColumnValues(U_stickers, col);
    copyValues(getColumnPointers(U_stickers, col), getColumnValues(D_stickers, col));
    copyValues(getColumnPointers(D_stickers, col), temp);
    temp = getColumnValuesReverse(F_stickers, col);
    copyValues(getColumnPointers(F_stickers, col), getColumnValuesReverse(B_stickers, N-1 - col));
    copyValues(getColumnPointers(B_stickers, N-1 - col), temp);
}

void Cube::rotateSliceY(int row) {
    std::array<char, N> temp = F_stickers[row];
    F_stickers[row] = R_stickers[row];
    R_stickers[row] = B_stickers[row];
    B_stickers[row] = L_stickers[row];
    L_stickers[row] = temp;
}

void Cube::rotateSliceYPrime(int row) {
    std::array<char, N> temp = F_stickers[row];
    F_stickers[row] = L_stickers[row];
    L_stickers[row] = B_stickers[row];
    B_stickers[row] = R_stickers[row];
    R_stickers[row] = temp;
}

void Cube::rotateSliceY2(int row) {
    std::swap(F_stickers[row], B_stickers[row]);
    std::swap(L_stickers[row], R_stickers[row]);
}

void Cube::rotateSliceZ(int row) {
    std::array<char, N> temp = U_stickers[row];
    U_stickers[row] = getColumnValuesReverse(L_stickers, row);
    copyValues(getColumnPointers(L_stickers, row), D_stickers[N-1 - row]);
    D_stickers[N-1 - row] = getColumnValuesReverse(R_stickers, N-1 - row);
    copyValues(getColumnPointers(R_stickers, N-1 - row), temp);
}

void Cube::rotateSliceZPrime(int row) {
    std::array<char, N> temp = U_stickers[row];
    U_stickers[row] = getColumnValues(R_stickers, N-1 - row);
    copyValues(getColumnPointersReverse(R_stickers, N-1 - row), D_stickers[N-1 - row]);
    D_stickers[N-1 - row] = getColumnValues(L_stickers, row);
    copyValues(getColumnPointersReverse(L_stickers, row), temp);
}

void Cube::rotateSliceZ2(int row) {
    std::swap(U_stickers[row], D_stickers[N-1 - row]);
    std::reverse(std::begin(U_stickers[row]), std::end(U_stickers[row]));
    std::reverse(std::begin(D_stickers[N-1 - row]), std::end(D_stickers[N-1 - row]));

    std::array<char, N> temp = getColumnValuesReverse(L_stickers, row);
    copyValues(getColumnPointers(L_stickers, row), getColumnValuesReverse(R_stickers, N-1 - row));
    copyValues(getColumnPointers(R_stickers, N-1 - row), temp);
}

std::array<char, Cube::N> Cube::getColumnValues(Cube::FaceStickers &mat, int col) {
    std::array<char, N> column_array = {};
    for (int i = 0; i < N; i++) {
        column_array[i] = mat[i][col];
    }
    return column_array;
}

std::array<char, Cube::N> Cube::getColumnValuesReverse(Cube::FaceStickers &mat, int col) {
    std::array<char, N> column_array = {};
    for (int i = 0; i < N; i++) {
        column_array[i] = mat[N-1-i][col];
    }
    return column_array;
}

std::array<char*, Cube::N> Cube::getColumnPointers(Cube::FaceStickers &mat, int col) {
    std::array<char*, N> column_array = {};
    for (int i = 0; i < N; i++) {
        column_array[i] = &mat[i][col];
    }
    return column_array;
}

std::array<char*, Cube::N> Cube::getColumnPointersReverse(Cube::FaceStickers &mat, int col) {
    std::array<char*, N> column_array = {};
    for (int i = 0; i < N; i++) {
        column_array[i] = &mat[N-1-i][col];
    }
    return column_array;
}

void Cube::copyValues(std::array<char*, N> pointers, const std::array<char, N>& values) {
    for(int i = 0; i < N; i++) {
        *pointers[i] = values[i];
    }
}

void Cube::UMove() {
    rotateMatrixClockwise(U_stickers);

    // Rotate the first row of stickers for the F, R, B and L faces clockwise
    // relative to U face of cube
    rotateSliceY(0);
}

void Cube::UPrimeMove() {
    rotateMatrixCounterClockwise(U_stickers);

    // Rotate the first row of stickers for the F, R, B and L faces
    // counter-clockwise relative to U face of cube
    rotateSliceYPrime(0);
}

void Cube::U2Move() {
    rotateMatrix180(U_stickers);

    // Swap the first row of stickers for the F, R, B and L faces
    rotateSliceY2(0);
}

void Cube::DMove() {
    rotateMatrixClockwise(D_stickers);

    // Rotate the last row of stickers for the F, R, B and L faces clockwise
    // relative to D face of cube
    rotateSliceYPrime(N-1);
}

void Cube::DPrimeMove() {
    rotateMatrixCounterClockwise(D_stickers);

    // Rotate the last row of stickers for the F, R, B and L faces
    // counter-clockwise relative to D face of cube
    rotateSliceY(N-1);
}

void Cube::D2Move() {
    rotateMatrix180(D_stickers);

    // Swap the last row of stickers for the F, R, B and L faces
    rotateSliceY2(N-1);
}

void Cube::FMove() {
    rotateMatrixClockwise(F_stickers);

    // Rotate the appropriate row/column of stickers for the U, R, D, and L
    // faces clockwise relative to F face of cube
    rotateSliceZ(N-1);
}

void Cube::FPrimeMove() {
    rotateMatrixCounterClockwise(F_stickers);

    // Rotate the appropriate row/column of stickers for the U, R, D, and L
    // faces counter-clockwise relative to F face of cube
    rotateSliceZPrime(N-1);
}

void Cube::F2Move() {
    rotateMatrix180(F_stickers);

    // Swap the appropriate row/column of stickers for the U, R, D, and L faces
    rotateSliceZ2(N-1);
}

void Cube::BMove() {
    rotateMatrixClockwise(B_stickers);

    // Rotate the appropriate row/column of stickers for the U, R, D, and L
    // faces clockwise relative to B face of cube
    rotateSliceZPrime(0);

}

void Cube::BPrimeMove() {
    rotateMatrixCounterClockwise(B_stickers);

    // Rotate the appropriate row/column of stickers for the U, R, D, and L
    // faces counter-clockwise relative to B face of cube
    rotateSliceZ(0);
}

void Cube::B2Move() {
    rotateMatrix180(B_stickers);

    // Swap the appropriate row/column of stickers for the U, R, D, and L faces
    rotateSliceZ2(0);
}

void Cube::RMove() {
    rotateMatrixClockwise(R_stickers);

    // Rotate the appropriate column of stickers for the U, F, D, and B
    // faces clockwise relative to R face of cube
    rotateSliceX(N-1);

}

void Cube::RPrimeMove() {
    rotateMatrixCounterClockwise(R_stickers);

    // Rotate the appropriate column of stickers for the U, F, D, and B
    // faces counter-clockwise relative to R face of cube
    rotateSliceXPrime(N-1);
}

void Cube::R2Move() {
    rotateMatrix180(R_stickers);

    // Swap the appropriate column of stickers for the U, F, D, and B faces
    rotateSliceX2(N-1);
}

void Cube::LMove() {
    rotateMatrixClockwise(L_stickers);

    // Rotate the appropriate column of stickers for the U, F, D, and B
    // faces clockwise relative to L face of cube
    rotateSliceXPrime(0);
}

void Cube::LPrimeMove() {
    rotateMatrixCounterClockwise(L_stickers);

    // Rotate the appropriate column of stickers for the U, F, D, and B
    // faces counter-clockwise relative to L face of cube
    rotateSliceX(0);
}

void Cube::L2Move() {
    rotateMatrix180(L_stickers);

    // Swap the appropriate column of stickers for the U, F, D, and B faces
    rotateSliceX2(0);
}

bool Cube::applyAlgorithm(const std::string &algorithm) {
    std::vector<std::string> moves;
    std::string current_move = "";
    // Parse moves in algorithm separated by spaces
    for (int i = 0; i < algorithm.length(); i++) {
        if (std::toupper(algorithm[i]) == ' ') {
            moves.push_back(current_move);
            current_move = "";
            continue;
        }
        current_move += std::toupper(algorithm[i]);
    }
    // If algorithm does not end with space, push back last move
    if (current_move.length() > 0) {
        moves.push_back(current_move);
    }
    // Execute moves
    for (std::string move : moves) {
        try {
            moveToFunction.at(move)();
        } catch (...) {
            return false;
        }
    }
    return true;
}

void Cube::printCube() const {
    for (int i = 0; i < N; i++) {
        std::cout << std::setw(N*2) << " ";
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
        std::cout << std::setw(N*2) << " ";
        for (int j = 0; j < N; j++) {
            std::cout << D_stickers[i][j] << " ";
        }
        std::cout << std::endl;
    }

}
