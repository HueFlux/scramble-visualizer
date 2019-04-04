#include "pieces.hpp"

// Corner class implementation
void Corner::RMove() {
  if (right == 0) { // Corner is not on right face of cube
    return;
  }

  // Rotate cubie sticker values clockwise relative to right face of cube
  int temp = up;
  up = front;
  front = down;
  down = back;
  back = temp;
}

void Corner::RPrimeMove() {
  if (right == 0) { // Corner is not on right face of cube
    return;
  }

  // Rotate cubie sticker values counter-clockwise relative to right face of cube
  int temp = up;
  up = back;
  back = down;
  down = front;
  front = temp;
}

void Corner::LMove() {
  if (left == 0) { // Corner is not on left face of cube
    return;
  }

  // Rotate cubie sticker values clockwise relative to left face of cube
  int temp = up;
  up = back;
  back = down;
  down = front;
  front = temp;
}

void Corner::LPrimeMove() {
  if (left == 0) { // Corner is not on left face of cube
    return;
  }

  // Rotate cubie sticker values counter-clockwise relative to left face of cube
  int temp = up;
  up = front;
  front = down;
  down = back;
  back = temp;
}

void Corner::UMove() {
  if (up == 0) { // Corner is not on top face of cube
    return;
  }

  // Rotate cubie sticker values clockwise relative to top face of cube
  int temp = front;
  front = right;
  right = back;
  back = left;
  left = temp;
}

void Corner::UPrimeMove() {
  if (up == 0) { // Corner is not on top face of cube
    return;
  }

  // Rotate cubie sticker values counter-clockwise relative to top face of cube
  int temp = front;
  front = left;
  left = back;
  back = right;
  right = temp;
}

void Corner::DMove() {
  if (down == 0) { // Corner is not on bottom face of cube
    return;
  }

  // Rotate cubie sticker values clockwise relative to bottom face of cube
  int temp = front;
  front = left;
  left = back;
  back = right;
  right = temp;
}

void Corner::DPrimeMove() {
  if (down == 0) { // Corner is not on bottom face of cube
    return;
  }

  // Rotate cubie sticker values counter-clockwise relative to bottom face of cube
  int temp = front;
  front = right;
  right = back;
  back = left;
  left = temp;
}

void Corner::FMove() {
  if (front == 0) { // Corner is not on front face of cube
    return;
  }

  // Rotate cubie sticker values clockwise relative to front face of cube
  int temp = up;
  up = left;
  left = down;
  down = right;
  right = temp;
}

void Corner::FPrimeMove() {
  if (front == 0) { // Corner is not on front face of cube
    return;
  }

  // Rotate cubie sticker values counter-clockwise relative to front face of cube
  int temp = up;
  up = right;
  right = down;
  down = left;
  left = temp;
}

void Corner::BMove() {
  if (back == 0) { // Corner is not on back face of cube
    return;
  }

  // Rotate cubie sticker values clockwise relative to back face of cube
  int temp = up;
  up = right;
  right = down;
  down = left;
  left = temp;
}

void Corner::BPrimeMove() {
  if (back == 0) { // Corner is not on back face of cube
    return;
  }

  // Rotate cubie sticker values counter-clockwise relative to back face of cube
  int temp = up;
  up = left;
  left = down;
  down = right;
  right = temp;
}
