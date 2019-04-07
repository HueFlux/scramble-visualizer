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
  U_stickers {
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1}
  },

  D_stickers {
    {2, 2, 2},
    {2, 2, 2},
    {2, 2, 2}
  },

  F_stickers {
    {3, 3, 3},
    {3, 3, 3},
    {3, 3, 3}
  },

  B_stickers {
    {4, 4, 4},
    {4, 4, 4},
    {4, 4, 4}
  },

  L_stickers {
    {5, 5, 5},
    {5, 5, 5},
    {5, 5, 5}
  },

  R_stickers {
    {6, 6, 6},
    {6, 6, 6},
    {6, 6, 6}
  }
{}

void Cube::RotateMatrixClockwise(int (&mat)[N][N]) {

}

void Cube::RotateMatrixCounterClockwise(int (&mat)[N][N]) {

}

void Cube::UMove() {

}

void Cube::UPrimeMove() {

}

void Cube::DMove() {

}

void Cube::DPrimeMove() {

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
