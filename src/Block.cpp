#include "Block.hpp"

Block::Block(float x, float y, Type type) {
    setType(type);
    const float size = BLOCK_SIZE - 2 * BLOCK_OUTLINE;
    mRect.setSize({size, size});
    mRect.setOutlineThickness(BLOCK_OUTLINE);
    setPosition(x, y);
}

std::pair<sf::Color, sf::Color> Block::toColors(Type type) {
    switch (type) {
        case None:
            return std::make_pair(sf::Color(0), sf::Color(0));
        case Border:
            return std::make_pair(sf::Color(0x44, 0x44, 0x44), sf::Color(0x22, 0x22, 0x22));
        case I:
            return std::make_pair(sf::Color(), sf::Color());
        case J:
            return std::make_pair(sf::Color(), sf::Color());
        case L:
            return std::make_pair(sf::Color(), sf::Color());
        case O:
            return std::make_pair(sf::Color(), sf::Color());
        case S:
            return std::make_pair(sf::Color(), sf::Color());
        case T:
            return std::make_pair(sf::Color(), sf::Color());
        case Z:
            return std::make_pair(sf::Color(), sf::Color());
        default:
            return std::make_pair(sf::Color(), sf::Color());
    }
}