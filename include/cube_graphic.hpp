#ifndef CUBE_GRAPHIC_HPP
#define CUBE_GRAPHIC_HPP

#include <SFML/Graphics.hpp>
#include "cube_face.hpp"
#include "cube.hpp"
#include <string>
#include <memory>

class CubeGraphic : public sf::Drawable {
    public:
        CubeGraphic(sf::View &view);
        virtual ~CubeGraphic();

        bool applyAlgorithm(const std::string &algorithm);
        void resetCube();
        void updateStickers();
        std::string superflipAlgorithm();

    private:
        Cube rubiks_cube;

        sf::View &view;
        sf::Vector2f face_size;
        // Containers for cube faces
        sf::RectangleShape F_box;
        sf::RectangleShape U_box;
        sf::RectangleShape D_box;
        sf::RectangleShape R_box;
        sf::RectangleShape L_box;
        sf::RectangleShape B_box;

        std::unique_ptr<CubeFace> F_face;
        std::unique_ptr<CubeFace> U_face;
        std::unique_ptr<CubeFace> D_face;
        std::unique_ptr<CubeFace> R_face;
        std::unique_ptr<CubeFace> L_face;
        std::unique_ptr<CubeFace> B_face;

        virtual void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const;
};

#endif
