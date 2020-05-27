#ifndef CUBE_HPP
#define CUBE_HPP

#include <array>
#include <unordered_map>
#include <string>
#include <functional>

#include <iostream>
#include <iomanip>
#include <cctype>
#include <vector>
#include <algorithm>

template<size_t SIZE>
class Cube {
    public:
        static const int N = SIZE; // Size of Rubik's Cube
        using FaceStickers = std::array<std::array<char, N>, N>;

        // Class constructor that initializes sticker values for all the
        // face matrices as well as populates moveToFunction unordered_map
        Cube();

        // Getter methods to access face matrices
        const FaceStickers& getUStickers() const;
        const FaceStickers& getDStickers() const;
        const FaceStickers& getFStickers() const;
        const FaceStickers& getBStickers() const;
        const FaceStickers& getLStickers() const;
        const FaceStickers& getRStickers() const;

        // Takes a series of moves separated by spaces as a string
        // and applies them to the Rubik's Cube
        // Returns true if algorithm is successfully executed
        // and false otherwise
        bool applyAlgorithm(const std::string &algorithm);

        // Prints a 2D representation of the Rubik's Cube
        // If color_output is true, stickers will be represented by colored
        // blocks, otherwise stickers are represented by characters
        void printCube(bool color_output = true) const;

        // Resets all sticker values in the face matrices to their
        // initial solved state
        void reset();

    private:
        // Two-dimensional arrays that store the individual sticker values
        // for each face of the Rubik's Cube
        FaceStickers U_stickers;
        FaceStickers D_stickers;
        FaceStickers F_stickers;
        FaceStickers B_stickers;
        FaceStickers L_stickers;
        FaceStickers R_stickers;

        // Unordered map which maps strings representing moves that can be
        // performed on the Rubik's Cube to their corresponding functions
        std::unordered_map<std::string, std::function<void()>> moveToFunction;

        // Methods representing all distinct types of face moves on a Rubik's Cube
        // The slices parameter specifies how many layers to turn
        void UMove(int slices = 1);
        void UPrimeMove(int slices = 1);
        void U2Move(int slices = 1);
        void DMove(int slices = 1);
        void DPrimeMove(int slices = 1);
        void D2Move(int slices = 1);
        void FMove(int slices = 1);
        void FPrimeMove(int slices = 1);
        void F2Move(int slices = 1);
        void BMove(int slices = 1);
        void BPrimeMove(int slices = 1);
        void B2Move(int slices = 1);
        void RMove(int slices = 1);
        void RPrimeMove(int slices = 1);
        void R2Move(int slices = 1);
        void LMove(int slices = 1);
        void LPrimeMove(int slices = 1);
        void L2Move(int slices = 1);

        // Helper functions used to rotate the values in the face matrices
        // by 90 degrees
        void rotateMatrixClockwise(FaceStickers &mat);
        void rotateMatrixCounterClockwise(FaceStickers &mat);
        // Helper function used to rotate the values in the face matrices
        // by 180 degrees
        void rotateMatrix180(FaceStickers &mat);

        // Helper functions used to rotate slices of stickers in the direction
        // of an x or x' cube rotation
        // The col parameter corresponds to the column of stickers on the F
        // face that belong to the slice
        void rotateSliceX(int col);
        void rotateSliceXPrime(int col);
        void rotateSliceX2(int col);
        // Helper functions used to rotate slices of stickers in the direction
        // of a y or y' cube rotation
        // The row parameter corresponds to the row of stickers on the F
        // face that belong to the slice
        void rotateSliceY(int row);
        void rotateSliceYPrime(int row);
        void rotateSliceY2(int row);
        // Helper functions used to rotate slices of stickers in the direction
        // of a z or z' cube rotation
        // The row parameter corresponds to the row of stickers on the U
        // face that belong to the slice
        void rotateSliceZ(int row);
        void rotateSliceZPrime(int row);
        void rotateSliceZ2(int row);

