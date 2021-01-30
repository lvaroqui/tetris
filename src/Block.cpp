#include "Block.hpp"

Block::Block(float x, float y, Type type) {
    setPosition(x, y);
    setType(type);
    const float size = BLOCK_SIZE - 2 * BLOCK_OUTLINE;
    mRect.setSize({size, size});
    mRect.setOutlineThickness(BLOCK_OUTLINE);
}

std::pair<sf::Color, sf::Color> Block::toColors(Type type) {
    switch (type) {
        case None:
            return std::make_pair(sf::Color(0), sf::Color(0));
        case Border:
            return std::make_pair(sf::Color(0x444444ff), sf::Color(0x222222ff));
        case I:
            return std::make_pair(sf::Color(0x17d9ebff), sf::Color(0x157085ff));
        case J:
            return std::make_pair(sf::Color(0x1f64ccff), sf::Color(0x10257aff));
        case L:
            return std::make_pair(sf::Color(0xf7a00aff), sf::Color(0x915607ff));
        case O:
            return std::make_pair(sf::Color(0xebc334ff), sf::Color(0xa37803ff));
        case S:
            return std::make_pair(sf::Color(0xdb1626ff), sf::Color(0x820c15ff));
        case T:
            return std::make_pair(sf::Color(0xb02bedff), sf::Color(0x54027aff));
        case Z:
            return std::make_pair(sf::Color(0x11d40bff), sf::Color(0x0d8f29ff));
        default:
            return std::make_pair(sf::Color(), sf::Color());
    }
}