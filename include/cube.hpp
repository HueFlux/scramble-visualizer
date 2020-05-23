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

        // Method that takes a series of moves separated by spaces as a string
        // and applies them to the Rubik's Cube
        // Returns true if algorithm is successfully executed
        // and false otherwise
        bool applyAlgorithm(const std::string &algorithm);

        // Method that prints a 2D representation of the Rubik's Cube
        // If color_output is true, stickers will be represented by colored
        // blocks, otherwise stickers are represented by characters
        void printCube(bool color_output = true) const;

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

        // Methods for outer block moves on higher order cubes
        // The slices parameter specifies how many layers to turn
        void UWMove(int slices = 2);
        void UWPrimeMove(int slices = 2);
        void UW2Move(int slices = 2);
        void DWMove(int slices = 2);
        void DWPrimeMove(int slices = 2);
        void DW2Move(int slices = 2);
        void FWMove(int slices = 2);
        void FWPrimeMove(int slices = 2);
        void FW2Move(int slices = 2);
        void BWMove(int slices = 2);
        void BWPrimeMove(int slices = 2);
        void BW2Move(int slices = 2);
        void RWMove(int slices = 2);
        void RWPrimeMove(int slices = 2);
        void RW2Move(int slices = 2);
        void LWMove(int slices = 2);
        void LWPrimeMove(int slices = 2);
        void LW2Move(int slices = 2);

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
        void copyValues(std::array<char*, N> pointers, const std::array<char, N>& values);

        // Helper function to get colored block for colored output
        // in printCube() method
        std::string getStickerColor(char sticker) const;
};

#endif
