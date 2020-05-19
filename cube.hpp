#ifndef __CUBE_HPP__
#define __CUBE_HPP__

#include <array>
#include <unordered_map>
#include <string>
#include <functional>
#include <iostream>

const int N = 3; // Size of Rubik's Cube
using FaceStickers = std::array<std::array<char, N>, N>;

class Cube {
    public:
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
        void DMove();
        void DPrimeMove();
        void FMove();
        void FPrimeMove();
        void BMove();
        void BPrimeMove();
        void RMove();
        void RPrimeMove();
        void LMove();
        void LPrimeMove();

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


// Implementation of getter methods
inline const FaceStickers& Cube::getUStickers() const {
    return U_stickers;
}

inline const FaceStickers& Cube::getDStickers() const {
    return D_stickers;
}

inline const FaceStickers& Cube::getFStickers() const {
    return F_stickers;
}

inline const FaceStickers& Cube::getBStickers() const {
    return B_stickers;
}

inline const FaceStickers& Cube::getLStickers() const {
    return L_stickers;
}

inline const FaceStickers& Cube::getRStickers() const {
    return R_stickers;
}

#endif
