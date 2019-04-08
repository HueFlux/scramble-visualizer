#ifndef __CUBE_HPP__
#define __CUBE_HPP__

#include <array>

const int N = 3; // Size of Rubik's Cube

class Cube {
    private:
        // Two-dimensional arrays that store the individual sticker values
        // for each face of the Rubik's Cube
        std::array<std::array<int, N>, N> U_stickers;
        std::array<std::array<int, N>, N> D_stickers;
        std::array<std::array<int, N>, N> F_stickers;
        std::array<std::array<int, N>, N> B_stickers;
        std::array<std::array<int, N>, N> L_stickers;
        std::array<std::array<int, N>, N> R_stickers;

        // Helper functions used to rotate the values in the face matrices
        void RotateMatrixClockwise(std::array<std::array<int, N>, N> &mat);
        void RotateMatrixCounterClockwise(std::array<std::array<int, N>, N> &mat);

    public:
        // Class constructor that initializes sticker values for
        // all the face matrices
        Cube();

        // Functions representing all distinct types of moves on a Rubik's Cube
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
        friend void PrintMatrixRotations(Cube &cube, std::array<std::array<int, N>, N> &mat);
};

#endif
