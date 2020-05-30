#include "cube_graphic.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "cube_face.hpp"
#include "cube.hpp"

CubeGraphic::CubeGraphic(sf::View &view) :
    view(view),
    face_size(sf::Vector2f(view.getSize().y * 0.30, view.getSize().y * 0.30)),

    F_box(sf::RectangleShape(face_size)),
    U_box(sf::RectangleShape(face_size)),
    D_box(sf::RectangleShape(face_size)),
    R_box(sf::RectangleShape(face_size)),
    L_box(sf::RectangleShape(face_size)),
    B_box(sf::RectangleShape(face_size))
{
    // rubiks_cube is default constructed
    
    F_box.setPosition(view.getCenter().x - face_size.x,
                      view.getCenter().y - face_size.y / 2);
    U_box.setPosition(view.getCenter().x - face_size.x,
                      view.getCenter().y - face_size.y * 3/2);
    D_box.setPosition(view.getCenter().x - face_size.x,
                      view.getCenter().y + face_size.y / 2);
    R_box.setPosition(view.getCenter().x,
                      view.getCenter().y - face_size.y / 2);
    L_box.setPosition(view.getCenter().x - face_size.x * 2,
                      view.getCenter().y - face_size.y / 2);
    B_box.setPosition(view.getCenter().x + face_size.x,
                      view.getCenter().y - face_size.y / 2);

    this->F_face = std::make_unique<CubeFace>(F_box, rubiks_cube.getFStickers());
    this->U_face = std::make_unique<CubeFace>(U_box, rubiks_cube.getUStickers());
    this->D_face = std::make_unique<CubeFace>(D_box, rubiks_cube.getDStickers());
    this->R_face = std::make_unique<CubeFace>(R_box, rubiks_cube.getRStickers());
    this->L_face = std::make_unique<CubeFace>(L_box, rubiks_cube.getLStickers());
    this->B_face = std::make_unique<CubeFace>(B_box, rubiks_cube.getBStickers());
};

CubeGraphic::~CubeGraphic() {
}

bool CubeGraphic::applyAlgorithm(const std::string &algorithm) {
    bool success = rubiks_cube.applyAlgorithm(algorithm);
    updateStickers();
    return success;
}

void CubeGraphic::resetCube() {
    rubiks_cube.reset();
    updateStickers();
}

void CubeGraphic::updateStickers() {
    F_face->updateStickers();
    U_face->updateStickers();
    D_face->updateStickers();
    R_face->updateStickers();
    L_face->updateStickers();
    B_face->updateStickers();
}

std::string CubeGraphic::superflipAlgorithm() {
    return rubiks_cube.superflipAlgorithm();
}

void CubeGraphic::draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const {
    renderTarget.setView(view);
    renderTarget.draw(*F_face);
    renderTarget.draw(*U_face);
    renderTarget.draw(*D_face);
    renderTarget.draw(*R_face);
    renderTarget.draw(*L_face);
    renderTarget.draw(*B_face);
}
