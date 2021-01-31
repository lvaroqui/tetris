#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#include "Block.hpp"
#include "Tetromino.hpp"

class Grid : public sf::Drawable, public sf::Transformable {
public:
    Grid();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool free(int x, int y) {
        return mPlayArea[x][y].type() == Block::None;
    }

    bool spawnTetromino() {
        Block::Type type = (Block::Type)distrib(gen);
        
        mActiveTetromino = Tetromino::Factory::create(type);

        if (!mActiveTetromino) {
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
        computeGhost();
        return true;
    }

    void down() {
        moveTetromino(0, 1);

        if (isStuck()) {
            clear();
        }
    }

    bool isStuck() {
        auto tmp = mActiveTetromino->clone();
        tmp->move(0, 1);

        hideTetromino();
        bool stuck = !isValid(*tmp);
        showTetromino();
        return stuck;
    }

    void clear() {
        std::vector<int> fullLines;
        fullLines.reserve(4);

        // Find full lines
        for (int i = 0; i < PLAY_AREA_HEIGHT; i++) {
            bool full = true;
            for (int j = 0; j < PLAY_AREA_WIDTH; j++) {
                if (mPlayArea[j][i].type() < Block::First) {
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
        while (!isStuck()) {
            down();
        };
    }

    void left() {
        if (!mActiveTetromino) {
            return;
        }
        moveTetromino(-1, 0);
        computeGhost();
    }

    void right() {
        if (!mActiveTetromino) {
            return;
        }
        moveTetromino(1, 0);
        computeGhost();
    }

    void rotateRight() {
        if (!mActiveTetromino) {
            return;
        }
        hideTetromino();
        auto newPos = mActiveTetromino->clone();

        newPos->rotateRight();

        if (!isValid(*newPos)) {
            showTetromino();
            return;
        }

        mActiveTetromino = std::move(newPos);
        showTetromino();

        computeGhost();
    }

private:
    bool moveTetromino(int dX, int dY) {
        hideTetromino();
        auto newPos = mActiveTetromino->clone();

        newPos->move(dX, dY);

        if (!isValid(*newPos)) {
            showTetromino();
            return false;
        }

        mActiveTetromino->move(dX, dY);
        showTetromino();

        return true;
    }

    bool isValid(Tetromino::Base& tetr) {
        for (auto c : tetr.toCoord()) {
            if (c.y >= PLAY_AREA_HEIGHT) {
                return false;
            }

            if (c.x < 0 || c.x >= PLAY_AREA_WIDTH) {
                return false;
            }

            if (mPlayArea[c.x][c.y].type() >= Block::First) {
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

    void computeGhost() {
        // Clean previous ghost
        if (mGhostTetromino) {
            for (auto c : mGhostTetromino->toCoord()) {
                if (mPlayArea[c.x][c.y].type() == Block::Ghost) {
                    mPlayArea[c.x][c.y].setType(Block::None);
                }
            }
        }

        mGhostTetromino = mActiveTetromino->clone();
        hideTetromino();
        while (isValid(*mGhostTetromino)) {
            mGhostTetromino->move(0, 1);
        }
        mGhostTetromino->move(0, -1);

        for (auto c : mGhostTetromino->toCoord()) {
            mPlayArea[c.x][c.y].setType(Block::Ghost);
        }

        showTetromino();
    }

    std::vector<Block> mBorder;
    std::array<std::array<Block, PLAY_AREA_HEIGHT>, PLAY_AREA_WIDTH> mPlayArea;
    std::unique_ptr<Tetromino::Base> mActiveTetromino;
    std::unique_ptr<Tetromino::Base> mGhostTetromino;

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen;       //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<int> distrib;
};