        // Helper function used to access the columns in the face matrices
        // as std::arrays in top-down order
        std::array<char, N> getColumnValues(const FaceStickers &mat, int col) const;
        // Helper function used to access the columns in the face matrices
        // as std::arrays in bottom-up order
        std::array<char, N> getColumnValuesReverse(const FaceStickers &mat, int col) const;

        // Helper function used to access the columns in the face matrices
        // as std::arrays of pointers in top-down order
        std::array<char*, N> getColumnPointers(FaceStickers &mat, int col) const;
        // Helper function used to access the columns in the face matrices
        // as std::arrays of pointers in bottom-up order
        std::array<char*, N> getColumnPointersReverse(FaceStickers &mat, int col) const;

        // Helper function used to copy the values of an array of chars into
        // an array of char pointers
        void copyValues(std::array<char*, N> pointers, const std::array<char, N> &values);

        // Helper function to get colored block for colored output
        // in printCube() method
        std::string getStickerColor(char sticker) const;
};

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
template<size_t SIZE>
Cube<SIZE>::Cube() {
    for (auto& row : U_stickers) {
        row.fill('W');
    }
    for (auto& row : D_stickers) {
        row.fill('Y');
    }
    for (auto& row : F_stickers) {
        row.fill('G');
    }
    for (auto& row : B_stickers) {
        row.fill('B');
    }
    for (auto& row : L_stickers) {
        row.fill('O');
    }
    for (auto& row : R_stickers) {
        row.fill('R');
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
        auto add_block_moves = [this] (const std::string &block_move,
                         const std::function<void(int)> &move_function) {
            this->moveToFunction[block_move] = [move_function] { move_function(2); };
            for (int i = 2; i < N-1; i++) {
                std::string move = std::to_string(i) + block_move;
                this->moveToFunction[move] = [move_function, i] { move_function(i); };
            }
        };

        add_block_moves("UW",  [this] (int slices) { this->UMove(slices); });
        add_block_moves("UW'", [this] (int slices) { this->UPrimeMove(slices); });
        add_block_moves("UW2", [this] (int slices) { this->U2Move(slices); });
        add_block_moves("DW",  [this] (int slices) { this->DMove(slices); });
        add_block_moves("DW'", [this] (int slices) { this->DPrimeMove(slices); });
        add_block_moves("DW2", [this] (int slices) { this->D2Move(slices); });
        add_block_moves("FW",  [this] (int slices) { this->FMove(slices); });
        add_block_moves("FW'", [this] (int slices) { this->FPrimeMove(slices); });
        add_block_moves("FW2", [this] (int slices) { this->F2Move(slices); });
        add_block_moves("BW",  [this] (int slices) { this->BMove(slices); });
        add_block_moves("BW'", [this] (int slices) { this->BPrimeMove(slices); });
        add_block_moves("BW2", [this] (int slices) { this->B2Move(slices); });
        add_block_moves("LW",  [this] (int slices) { this->LMove(slices); });
        add_block_moves("LW'", [this] (int slices) { this->LPrimeMove(slices); });
        add_block_moves("LW2", [this] (int slices) { this->L2Move(slices); });
        add_block_moves("RW",  [this] (int slices) { this->RMove(slices); });
        add_block_moves("RW'", [this] (int slices) { this->RPrimeMove(slices); });
        add_block_moves("RW2", [this] (int slices) { this->R2Move(slices); });
    }
}

template <size_t SIZE>
const typename Cube<SIZE>::FaceStickers& Cube<SIZE>::getUStickers() const {
    return U_stickers;
}

template <size_t SIZE>
const typename Cube<SIZE>::FaceStickers& Cube<SIZE>::getDStickers() const {
    return D_stickers;
}

template <size_t SIZE>
const typename Cube<SIZE>::FaceStickers& Cube<SIZE>::getFStickers() const {
    return F_stickers;
}

template <size_t SIZE>
const typename Cube<SIZE>::FaceStickers& Cube<SIZE>::getBStickers() const {
    return B_stickers;
}

template <size_t SIZE>
const typename Cube<SIZE>::FaceStickers& Cube<SIZE>::getLStickers() const {
    return L_stickers;
}

template <size_t SIZE>
const typename Cube<SIZE>::FaceStickers& Cube<SIZE>::getRStickers() const {
    return R_stickers;
}

