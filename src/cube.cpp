#include "cube.hpp"
#include <iostream>
#include <iomanip>
#include <array>
#include <vector>
#include <cctype>
#include <string>
#include <algorithm>

/* Char values used to represent sticker colors
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

    // Add outer block moves for 4x4x4 and up
    if (N > 3) {
        moveToFunction["UW"]  = [this] { this->UWMove(); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "UW";
            moveToFunction[move] = [this, i] { this->UWMove(i); };
        }

        moveToFunction["UW'"] = [this] { this->UWPrimeMove(); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "UW'";
            moveToFunction[move] = [this, i] { this->UWPrimeMove(i); };
        }

        moveToFunction["UW2"] = [this] { this->UW2Move(); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "UW2";
            moveToFunction[move] = [this, i] { this->UW2Move(i); };
        }

        moveToFunction["DW"]  = [this] { this->DWMove(); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "DW";
            moveToFunction[move] = [this, i] { this->DWMove(i); };
        }

        moveToFunction["DW'"] = [this] { this->DWPrimeMove(); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "DW'";
            moveToFunction[move] = [this, i] { this->DWPrimeMove(i); };
        }

        moveToFunction["DW2"] = [this] { this->DW2Move(); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "DW2";
            moveToFunction[move] = [this, i] { this->DW2Move(i); };
        }

        moveToFunction["FW"]  = [this] { this->FWMove(); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "FW";
            moveToFunction[move] = [this, i] { this->FWMove(i); };
        }

        moveToFunction["FW'"] = [this] { this->FWPrimeMove(); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "FW'";
            moveToFunction[move] = [this, i] { this->FWPrimeMove(i); };
        }

        moveToFunction["FW2"] = [this] { this->FW2Move(); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "FW2";
            moveToFunction[move] = [this, i] { this->FW2Move(i); };
        }

        moveToFunction["BW"]  = [this] { this->BWMove(); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "BW";
            moveToFunction[move] = [this, i] { this->BWMove(i); };
        }

        moveToFunction["BW'"] = [this] { this->BWPrimeMove(); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "BW'";
            moveToFunction[move] = [this, i] { this->BWPrimeMove(i); };
        }

        moveToFunction["BW2"] = [this] { this->BW2Move(); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "BW2";
            moveToFunction[move] = [this, i] { this->BW2Move(i); };
        }

        moveToFunction["LW"]  = [this] { this->LWMove(); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "LW";
            moveToFunction[move] = [this, i] { this->LWMove(i); };
        }

        moveToFunction["LW'"] = [this] { this->LWPrimeMove(); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "LW'";
            moveToFunction[move] = [this, i] { this->LWPrimeMove(i); };
        }

        moveToFunction["LW2"] = [this] { this->LW2Move(); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "LW2";
            moveToFunction[move] = [this, i] { this->LW2Move(i); };
        }

        moveToFunction["RW"]  = [this] { this->RWMove(); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "RW";
            moveToFunction[move] = [this, i] { this->RWMove(i); };
        }

        moveToFunction["RW'"] = [this] { this->RWPrimeMove(); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "RW'";
            moveToFunction[move] = [this, i] { this->RWPrimeMove(i); };
        }

        moveToFunction["RW2"] = [this] { this->RW2Move(); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "RW2";
            moveToFunction[move] = [this, i] { this->RW2Move(i); };
        }
    }
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

std::array<char, Cube::N> Cube::getColumnValues(const Cube::FaceStickers &mat, int col) const {
    std::array<char, N> column_array = {};
    for (int i = 0; i < N; i++) {
        column_array[i] = mat[i][col];
    }
    return column_array;
}

std::array<char, Cube::N> Cube::getColumnValuesReverse(const Cube::FaceStickers &mat, int col) const {
    std::array<char, N> column_array = {};
    for (int i = 0; i < N; i++) {
        column_array[i] = mat[N-1-i][col];
    }
    return column_array;
}

std::array<char*, Cube::N> Cube::getColumnPointers(Cube::FaceStickers &mat, int col) const {
    std::array<char*, N> column_array = {};
    for (int i = 0; i < N; i++) {
        column_array[i] = &mat[i][col];
    }
    return column_array;
}

std::array<char*, Cube::N> Cube::getColumnPointersReverse(Cube::FaceStickers &mat, int col) const {
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

void Cube::UWMove(int slices) {
    UMove();

    for(int i = 1; i < slices; i++) {
        rotateSliceY(i);
    }
}

void Cube::UWPrimeMove(int slices) {
    UPrimeMove();

    for(int i = 1; i < slices; i++) {
        rotateSliceYPrime(i);
    }
}

void Cube::UW2Move(int slices) {
    U2Move();

    for(int i = 1; i < slices; i++) {
        rotateSliceY2(i);
    }
}

void Cube::DWMove(int slices) {
    DMove();

    for(int i = 1; i < slices; i++) {
        rotateSliceYPrime(N-1 - i);
    }
}

void Cube::DWPrimeMove(int slices) {
    DPrimeMove();

    for(int i = 1; i < slices; i++) {
        rotateSliceY(N-1 - i);
    }
}

void Cube::DW2Move(int slices) {
    D2Move();

    for(int i = 1; i < slices; i++) {
        rotateSliceY2(N-1 - i);
    }
}

void Cube::FWMove(int slices) {
    FMove();

    for(int i = 1; i < slices; i++) {
        rotateSliceZ(N-1 - i);
    }
}

void Cube::FWPrimeMove(int slices) {
    FPrimeMove();

    for(int i = 1; i < slices; i++) {
        rotateSliceZPrime(N-1 - i);
    }
}

void Cube::FW2Move(int slices) {
    F2Move();

    for(int i = 1; i < slices; i++) {
        rotateSliceZ2(N-1 - i);
    }
}

void Cube::BWMove(int slices) {
    BMove();

    for(int i = 1; i < slices; i++) {
        rotateSliceZPrime(i);
    }
}

void Cube::BWPrimeMove(int slices) {
    BPrimeMove();

    for(int i = 1; i < slices; i++) {
        rotateSliceZ(i);
    }
}

void Cube::BW2Move(int slices) {
    B2Move();

    for(int i = 1; i < slices; i++) {
        rotateSliceZ2(i);
    }
}

void Cube::RWMove(int slices) {
    RMove();

    for(int i = 1; i < slices; i++) {
        rotateSliceX(N-1 - i);
    }
}

void Cube::RWPrimeMove(int slices) {
    RPrimeMove();

    for(int i = 1; i < slices; i++) {
        rotateSliceXPrime(N-1 - i);
    }
}

void Cube::RW2Move(int slices) {
    R2Move();

    for(int i = 1; i < slices; i++) {
        rotateSliceX2(N-1 - i);
    }
}

void Cube::LWMove(int slices) {
    LMove();

    for(int i = 1; i < slices; i++) {
        rotateSliceXPrime(i);
    }
}

void Cube::LWPrimeMove(int slices) {
    LPrimeMove();

    for(int i = 1; i < slices; i++) {
        rotateSliceX(i);
    }
}

void Cube::LW2Move(int slices) {
    L2Move();

    for(int i = 1; i < slices; i++) {
        rotateSliceX2(i);
    }
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

void Cube::printCube(bool color_output) const {
    for (int i = 0; i < N; i++) {
        std::cout << std::setw(N*2 + 1) << ' ';
        for (int j = 0; j < N; j++) {
            std::string sticker = color_output ? getStickerColor(U_stickers[i][j])
                                               : std::string(1, U_stickers[i][j]);
            std::cout << sticker << ' ';
        }
        std::cout << '\n';
    }

    std::cout << '\n';

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::string sticker = color_output ? getStickerColor(L_stickers[i][j])
                                               : std::string(1, L_stickers[i][j]);
            std::cout << sticker << ' ';
        }

        std::cout << ' ';

        for (int j = 0; j < N; j++) {
            std::string sticker = color_output ? getStickerColor(F_stickers[i][j])
                                               : std::string(1, F_stickers[i][j]);
            std::cout << sticker << ' ';
        }

        std::cout << ' ';

        for (int j = 0; j < N; j++) {
            std::string sticker = color_output ? getStickerColor(R_stickers[i][j])
                                               : std::string(1, R_stickers[i][j]);
            std::cout << sticker << ' ';
        }

        std::cout << ' ';

        for (int j = 0; j < N; j++) {
            std::string sticker = color_output ? getStickerColor(B_stickers[i][j])
                                               : std::string(1, B_stickers[i][j]);
            std::cout << sticker << ' ';
        }
        std::cout << '\n';
    }

    std::cout << '\n';

    for (int i = 0; i < N; i++) {
        std::cout << std::setw(N*2 + 1) << ' ';
        for (int j = 0; j < N; j++) {
            std::string sticker = color_output ? getStickerColor(D_stickers[i][j])
                                               : std::string(1, D_stickers[i][j]);
            std::cout << sticker << ' ';
        }
        std::cout << '\n';
    }
}

std::string Cube::getStickerColor(char sticker) const {
    switch (sticker) {
        case 'W':
            return "\033[1;37m█\033[0m";
        case 'Y':
            return "\033[1;33m█\033[0m";
        case 'G':
            return "\033[1;32m█\033[0m";
        case 'B':
            return "\033[1;34m█\033[0m";
        case 'O':
            return "\033[1;35m█\033[0m";
        case 'R':
            return "\033[1;31m█\033[0m";
        default:
            return std::to_string(sticker);
    }
}
