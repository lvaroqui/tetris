#include <SFML/Graphics.hpp>
#include <iostream>

#include "Grid.hpp"

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(FULL_AREA_WIDTH * BLOCK_SIZE, FULL_AREA_HEIGHT * BLOCK_SIZE), "Tetris", sf::Style::Default, settings);

    window.setFramerateLimit(144);
    window.setKeyRepeatEnabled(false);

    const float normalDropInterval = .5f;
    const float fastDropInterval = 0.05f;

    const float slideInterval = 0.1f;

    Grid grid;
    grid.spawnTetromino();

    sf::Clock dropClock;
    sf::Clock slideClock;
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
                        grid.left();
                        slideClock.restart();
                        dropClock.restart();
                        break;
                    case sf::Keyboard::Right:
                        grid.right();
                        slideClock.restart();
                        dropClock.restart();
                        break;
                    case sf::Keyboard::Space:
                        dropClock.restart();
                        grid.drop();
                        grid.clear();
                        if (!grid.spawnTetromino()) {
                            std::exit(0);  // lose
                        }
                        dropClock.restart();
                        slideClock.restart();
                        break;
                    case sf::Keyboard::Up:
                        grid.rotateRight();
                        dropClock.restart();
                        break;
                    default:
                        break;
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
            slideClock.getElapsedTime().asSeconds() > slideInterval) {
            grid.left();
            slideClock.restart();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
            slideClock.getElapsedTime().asSeconds() > slideInterval) {
            grid.right();
            slideClock.restart();
        }

        float dropInterval = sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
                                 ? fastDropInterval
                                 : normalDropInterval;

        if (dropClock.getElapsedTime().asSeconds() > dropInterval) {
            dropClock.restart();

            if (!grid.down()) {
                if (!grid.spawnTetromino()) {
                    std::exit(0);  // lose
                }
                slideClock.restart();
                dropClock.restart();
            }
        }

        window.clear();
        window.draw(grid);
        window.display();
    }
}
