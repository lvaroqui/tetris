#pragma once

#include "Block.hpp"

namespace Tetromino {

template <size_t N>
using Layout = std::array<std::array<bool, N>, N>;

class Base {
public:
    Base(Block::Type type) : mType(type) {}
    virtual ~Base() = default;

    virtual void rotateLeft() = 0;
    virtual void rotateRight() = 0;

    sf::Vector2<int> position() const { return {mX, mY}; }

    void setPosition(int x, int y) {
        mX = x;
        mY = y;
    }

    void move(int dX, int dY) {
        mX += dX;
        mY += dY;
    }

    virtual std::array<sf::Vector2<int>, 4> toCoord() const = 0;

    Block::Type type() const { return mType; }

    virtual std::unique_ptr<Base> clone() const = 0;

private:
    int mX = 0, mY = 0;
    Block::Type mType;
};

template <std::size_t LAYOUT_WIDTH, std::size_t LAYOUT_NB>
class BaseWithLayout : public Base {
public:
    typedef std::array<Layout<LAYOUT_WIDTH>, LAYOUT_NB> LayoutArray;

    BaseWithLayout(Block::Type type, const LayoutArray& arr)
        : Base(type), mLayout(arr) {}

    void rotateLeft() override {
        mIndex - 1;
        if (mIndex > 0) {
            mIndex = LAYOUT_NB - 1;
        }
    }

    void rotateRight() override {
        mIndex++;
        if (mIndex >= LAYOUT_NB) {
            mIndex = 0;
        }
    }

    std::array<sf::Vector2<int>, 4> toCoord() const override {
        std::array<sf::Vector2<int>, 4> ret;
        int index = 0;
        for (int i = 0; i < LAYOUT_WIDTH; i++) {
            for (int j = 0; j < LAYOUT_WIDTH; j++) {
                if (mLayout[mIndex][j][i]) {
                    auto pos = position();
                    ret[index++] = {i + pos.x, j + pos.y};
                }
            }
        }
        return ret;
    }

private:
    int mIndex = 0;
    LayoutArray mLayout;
};

class O : public BaseWithLayout<2, 1> {
    static constexpr LayoutArray layout = {{{{
        {1, 1},
        {1, 1},
    }}}};

public:
    O() : BaseWithLayout(Block::O, layout) {}

    std::unique_ptr<Base> clone() const override {
        return std::make_unique<O>(*this);
    }
};

class L : public BaseWithLayout<3, 4> {
    static constexpr LayoutArray layout =
        {{{{{0, 1, 0},
            {0, 1, 0},
            {0, 1, 1}}},
          {{{0, 0, 0},
            {1, 1, 1},
            {1, 0, 0}}},
          {{{1, 1, 0},
            {0, 1, 0},
            {0, 1, 0}}},
          {{{0, 0, 1},
            {1, 1, 1},
            {0, 0, 0}}}}};

public:
    L() : BaseWithLayout(Block::L, layout) {}

    std::unique_ptr<Base> clone() const override {
        return std::make_unique<L>(*this);
    }
};

class I : public BaseWithLayout<4, 2> {
    static constexpr LayoutArray layout = {{{{{0, 1, 0, 0},
                                              {0, 1, 0, 0},
                                              {0, 1, 0, 0},
                                              {0, 1, 0, 0}}},
                                            {{{0, 0, 0, 0},
                                              {0, 0, 0, 0},
                                              {1, 1, 1, 1},
                                              {0, 0, 0, 0}}}}};

public:
    I() : BaseWithLayout(Block::I, layout) {}

    std::unique_ptr<Base> clone() const override {
        return std::make_unique<I>(*this);
    }
};

class J : public BaseWithLayout<3, 4> {
    static constexpr LayoutArray layout =
        {{{{{0, 1, 0},
            {0, 1, 0},
            {1, 1, 0}}},
          {{{1, 0, 0},
            {1, 1, 1},
            {0, 0, 0}}},
          {{{0, 1, 1},
            {0, 1, 0},
            {0, 1, 0}}},
          {{{0, 0, 0},
            {1, 1, 1},
            {0, 0, 1}}}}};

public:
    J() : BaseWithLayout(Block::J, layout) {}

    std::unique_ptr<Base> clone() const override {
        return std::make_unique<J>(*this);
    }
};

class T : public BaseWithLayout<3, 4> {
    static constexpr LayoutArray layout =
        {{{{{0, 0, 0},
            {1, 1, 1},
            {0, 1, 0}}},
          {{{0, 1, 0},
            {1, 1, 0},
            {0, 1, 0}}},
          {{{0, 0, 0},
            {0, 1, 0},
            {1, 1, 1}}},
          {{{0, 1, 0},
            {0, 1, 1},
            {0, 1, 0}}}}};

public:
    T() : BaseWithLayout(Block::T, layout) {}

    std::unique_ptr<Base> clone() const override {
        return std::make_unique<T>(*this);
    }
};

class Z : public BaseWithLayout<3, 4> {
    static constexpr LayoutArray layout =
        {{{{{0, 0, 0},
            {1, 1, 0},
            {0, 1, 1}}},
          {{{0, 1, 0},
            {1, 1, 0},
            {1, 0, 0}}},
          {{{0, 0, 0},
            {1, 1, 0},
            {0, 1, 1}}},
          {{{0, 0, 1},
            {0, 1, 1},
            {0, 1, 0}}}}};

public:
    Z() : BaseWithLayout(Block::Z, layout) {}

    std::unique_ptr<Base> clone() const override {
        return std::make_unique<Z>(*this);
    }
};

class S : public BaseWithLayout<3, 4> {
    static constexpr LayoutArray layout =
        {{{{
            {0, 0, 0},
            {0, 1, 1},
            {1, 1, 0}}},
          {{
            {1, 0, 0},
            {1, 1, 0},
            {0, 1, 0}}},
          {{
            {0, 0, 0},
            {0, 1, 1},
            {1, 1, 0}}},
          {{
            {0, 1, 0},
            {0, 1, 1},
            {0, 0, 1}}}}};

public:
    S() : BaseWithLayout(Block::S, layout) {}

    std::unique_ptr<Base> clone() const override {
        return std::make_unique<S>(*this);
    }
};

class Factory {
public:
    static std::unique_ptr<Base> create(Block::Type type) {
        switch (type) {
            case Block::I:
                return std::make_unique<Tetromino::I>();
            case Block::J:
                return std::make_unique<Tetromino::J>();
            case Block::L:
                return std::make_unique<Tetromino::L>();
            case Block::O:
                return std::make_unique<Tetromino::O>();
            case Block::S:
                return std::make_unique<Tetromino::S>();
            case Block::T:
                return std::make_unique<Tetromino::T>();
            case Block::Z:
                return std::make_unique<Tetromino::Z>();
            default:
                return nullptr;
        }
    }
};

}  // namespace Tetromino
