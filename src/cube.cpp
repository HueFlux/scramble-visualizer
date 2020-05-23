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
        moveToFunction["UW"]  = [this] { this->UMove(2); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "UW";
            moveToFunction[move] = [this, i] { this->UMove(i); };
        }

        moveToFunction["UW'"] = [this] { this->UPrimeMove(2); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "UW'";
            moveToFunction[move] = [this, i] { this->UPrimeMove(i); };
        }

        moveToFunction["UW2"] = [this] { this->U2Move(2); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "UW2";
            moveToFunction[move] = [this, i] { this->U2Move(i); };
        }

        moveToFunction["DW"]  = [this] { this->DMove(2); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "DW";
            moveToFunction[move] = [this, i] { this->DMove(i); };
        }

        moveToFunction["DW'"] = [this] { this->DPrimeMove(2); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "DW'";
            moveToFunction[move] = [this, i] { this->DPrimeMove(i); };
        }

        moveToFunction["DW2"] = [this] { this->D2Move(2); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "DW2";
            moveToFunction[move] = [this, i] { this->D2Move(i); };
        }

        moveToFunction["FW"]  = [this] { this->FMove(2); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "FW";
            moveToFunction[move] = [this, i] { this->FMove(i); };
        }

        moveToFunction["FW'"] = [this] { this->FPrimeMove(2); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "FW'";
            moveToFunction[move] = [this, i] { this->FPrimeMove(i); };
        }

        moveToFunction["FW2"] = [this] { this->F2Move(2); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "FW2";
            moveToFunction[move] = [this, i] { this->F2Move(i); };
        }

        moveToFunction["BW"]  = [this] { this->BMove(2); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "BW";
            moveToFunction[move] = [this, i] { this->BMove(i); };
        }

        moveToFunction["BW'"] = [this] { this->BPrimeMove(2); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "BW'";
            moveToFunction[move] = [this, i] { this->BPrimeMove(i); };
        }

        moveToFunction["BW2"] = [this] { this->B2Move(2); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "BW2";
            moveToFunction[move] = [this, i] { this->B2Move(i); };
        }

        moveToFunction["LW"]  = [this] { this->LMove(2); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "LW";
            moveToFunction[move] = [this, i] { this->LMove(i); };
        }

        moveToFunction["LW'"] = [this] { this->LPrimeMove(2); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "LW'";
            moveToFunction[move] = [this, i] { this->LPrimeMove(i); };
        }

        moveToFunction["LW2"] = [this] { this->L2Move(2); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "LW2";
            moveToFunction[move] = [this, i] { this->L2Move(i); };
        }

        moveToFunction["RW"]  = [this] { this->RMove(2); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "RW";
            moveToFunction[move] = [this, i] { this->RMove(i); };
        }

        moveToFunction["RW'"] = [this] { this->RPrimeMove(2); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "RW'";
            moveToFunction[move] = [this, i] { this->RPrimeMove(i); };
        }

        moveToFunction["RW2"] = [this] { this->R2Move(2); };
        for (int i = 2; i < N-1; i++) {
            std::string move = std::to_string(i) + "RW2";
            moveToFunction[move] = [this, i] { this->R2Move(i); };
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

void Cube::reset() {
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

void Cube::UMove(int slices) {
    rotateMatrixClockwise(U_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceY(i);
    }
}

void Cube::UPrimeMove(int slices) {
    rotateMatrixCounterClockwise(U_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceYPrime(i);
    }
}

void Cube::U2Move(int slices) {
    rotateMatrix180(U_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceY2(i);
    }
}

void Cube::DMove(int slices) {
    rotateMatrixClockwise(D_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceYPrime(N-1 - i);
    }
}

void Cube::DPrimeMove(int slices) {
    rotateMatrixCounterClockwise(D_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceY(N-1 - i);
    }
}

void Cube::D2Move(int slices) {
    rotateMatrix180(D_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceY2(N-1 - i);
    }
}

void Cube::FMove(int slices) {
    rotateMatrixClockwise(F_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceZ(N-1 - i);
    }
}

void Cube::FPrimeMove(int slices) {
    rotateMatrixCounterClockwise(F_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceZPrime(N-1 - i);
    }
}

void Cube::F2Move(int slices) {
    rotateMatrix180(F_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceZ2(N-1 - i);
    }
}

void Cube::BMove(int slices) {
    rotateMatrixClockwise(B_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceZPrime(i);
    }

}

void Cube::BPrimeMove(int slices) {
    rotateMatrixCounterClockwise(B_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceZ(i);
    }
}

void Cube::B2Move(int slices) {
    rotateMatrix180(B_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceZ2(i);
    }
}

void Cube::RMove(int slices) {
    rotateMatrixClockwise(R_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceX(N-1 - i);
    }
}

void Cube::RPrimeMove(int slices) {
    rotateMatrixCounterClockwise(R_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceXPrime(N-1 - i);
    }
}

void Cube::R2Move(int slices) {
    rotateMatrix180(R_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceX2(N-1 - i);
    }
}

void Cube::LMove(int slices) {
    rotateMatrixClockwise(L_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceXPrime(i);
    }
}

void Cube::LPrimeMove(int slices) {
    rotateMatrixCounterClockwise(L_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceX(i);
    }
}

void Cube::L2Move(int slices) {
    rotateMatrix180(L_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceX2(i);
    }
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
    // Rotate the appropriate columns of stickers for the U, F, D, and B
    // faces clockwise relative to R face of cube
    std::array<char, N> temp = getColumnValues(U_stickers, col);
    copyValues(getColumnPointers(U_stickers, col), getColumnValues(F_stickers, col));
    copyValues(getColumnPointers(F_stickers, col), getColumnValues(D_stickers, col));
    copyValues(getColumnPointers(D_stickers, col), getColumnValuesReverse(B_stickers, N-1 - col));
    copyValues(getColumnPointersReverse(B_stickers, N-1 - col), temp);
}

void Cube::rotateSliceXPrime(int col) {
    // Rotate the appropriate columns of stickers for the U, F, D, and B
    // faces counter-clockwise relative to R face of cube
    std::array<char, N> temp = getColumnValues(U_stickers, col);
    copyValues(getColumnPointers(U_stickers, col), getColumnValuesReverse(B_stickers, N-1 - col));
    copyValues(getColumnPointersReverse(B_stickers, N-1 - col), getColumnValues(D_stickers, col));
    copyValues(getColumnPointers(D_stickers, col), getColumnValues(F_stickers, col));
    copyValues(getColumnPointers(F_stickers, col), temp);
}

void Cube::rotateSliceX2(int col) {
    // Swap the appropriate columns of stickers for the U, F, D, and B faces
    std::array<char, N> temp = getColumnValues(U_stickers, col);
    copyValues(getColumnPointers(U_stickers, col), getColumnValues(D_stickers, col));
    copyValues(getColumnPointers(D_stickers, col), temp);
    temp = getColumnValuesReverse(F_stickers, col);
    copyValues(getColumnPointers(F_stickers, col), getColumnValuesReverse(B_stickers, N-1 - col));
    copyValues(getColumnPointers(B_stickers, N-1 - col), temp);
}

void Cube::rotateSliceY(int row) {
    // Rotate the appropriate rows of stickers for the F, R, B and L faces clockwise
    // relative to U face of cube
    std::array<char, N> temp = F_stickers[row];
    F_stickers[row] = R_stickers[row];
    R_stickers[row] = B_stickers[row];
    B_stickers[row] = L_stickers[row];
    L_stickers[row] = temp;
}

void Cube::rotateSliceYPrime(int row) {
    // Rotate the appropriate rows of stickers for the F, R, B and L faces
    // counter-clockwise relative to U face of cube
    std::array<char, N> temp = F_stickers[row];
    F_stickers[row] = L_stickers[row];
    L_stickers[row] = B_stickers[row];
    B_stickers[row] = R_stickers[row];
    R_stickers[row] = temp;
}

void Cube::rotateSliceY2(int row) {
    // Swap the appropriate rows of stickers for the F, R, B and L faces
    std::swap(F_stickers[row], B_stickers[row]);
    std::swap(L_stickers[row], R_stickers[row]);
}

void Cube::rotateSliceZ(int row) {
    // Rotate the appropriate rows/columns of stickers for the U, R, D, and L
    // faces clockwise relative to F face of cube
    std::array<char, N> temp = U_stickers[row];
    U_stickers[row] = getColumnValuesReverse(L_stickers, row);
    copyValues(getColumnPointers(L_stickers, row), D_stickers[N-1 - row]);
    D_stickers[N-1 - row] = getColumnValuesReverse(R_stickers, N-1 - row);
    copyValues(getColumnPointers(R_stickers, N-1 - row), temp);
}

void Cube::rotateSliceZPrime(int row) {
    // Rotate the appropriate rows/columns of stickers for the U, R, D, and L
    // faces counter-clockwise relative to F face of cube
    std::array<char, N> temp = U_stickers[row];
    U_stickers[row] = getColumnValues(R_stickers, N-1 - row);
    copyValues(getColumnPointersReverse(R_stickers, N-1 - row), D_stickers[N-1 - row]);
    D_stickers[N-1 - row] = getColumnValues(L_stickers, row);
    copyValues(getColumnPointersReverse(L_stickers, row), temp);
}

void Cube::rotateSliceZ2(int row) {
    // Swap the appropriate rows/columns of stickers for the U, R, D, and L faces
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
