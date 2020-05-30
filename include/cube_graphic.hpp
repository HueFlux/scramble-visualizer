#ifndef CUBE_GRAPHIC_HPP
#define CUBE_GRAPHIC_HPP

#include <SFML/Graphics.hpp>
#include "cube_face.hpp"
#include "cube.hpp"
#include <string>
#include <memory>

class CubeGraphic : public sf::Drawable {
    public:
        // Constructor which takes a View in which CubeGraphic will be placed
        CubeGraphic(sf::View &view);

        virtual ~CubeGraphic();

        // Takes a series of moves separated by spaces as a string
        // and applies them to the Rubik's Cube
        // Returns true if algorithm is successfully executed
        // and false otherwise
        bool applyAlgorithm(const std::string &algorithm);
        // Resets all sticker values in the face matrices to their
        // initial solved state
        void resetCube();
        // Updates the fill colors for all the sticker rectangles
        void updateStickers();
        // Returns the superflip algorithm for the Rubik's Cube as a string
        std::string superflipAlgorithm();

    private:
        // Cube object representing the logical Rubik's Cube
        Cube rubiks_cube;

        // Reference to the view in which to place the Rubik's Cube
        sf::View &view;
        // Dimensions for each cube face
        sf::Vector2f face_size;
        // Containers for cube faces
        sf::RectangleShape F_box;
        sf::RectangleShape U_box;
        sf::RectangleShape D_box;
        sf::RectangleShape R_box;
        sf::RectangleShape L_box;
        sf::RectangleShape B_box;
        // Smart pointers to CubeFaces
        std::unique_ptr<CubeFace> F_face;
        std::unique_ptr<CubeFace> U_face;
        std::unique_ptr<CubeFace> D_face;
        std::unique_ptr<CubeFace> R_face;
        std::unique_ptr<CubeFace> L_face;
        std::unique_ptr<CubeFace> B_face;

        // Overridden draw method to draw CubeGraphic to the RenderTarget
        virtual void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const;
};

#endif
