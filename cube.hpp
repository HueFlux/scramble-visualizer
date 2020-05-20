#ifndef CUBE_HPP
#define CUBE_HPP

#include <array>
#include <unordered_map>
#include <string>
#include <functional>

class Cube {
    public:
        static const int N = 3; // Size of Rubik's Cube
        using FaceStickers = std::array<std::array<char, N>, N>;

        // Class constructor that initializes sticker values for
        // all the face matrices
        Cube();

        // Getter methods to access face matrices
        const FaceStickers& getUStickers() const;
        const FaceStickers& getDStickers() const;
        const FaceStickers& getFStickers() const;
        const FaceStickers& getBStickers() const;
        const FaceStickers& getLStickers() const;
        const FaceStickers& getRStickers() const;

        // Methods representing all distinct types of moves on a Rubik's Cube
        // These functions will define how all faces will be affected
        void UMove();
        void UPrimeMove();
        void U2Move();
        void DMove();
        void DPrimeMove();
        void D2Move();
        void FMove();
        void FPrimeMove();
        void F2Move();
        void BMove();
        void BPrimeMove();
        void B2Move();
        void RMove();
        void RPrimeMove();
        void R2Move();
        void LMove();
        void LPrimeMove();
        void L2Move();

        // Method that takes a series of moves as a string and applies
        // them to the Rubik's Cube
        // Returns true if algorithm is successful and false otherwise
        bool applyAlgorithm(const std::string &algorithm);

        // Method that prints a 2D representation of the Rubik's Cube
        void printCube() const;

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
        std::unordered_map<std::string, std::function<void ()>> moveToFunction;

        // Helper functions used to rotate the values in the face matrices
        // by 90 degrees
        void rotateMatrixClockwise(FaceStickers &mat);
        void rotateMatrixCounterClockwise(FaceStickers &mat);
        // Helper function used to rotate the values in the face matrices
        // by 180 degrees
        void rotateMatrix180(FaceStickers &mat);

        // Helper function used to access the columns in the face matrices
        // as std::arrays in top-down order
        std::array<char, N> getColumnValues(FaceStickers &mat, int col);
        // Helper function used to access the columns in the face matrices
        // as std::arrays in bottom-up order
        std::array<char, N> getColumnValuesReverse(FaceStickers &mat, int col);

        // Helper function used to access the columns in the face matrices
        // as std::arrays of pointers in top-down order
        std::array<char*, N> getColumnPointers(FaceStickers &mat, int col);
        // Helper function used to access the columns in the face matrices
        // as std::arrays of pointers in bottom-up order
        std::array<char*, N> getColumnPointersReverse(FaceStickers &mat, int col);

        // Helper function used to copy the values of an array of chars into
        // an array of char pointers
        void copyValues(std::array<char*, N> pointers, const std::array<char, N>& values);

};

#endif
