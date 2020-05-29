#ifndef CUBE_FACE_HPP
#define CUBE_FACE_HPP

#include <SFML/Graphics.hpp>
#include "cube.hpp"
#include <array>

class CubeFace : public sf::Drawable {
    public:
        using FaceStickerRectangles = std::array<std::array<sf::RectangleShape, Cube::N>, Cube::N>;

        inline static const sf::Color black{0, 0, 0};
        inline static const sf::Color white{255, 255, 255};
        inline static const sf::Color yellow{254, 227, 51};
        inline static const sf::Color green{71, 209, 75};
        inline static const sf::Color blue{30, 127, 239};
        inline static const sf::Color orange{246, 108, 46};
        inline static const sf::Color red{252, 36, 37};

        CubeFace(sf::RectangleShape &face, const Cube::FaceStickers &sticker_values);

        virtual ~CubeFace();

        void createCubeFace();
        void updateStickers();

    private:
        sf::RectangleShape &face;
        const Cube::FaceStickers &sticker_values;
        FaceStickerRectangles stickers;

        virtual void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const;
};

#endif
