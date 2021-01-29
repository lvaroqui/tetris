#include <SFML/Graphics.hpp>
#include <iostream>

#include "Grid.hpp"

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(FULL_AREA_WIDTH * BLOCK_SIZE, FULL_AREA_HEIGHT * BLOCK_SIZE), "Tetris", sf::Style::Default, settings);

    window.setFramerateLimit(144);

    const float normalDropInterval = 1.f;
    const float fastDropInterval = 0.05f;

    Grid grid;

    sf::Clock cycleClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::Resized) {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                        break;
                    case sf::Keyboard::Right:
                        break;
                    case sf::Keyboard::Up:
                        break;
                    default:
                        break;
                }
            }
        }

        float dropInterval = sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
                                 ? fastDropInterval
                                 : normalDropInterval;

        if (cycleClock.getElapsedTime().asSeconds() > dropInterval) {
            cycleClock.restart();
        }

        window.clear();
        window.draw(grid);
        window.display();
    }

    return 0;
}
