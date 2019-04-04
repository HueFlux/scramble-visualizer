#ifndef __PIECES_HPP_INCLUDED__
#define __PIECES_HPP_INCLUDED__

// Integer values used to represent sticker colors
// 0 = None
// 1 = White
// 2 = Green
// 3 = Red
// 4 = Blue
// 5 = Orange
// 6 = Yellow

// Abstract class representing a single piece/cubie of the Rubik's Cube
class Piece {
  protected:
    // All sides of the piece have a defualt sticker value of 0 (No Sticker)
    int up = 0;
    int down = 0;
    int right = 0;
    int left = 0;
    int front = 0;
    int back = 0;

  public:
    // Virtual functions representing all distinct types of moves on a Rubik's Cube
    // These functions will define how a single piece will be affected
    virtual void RMove() = 0;
    virtual void RPrimeMove() = 0;
    virtual void LMove() = 0;
    virtual void LPrimeMove() = 0;
    virtual void UMove() = 0;
    virtual void UPrimeMove() = 0;
    virtual void DMove() = 0;
    virtual void DPrimeMove() = 0;
    virtual void FMove() = 0;
    virtual void FPrimeMove() = 0;
    virtual void BMove() = 0;
    virtual void BPrimeMove() = 0;
};

// Derived class representing a single corner piece
class Corner: public Piece {
  public:
    void RMove();
    void RPrimeMove();
    void LMove();
    void LPrimeMove();
    void UMove();
    void UPrimeMove();
    void DMove();
    void DPrimeMove();
    void FMove();
    void FPrimeMove();
    void BMove();
    void BPrimeMove();
};

// Derived class representing a single edge piece
class Edge: public Piece {
  public:
    void RMove();
    void RPrimeMove();
    void LMove();
    void LPrimeMove();
    void UMove();
    void UPrimeMove();
    void DMove();
    void DPrimeMove();
    void FMove();
    void FPrimeMove();
    void BMove();
    void BPrimeMove();
};

#endif
