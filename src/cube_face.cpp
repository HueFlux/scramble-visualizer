#include "cube_face.hpp"
#include <SFML/Graphics.hpp>
#include "cube.hpp"

CubeFace::CubeFace(sf::RectangleShape &face, const Cube::FaceStickers &sticker_values) :
    face(face),
    sticker_values(sticker_values)
{
    createCubeFace();
}

CubeFace::~CubeFace() {
}

void CubeFace::createCubeFace() {
    face.setFillColor(sf::Color::Transparent);

    float face_border = 7;
    float sticker_width = (face.getSize().x - face_border*2) / Cube::N;
    sf::Vector2f sticker_size(sticker_width, sticker_width);

    sf::Vector2f face_origin = face.getPosition(); // Top left corner of face
    for (int i = 0; i < stickers.size(); i++) {
        for (int j = 0; j < stickers[0].size(); j++) {
            stickers[i][j].setSize(sticker_size);
            stickers[i][j].setPosition(face_origin.x + face_border + j * sticker_width,
                                        face_origin.y + face_border + i * sticker_width);
            // Set fill color for stickers
            switch (sticker_values[i][j]) {
                case 'W':
                    stickers[i][j].setFillColor(white);
                    break;
                case 'Y':
                    stickers[i][j].setFillColor(yellow);
                    break;
                case 'G':
                    stickers[i][j].setFillColor(green);
                    break;
                case 'B':
                    stickers[i][j].setFillColor(blue);
                    break;
                case 'O':
                    stickers[i][j].setFillColor(orange);
                    break;
                case 'R':
                    stickers[i][j].setFillColor(red);
                    break;
                default:
                    stickers[i][j].setFillColor(black);
                    break;
            }
            stickers[i][j].setOutlineColor(black);
            stickers[i][j].setOutlineThickness(sticker_width * -0.05);
        }
    }
}

void CubeFace::updateStickers() {
    for (int i = 0; i < stickers.size(); i++) {
        for (int j = 0; j < stickers[0].size(); j++) {
            // Set fill color for stickers
            switch (sticker_values[i][j]) {
                case 'W':
                    stickers[i][j].setFillColor(white);
                    break;
                case 'Y':
                    stickers[i][j].setFillColor(yellow);
                    break;
                case 'G':
                    stickers[i][j].setFillColor(green);
                    break;
                case 'B':
                    stickers[i][j].setFillColor(blue);
                    break;
                case 'O':
                    stickers[i][j].setFillColor(orange);
                    break;
                case 'R':
                    stickers[i][j].setFillColor(red);
                    break;
                default:
                    stickers[i][j].setFillColor(black);
                    break;
            }
        }
    }
}

void CubeFace::draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const {
    renderTarget.draw(face);
    for (int i = 0; i < stickers.size(); i++) {
        for (int j = 0; j < stickers[0].size(); j++) {
            renderTarget.draw(stickers[i][j]);
        }
    }
}
