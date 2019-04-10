#ifndef __CUBE_HPP__
#define __CUBE_HPP__

#include <array>

const int N = 3; // Size of Rubik's Cube

class Cube {
    private:
        // Two-dimensional arrays that store the individual sticker values
        // for each face of the Rubik's Cube
        std::array<std::array<char, N>, N> U_stickers;
        std::array<std::array<char, N>, N> D_stickers;
        std::array<std::array<char, N>, N> F_stickers;
        std::array<std::array<char, N>, N> B_stickers;
        std::array<std::array<char, N>, N> L_stickers;
        std::array<std::array<char, N>, N> R_stickers;

        // Helper functions used to rotate the values in the face matrices
        // by 90 degrees
        void RotateMatrixClockwise(std::array<std::array<char, N>, N> &mat);
        void RotateMatrixCounterClockwise(std::array<std::array<char, N>, N> &mat);

        // Helper function used to access the columns in the face matrices
        // as std::arrays of pointers in top-down order
        std::array<char*, N> GetColumn(std::array<std::array<char, N>, N> &mat, int col);
        // Helper function used to access the columns in the face matrices
        // as std::arrays of pointers in bottom-up order
        std::array<char*, N> GetColumnReverse(std::array<std::array<char, N>, N> &mat, int col);

    public:
        // Class constructor that initializes sticker values for
        // all the face matrices
        Cube();

        // Getter methods to access face matrices
        const std::array<std::array<char, N>, N>& GetUStickers() const;
        const std::array<std::array<char, N>, N>& GetDStickers() const;
        const std::array<std::array<char, N>, N>& GetFStickers() const;
        const std::array<std::array<char, N>, N>& GetBStickers() const;
        const std::array<std::array<char, N>, N>& GetLStickers() const;
        const std::array<std::array<char, N>, N>& GetRStickers() const;

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

        // Friend function for testing private helper functions
        friend void PrintMatrixRotations(Cube &cube, std::array<std::array<char, N>, N> &mat);
};


// Implementation of getter methods
inline const std::array<std::array<char, N>, N>& Cube::GetUStickers() const {
    return U_stickers;
}

inline const std::array<std::array<char, N>, N>& Cube::GetDStickers() const {
    return D_stickers;
}

inline const std::array<std::array<char, N>, N>& Cube::GetFStickers() const {
    return F_stickers;
}

inline const std::array<std::array<char, N>, N>& Cube::GetBStickers() const {
    return B_stickers;
}

inline const std::array<std::array<char, N>, N>& Cube::GetLStickers() const {
    return L_stickers;
}

inline const std::array<std::array<char, N>, N>& Cube::GetRStickers() const {
    return R_stickers;
}

#endif
