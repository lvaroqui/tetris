#pragma once

#include <SFML/Graphics.hpp>

#include "Block.hpp"

class Grid : public sf::Drawable {
public:
    Grid();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    Block& get(int x, int y) {
        return mPlayArea[x][y];
    }

    bool free(int x, int y) {
        return mPlayArea[x][y].type() == Block::None;
    }

private:
    std::vector<Block> mBorder;
    std::array<std::array<Block, PLAY_AREA_HEIGHT>, PLAY_AREA_WIDTH> mPlayArea;
};
