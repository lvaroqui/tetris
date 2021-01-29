#pragma once

#include <SFML/Graphics.hpp>

#include "Constants.hpp"

class Block : public sf::Drawable {
public:
    enum Type {
        None,
        Border,
        I,
        J,
        L,
        O,
        S,
        T,
        Z
    };

    Block(float x = 0, float y = 0, Type type = None);

    void setPosition(int x, int y) {
        mRect.setPosition(x * BLOCK_SIZE + BLOCK_OUTLINE, y * BLOCK_SIZE + BLOCK_OUTLINE);
    }

    Type type() const { return mType; }

    void setType(Type type) {
        mType = type;

        auto colors = toColors(type);
        mRect.setFillColor(colors.first);
        mRect.setOutlineColor(colors.second);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        if (mType == None) {
            return;  // Skip rendering
        }
        target.draw(mRect, states);
    }

private:
    std::pair<sf::Color, sf::Color> toColors(Type type);

    sf::RectangleShape mRect;
    Type mType;
};
