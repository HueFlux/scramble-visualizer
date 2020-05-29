#include <SFML/Graphics.hpp>
#include "cube_graphic.hpp"
#include <iostream>
#include <string>
#include <array>
#include <thread>
#include <vector>

sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);
void input(sf::RenderWindow* window, CubeGraphic* cube, bool* quit);

std::string superflipAlgorithm(int size);

int main() {
    // Create a window
    int res_x = 800;
    int res_y = 600;
    sf::RenderWindow window(sf::VideoMode(res_x, res_y), "Rubik's Cube", (sf::Style::Resize + sf::Style::Close));
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    // Create a view
    sf::View view;
    view.setSize(res_x, res_y);
    view.setCenter(view.getSize().x / 2, view.getSize().y / 2);

    CubeGraphic cube(view);
    cube.applyAlgorithm(cube.superflipAlgorithm());
    cube.updateStickers();

    window.setActive(false);
    bool quit_from_input = false;
    std::thread input_thread(input, &window, &cube, &quit_from_input);

    while (window.isOpen()) {
        if (quit_from_input) {
            window.close();
            break;
        }
        sf::Event event;
        // Handle all events
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    view = getLetterboxView(view, event.size.width, event.size.height);
                    break;
                default:
                    break;
            }
        }
        // Update the screen
        window.clear();
        window.setView(view);
        // Draw objects here
        window.draw(cube);

        window.display();
    }
    input_thread.detach();

    return 0;
}

// https://github.com/SFML/SFML/wiki/Source%3A-Letterbox-effect-using-a-view
sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight) {

    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox effect.
    // A new view (with a new viewport set) is returned.

    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));

    return view;
}

void input(sf::RenderWindow* window, CubeGraphic* cube, bool* quit) {
    std::string algorithm;

    while (window->isOpen()) {
        std::cout << "Enter a move or algorithm to execute ('Q' to quit, '\\' to reset): ";
        std::getline(std::cin, algorithm);

        if (std::toupper(algorithm[0]) == 'Q') {
            *quit = true;
            break;
        }
        if (algorithm[0] == '\\') {
            cube->resetCube();
            continue;
        }
        if(!cube->applyAlgorithm(algorithm)) {
            std::cout << "\033[1;31mInvalid move(s).\033[0m" << std::endl;
        }
    }
}
