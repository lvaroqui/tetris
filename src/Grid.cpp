#include "Grid.hpp"

Grid::Grid() : gen(rd()), distrib(Block::First, Block::Last) {
    mBorder.reserve(FULL_AREA_HEIGHT * 2 + FULL_AREA_HEIGHT - 2);

    // Vertical borders
    for (int i = 0; i < FULL_AREA_HEIGHT; i++) {
        mBorder.emplace_back(0.f, i, Block::Border);
        mBorder.emplace_back(FULL_AREA_WIDTH - 1, i, Block::Border);
    }

    // Horizontal border
    for (int i = 1; i < FULL_AREA_WIDTH - 1; i++) {
        mBorder.emplace_back(i, FULL_AREA_HEIGHT - 1, Block::Border);
    }

    // Horizontal border
    for (int i = 0; i < PLAY_AREA_WIDTH; i++) {
        for (int j = 0; j < PLAY_AREA_HEIGHT; j++) {
            mPlayArea[i][j].setPosition(i + 1, j);
        }
    }

    setOrigin((FULL_AREA_WIDTH * BLOCK_SIZE) / 2, (FULL_AREA_HEIGHT * BLOCK_SIZE) / 2);
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    for (auto& block : mBorder) {
        target.draw(block, states);
    }

    for (auto& line : mPlayArea) {
        for (auto& block : line) {
            target.draw(block, states);
        }
    }
}
