#ifndef CUBE_FACE_HPP
#define CUBE_FACE_HPP

#include <SFML/Graphics.hpp>
#include "cube.hpp"
#include <array>

class CubeFace : public sf::Drawable {
    public:
        using FaceStickerRectangles = std::array<std::array<sf::RectangleShape, Cube::N>, Cube::N>;
        // Color objects for each sticker color on the cube + black
        inline static const sf::Color black{0, 0, 0};
        inline static const sf::Color white{255, 255, 255};
        inline static const sf::Color yellow{254, 227, 51};
        inline static const sf::Color green{71, 209, 75};
        inline static const sf::Color blue{30, 127, 239};
        inline static const sf::Color orange{247, 134, 57};
        inline static const sf::Color red{252, 36, 37};

        // Constructor which takes a RectangleShape used to contain the
        // face stickers and a FaceStickers matrix holding the values of
        // all the face stickers
        CubeFace(sf::RectangleShape &face, const Cube::FaceStickers &sticker_values);

        virtual ~CubeFace();

        // Updates the fill colors for all the sticker
        // rectangles inside the face rectangle
        void updateStickers();

    private:
        // Rectangle to contain face sticker rectangles
        sf::RectangleShape &face;
        // FaceStickers matrix containing sticker values
        const Cube::FaceStickers &sticker_values;
        // Matrix of face sticker rectangles
        FaceStickerRectangles stickers;

        // Overridden draw method to draw CubeFace to the RenderTarget
        virtual void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const;
};

#endif
