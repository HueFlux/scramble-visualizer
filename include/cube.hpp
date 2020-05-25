#ifndef CUBE_HPP
#define CUBE_HPP

#include <array>
#include <unordered_map>
#include <string>
#include <functional>

class Cube {
    public:
        static const int N = 5; // Size of Rubik's Cube
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

#endif
