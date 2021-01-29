#include <SFML/Graphics.hpp>
#include <iostream>

const float BLOCK_SIZE = 40;

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(12 * BLOCK_SIZE, 22 * BLOCK_SIZE), "Tetris", sf::Style::Default, settings);

    window.setFramerateLimit(144);

    sf::RectangleShape shape({BLOCK_SIZE - 4, BLOCK_SIZE - 4});
    shape.setFillColor(sf::Color::Cyan);
    shape.setOutlineColor(sf::Color::Blue);
    shape.setOutlineThickness(2.f);
    shape.setPosition(2, 2);

    const float normalDropInterval = 1.f;
    const float fastDropInterval = 0.05f;

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
                        shape.move({-BLOCK_SIZE, 0.f});
                        break;
                    case sf::Keyboard::Right:
                        shape.move({BLOCK_SIZE, 0.f});
                        break;
                    case sf::Keyboard::Up:
                        shape.move({0.f, -1.f});
                        break;
                    default:
                        break;
                }
            }
        }

        float dropInterval = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ? fastDropInterval : normalDropInterval;

        if (cycleClock.getElapsedTime().asSeconds() > dropInterval) {
            cycleClock.restart();
            shape.move(0, BLOCK_SIZE);
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}