template <size_t SIZE>
bool Cube<SIZE>::applyAlgorithm(const std::string &algorithm) {
    std::vector<std::string> moves;
    std::string current_move = "";
    // Parse moves in algorithm separated by spaces
    for (const char& c : algorithm) {
        if (std::toupper(c) == ' ') {
            moves.push_back(current_move);
            current_move = "";
            continue;
        }
        current_move += std::toupper(c);
    }
    // If algorithm does not end with space, push back last move
    if (current_move.length() > 0) {
        moves.push_back(current_move);
    }
    // Execute moves
    for (const std::string& move : moves) {
        try {
            moveToFunction.at(move)();
        } catch (...) {
            return false;
        }
    }
    return true;
}

template <size_t SIZE>
void Cube<SIZE>::printCube(bool color_output) const {
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

template <size_t SIZE>
void Cube<SIZE>::reset() {
    for (auto& row : U_stickers) {
        row.fill('W');
    }
    for (auto& row : D_stickers) {
        row.fill('Y');
    }
    for (auto& row : F_stickers) {
        row.fill('G');
    }
    for (auto& row : B_stickers) {
        row.fill('B');
    }
    for (auto& row : L_stickers) {
        row.fill('O');
    }
    for (auto& row : R_stickers) {
        row.fill('R');
    }
}

template <size_t SIZE>
std::string Cube<SIZE>::getStickerColor(char sticker) const {
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

template <size_t SIZE>
void Cube<SIZE>::UMove(int slices) {
    rotateMatrixClockwise(U_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceY(i);
    }
}

template <size_t SIZE>
void Cube<SIZE>::UPrimeMove(int slices) {
    rotateMatrixCounterClockwise(U_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceYPrime(i);
    }
}

template <size_t SIZE>
void Cube<SIZE>::U2Move(int slices) {
    rotateMatrix180(U_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceY2(i);
    }
}

template <size_t SIZE>
void Cube<SIZE>::DMove(int slices) {
    rotateMatrixClockwise(D_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceYPrime(N-1 - i);
    }
}

template <size_t SIZE>
void Cube<SIZE>::DPrimeMove(int slices) {
    rotateMatrixCounterClockwise(D_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceY(N-1 - i);
    }
}

template <size_t SIZE>
void Cube<SIZE>::D2Move(int slices) {
    rotateMatrix180(D_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceY2(N-1 - i);
    }
}

template <size_t SIZE>
void Cube<SIZE>::FMove(int slices) {
    rotateMatrixClockwise(F_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceZ(N-1 - i);
    }
}

template <size_t SIZE>
void Cube<SIZE>::FPrimeMove(int slices) {
    rotateMatrixCounterClockwise(F_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceZPrime(N-1 - i);
    }
}

template <size_t SIZE>
void Cube<SIZE>::F2Move(int slices) {
    rotateMatrix180(F_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceZ2(N-1 - i);
    }
}

template <size_t SIZE>
void Cube<SIZE>::BMove(int slices) {
    rotateMatrixClockwise(B_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceZPrime(i);
    }

}

template <size_t SIZE>
void Cube<SIZE>::BPrimeMove(int slices) {
    rotateMatrixCounterClockwise(B_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceZ(i);
    }
}

template <size_t SIZE>
void Cube<SIZE>::B2Move(int slices) {
    rotateMatrix180(B_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceZ2(i);
    }
}

template <size_t SIZE>
void Cube<SIZE>::RMove(int slices) {
    rotateMatrixClockwise(R_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceX(N-1 - i);
    }
}

template <size_t SIZE>
void Cube<SIZE>::RPrimeMove(int slices) {
    rotateMatrixCounterClockwise(R_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceXPrime(N-1 - i);
    }
}

template <size_t SIZE>
void Cube<SIZE>::R2Move(int slices) {
    rotateMatrix180(R_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceX2(N-1 - i);
    }
}

template <size_t SIZE>
void Cube<SIZE>::LMove(int slices) {
    rotateMatrixClockwise(L_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceXPrime(i);
    }
}

template <size_t SIZE>
void Cube<SIZE>::LPrimeMove(int slices) {
    rotateMatrixCounterClockwise(L_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceX(i);
    }
}

template <size_t SIZE>
void Cube<SIZE>::L2Move(int slices) {
    rotateMatrix180(L_stickers);

    for(int i = 0; i < slices; i++) {
        rotateSliceX2(i);
    }
}

template <size_t SIZE>
void Cube<SIZE>::rotateMatrixClockwise(Cube<SIZE>::FaceStickers &mat) {
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

template <size_t SIZE>
// https://www.geeksforgeeks.org/inplace-rotate-square-matrix-by-90-degrees/
void Cube<SIZE>::rotateMatrixCounterClockwise(Cube<SIZE>::FaceStickers &mat) {
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

template <size_t SIZE>
void Cube<SIZE>::rotateMatrix180(Cube<SIZE>::FaceStickers &mat) {
    for (int i = 0; i < N/2; i++) {
		for (int j = 0; j < N; j++) {
			std::swap(mat[i][j], mat[N-i-1][N-j-1]);
        }
    }
    // Reverse middle row if matrix has odd dimensions
    if (N & 1) {
		for (int j = 0; j < N/2; j++) {
			std::swap(mat[N/2][j], mat[N/2][N-j-1]);
        }
	}
}

template <size_t SIZE>
void Cube<SIZE>::rotateSliceX(int col) {
    // Rotate the appropriate columns of stickers for the U, F, D, and B
    // faces clockwise relative to R face of cube
    std::array<char, N> temp = getColumnValues(U_stickers, col);
    copyValues(getColumnPointers(U_stickers, col), getColumnValues(F_stickers, col));
    copyValues(getColumnPointers(F_stickers, col), getColumnValues(D_stickers, col));
    copyValues(getColumnPointers(D_stickers, col), getColumnValuesReverse(B_stickers, N-1 - col));
    copyValues(getColumnPointersReverse(B_stickers, N-1 - col), temp);
}

template <size_t SIZE>
void Cube<SIZE>::rotateSliceXPrime(int col) {
    // Rotate the appropriate columns of stickers for the U, F, D, and B
    // faces counter-clockwise relative to R face of cube
    std::array<char, N> temp = getColumnValues(U_stickers, col);
    copyValues(getColumnPointers(U_stickers, col), getColumnValuesReverse(B_stickers, N-1 - col));
    copyValues(getColumnPointersReverse(B_stickers, N-1 - col), getColumnValues(D_stickers, col));
    copyValues(getColumnPointers(D_stickers, col), getColumnValues(F_stickers, col));
    copyValues(getColumnPointers(F_stickers, col), temp);
}

template <size_t SIZE>
void Cube<SIZE>::rotateSliceX2(int col) {
    // Swap the appropriate columns of stickers for the U, F, D, and B faces
    std::array<char, N> temp = getColumnValues(U_stickers, col);
    copyValues(getColumnPointers(U_stickers, col), getColumnValues(D_stickers, col));
    copyValues(getColumnPointers(D_stickers, col), temp);
    temp = getColumnValuesReverse(F_stickers, col);
    copyValues(getColumnPointers(F_stickers, col), getColumnValuesReverse(B_stickers, N-1 - col));
    copyValues(getColumnPointers(B_stickers, N-1 - col), temp);
}

template <size_t SIZE>
void Cube<SIZE>::rotateSliceY(int row) {
    // Rotate the appropriate rows of stickers for the F, R, B and L faces clockwise
    // relative to U face of cube
    std::array<char, N> temp = F_stickers[row];
    F_stickers[row] = R_stickers[row];
    R_stickers[row] = B_stickers[row];
    B_stickers[row] = L_stickers[row];
    L_stickers[row] = temp;
}

template <size_t SIZE>
void Cube<SIZE>::rotateSliceYPrime(int row) {
    // Rotate the appropriate rows of stickers for the F, R, B and L faces
    // counter-clockwise relative to U face of cube
    std::array<char, N> temp = F_stickers[row];
    F_stickers[row] = L_stickers[row];
    L_stickers[row] = B_stickers[row];
    B_stickers[row] = R_stickers[row];
    R_stickers[row] = temp;
}

template <size_t SIZE>
void Cube<SIZE>::rotateSliceY2(int row) {
    // Swap the appropriate rows of stickers for the F, R, B and L faces
    std::swap(F_stickers[row], B_stickers[row]);
    std::swap(L_stickers[row], R_stickers[row]);
}

template <size_t SIZE>
void Cube<SIZE>::rotateSliceZ(int row) {
    // Rotate the appropriate rows/columns of stickers for the U, R, D, and L
    // faces clockwise relative to F face of cube
    std::array<char, N> temp = U_stickers[row];
    U_stickers[row] = getColumnValuesReverse(L_stickers, row);
    copyValues(getColumnPointers(L_stickers, row), D_stickers[N-1 - row]);
    D_stickers[N-1 - row] = getColumnValuesReverse(R_stickers, N-1 - row);
    copyValues(getColumnPointers(R_stickers, N-1 - row), temp);
}

template <size_t SIZE>
void Cube<SIZE>::rotateSliceZPrime(int row) {
    // Rotate the appropriate rows/columns of stickers for the U, R, D, and L
    // faces counter-clockwise relative to F face of cube
    std::array<char, N> temp = U_stickers[row];
    U_stickers[row] = getColumnValues(R_stickers, N-1 - row);
    copyValues(getColumnPointersReverse(R_stickers, N-1 - row), D_stickers[N-1 - row]);
    D_stickers[N-1 - row] = getColumnValues(L_stickers, row);
    copyValues(getColumnPointersReverse(L_stickers, row), temp);
}

template <size_t SIZE>
void Cube<SIZE>::rotateSliceZ2(int row) {
    // Swap the appropriate rows/columns of stickers for the U, R, D, and L faces
    std::swap(U_stickers[row], D_stickers[N-1 - row]);
    std::reverse(std::begin(U_stickers[row]), std::end(U_stickers[row]));
    std::reverse(std::begin(D_stickers[N-1 - row]), std::end(D_stickers[N-1 - row]));

    std::array<char, N> temp = getColumnValuesReverse(L_stickers, row);
    copyValues(getColumnPointers(L_stickers, row), getColumnValuesReverse(R_stickers, N-1 - row));
    copyValues(getColumnPointers(R_stickers, N-1 - row), temp);
}

template <size_t SIZE>
std::array<char, Cube<SIZE>::N> Cube<SIZE>::getColumnValues(const Cube<SIZE>::FaceStickers &mat, int col) const {
    std::array<char, N> column_array = {};
    for (int i = 0; i < N; i++) {
        column_array[i] = mat[i][col];
    }
    return column_array;
}

template <size_t SIZE>
std::array<char, Cube<SIZE>::N> Cube<SIZE>::getColumnValuesReverse(const Cube<SIZE>::FaceStickers &mat, int col) const {
    std::array<char, N> column_array = {};
    for (int i = 0; i < N; i++) {
        column_array[i] = mat[N-1-i][col];
    }
    return column_array;
}

template <size_t SIZE>
std::array<char*, Cube<SIZE>::N> Cube<SIZE>::getColumnPointers(Cube<SIZE>::FaceStickers &mat, int col) const {
    std::array<char*, N> column_array = {};
    for (int i = 0; i < N; i++) {
        column_array[i] = &mat[i][col];
    }
    return column_array;
}

template <size_t SIZE>
std::array<char*, Cube<SIZE>::N> Cube<SIZE>::getColumnPointersReverse(Cube<SIZE>::FaceStickers &mat, int col) const {
    std::array<char*, N> column_array = {};
    for (int i = 0; i < N; i++) {
        column_array[i] = &mat[N-1-i][col];
    }
    return column_array;
}

template <size_t SIZE>
void Cube<SIZE>::copyValues(std::array<char*, N> pointers, const std::array<char, N> &values) {
    for(int i = 0; i < N; i++) {
        *pointers[i] = values[i];
    }
}

#endif
