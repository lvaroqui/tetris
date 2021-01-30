#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#include "Block.hpp"
#include "Tetromino.hpp"

class Grid : public sf::Drawable {
public:
    Grid();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool free(int x, int y) {
        return mPlayArea[x][y].type() == Block::None;
    }

    bool spawnTetromino() {
        Block::Type type = (Block::Type)distrib(gen);
        switch (type) {
            case Block::I:
                mActiveTetromino = std::make_unique<Tetromino::I>();
                break;
            case Block::J:
                mActiveTetromino = std::make_unique<Tetromino::J>();
                break;
            case Block::L:
                mActiveTetromino = std::make_unique<Tetromino::L>();
                break;
            case Block::O:
                mActiveTetromino = std::make_unique<Tetromino::O>();
                break;
            case Block::S:
                mActiveTetromino = std::make_unique<Tetromino::S>();
                break;
            case Block::T:
                mActiveTetromino = std::make_unique<Tetromino::T>();
                break;
            case Block::Z:
                mActiveTetromino = std::make_unique<Tetromino::Z>();
                break;
            default:
                std::abort();
        }
        mActiveTetromino->setPosition(3, 0);

        for (auto c : mActiveTetromino->toCoord()) {
            auto& block = mPlayArea[c.x][c.y];
            if (block.type() != Block::None) {
                return false;
            }
            block.setType(type);
        }
        return true;
    }

    bool down() {
        bool moved = moveTetromino(0, 1);

        if (!moved) {
            clear();
            mActiveTetromino.release();
        }

        return moved;
    }

    void clear() {
        std::vector<int> fullLines;
        fullLines.reserve(4);

        // Find full lines
        for (int i = 0; i < PLAY_AREA_HEIGHT; i++) {
            bool full = true;
            for (int j = 0; j < PLAY_AREA_WIDTH; j++) {
                if (mPlayArea[j][i].type() == Block::None) {
                    full = false;
                    break;
                }
            }

            if (full) {
                fullLines.push_back(i);
            }
        }

        if (!fullLines.empty()) {
            // "Delete" full lines
            for (auto line : fullLines) {
                for (int i = line; i > 1; i--) {
                    for (int j = 0; j < PLAY_AREA_WIDTH; j++) {
                        mPlayArea[j][i].setType(mPlayArea[j][i - 1].type());
                    }
                }
            }
            
            // Clear top line
            for (int j = 0; j < PLAY_AREA_WIDTH; j++) {
                mPlayArea[j][0].setType(Block::None);
            }
        }
    }

    void drop() {
        if (!mActiveTetromino) {
            return;
        }
        while (down()) {
        };
    }

    void left() {
        if (!mActiveTetromino) {
            return;
        }
        moveTetromino(-1, 0);
    }

    void right() {
        if (!mActiveTetromino) {
            return;
        }
        moveTetromino(1, 0);
    }

    void rotateRight() {
        if (!mActiveTetromino) {
            return;
        }
        hideTetromino();
        auto newPos = mActiveTetromino->clone();

        newPos->rotateRight();

        if (!validate(*newPos)) {
            showTetromino();
            return;
        }

        mActiveTetromino = std::move(newPos);
        showTetromino();
    }

private:
    bool moveTetromino(int dX, int dY) {
        hideTetromino();
        auto newPos = mActiveTetromino->clone();

        newPos->move(dX, dY);

        if (!validate(*newPos)) {
            showTetromino();
            return false;
        }

        mActiveTetromino->move(dX, dY);
        showTetromino();

        return true;
    }

    bool validate(Tetromino::Base& tetr) {
        for (auto c : tetr.toCoord()) {
            if (c.y >= PLAY_AREA_HEIGHT) {
                return false;
            }

            if (c.x < 0 || c.x >= PLAY_AREA_WIDTH) {
                return false;
            }

            if (mPlayArea[c.x][c.y].type() != Block::None) {
                return false;
            }
        }
        return true;
    }

    void showTetromino() {
        for (auto c : mActiveTetromino->toCoord()) {
            mPlayArea[c.x][c.y].setType(mActiveTetromino->type());
        }
    }

    void hideTetromino() {
        for (auto c : mActiveTetromino->toCoord()) {
            mPlayArea[c.x][c.y].setType(Block::None);
        }
    }

    std::vector<Block> mBorder;
    std::array<std::array<Block, PLAY_AREA_HEIGHT>, PLAY_AREA_WIDTH> mPlayArea;
    std::unique_ptr<Tetromino::Base> mActiveTetromino;

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen;       //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<int> distrib;
};
