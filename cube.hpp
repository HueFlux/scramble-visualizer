#ifndef __CUBE_HPP__
#define __CUBE_HPP__

const int N = 3; // Size of Rubik's Cube

class Cube {
  private:
    // Two-dimensional arrays that store the individual sticker values
    // for each face of the Rubik's Cube
    int U_stickers [N][N];
    int D_stickers [N][N];
    int F_stickers [N][N];
    int B_stickers [N][N];
    int L_stickers [N][N];
    int R_stickers [N][N];

    // Helper functions used to rotate the values in the face matrices
    void RotateMatrixClockwise(int (&mat)[N][N]);
    void RotateMatrixCounterClockwise(int (&mat)[N][N]);

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
};

#endif
