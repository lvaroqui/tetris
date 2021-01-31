#pragma once

#include "Block.hpp"

namespace Tetromino {
typedef std::array<std::array<bool, 4>, 4> Layout;

class Base {
public:
    Base(Block::Type type, const Layout* layout) : mType(type), mLayout(layout) {}
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

    std::array<sf::Vector2<int>, 4> toCoord() const {
        std::array<sf::Vector2<int>, 4> ret;
        int index = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (layout()[j][i]) {
                    auto pos = position();
                    ret[index++] = {i + pos.x, j + pos.y};
                }
            }
        }
        return ret;
    }

    const Layout& layout() const { return *mLayout; }
    Block::Type type() const { return mType; }

    virtual std::unique_ptr<Base> clone() const = 0;

protected:
    void setLayout(const Layout* layout) { mLayout = layout; }

private:
    int mX = 0, mY = 0;
    Block::Type mType;
    const Layout* mLayout;
};

template <std::size_t N>
class BaseWithLayout : public Base {
public:
    typedef std::array<Layout, N> LayoutArray;

    BaseWithLayout(Block::Type type, const LayoutArray& arr)
        : Base(type, &arr[0]), layout(arr) {}

    void rotateLeft() override {
        index = (index - 1) % N;
        setLayout(&layout[index]);
    }

    void rotateRight() override {
        index = (index + 1) % N;
        setLayout(&layout[index]);
    }

private:
    int index = 0;
    LayoutArray layout;
};

class O : public Base {
    static constexpr Layout layout = {{{0, 0, 0, 0},
                                       {0, 1, 1, 0},
                                       {0, 1, 1, 0},
                                       {0, 0, 0, 0}}};

public:
    O() : Base(Block::O, &layout) {}

    void rotateLeft() override {}
    void rotateRight() override {}

    std::unique_ptr<Base> clone() const override {
        return std::make_unique<O>(*this);
    }
};

class L : public BaseWithLayout<4> {
    static constexpr LayoutArray layout =
        {{{{{0, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 1, 0}}},
          {{{0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 1, 1, 0},
            {1, 0, 0, 0}}},
          {{{0, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0}}},
          {{{0, 0, 0, 0},
            {0, 0, 1, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0}}}}};

public:
    L() : BaseWithLayout(Block::L, layout) {}

    std::unique_ptr<Base> clone() const override {
        return std::make_unique<L>(*this);
    }
};

class I : public BaseWithLayout<2> {
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

class J : public BaseWithLayout<4> {
    static constexpr LayoutArray layout =
        {{{{{0, 0, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 1, 1, 0}}},
          {{{0, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 1, 1},
            {0, 0, 0, 0}}},
          {{{0, 0, 0, 0},
            {0, 0, 1, 1},
            {0, 0, 1, 0},
            {0, 0, 1, 0}}},
          {{{0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 1, 1, 1},
            {0, 0, 0, 1}}}}};

public:
    J() : BaseWithLayout(Block::J, layout) {}

    std::unique_ptr<Base> clone() const override {
        return std::make_unique<J>(*this);
    }
};


class T : public BaseWithLayout<4> {
    static constexpr LayoutArray layout =
        {{{{{0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 1, 0, 0}}},
          {{{0, 0, 0, 0},
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 0, 0}}},
          {{{0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 1, 0, 0},
            {1, 1, 1, 0}}},
          {{{0, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 0, 0}}}}};

public:
    T() : BaseWithLayout(Block::T, layout) {}

    std::unique_ptr<Base> clone() const override {
        return std::make_unique<T>(*this);
    }
};

class Z : public BaseWithLayout<4> {
    static constexpr LayoutArray layout =
        {{{{{0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 1, 0}}},
          {{{0, 0, 0, 0},
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {1, 0, 0, 0}}},
          {{{0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 1, 0}}},
          {{{0, 0, 0, 0},
            {0, 0, 1, 0},
            {0, 1, 1, 0},
            {0, 1, 0, 0}}}}};

public:
    Z() : BaseWithLayout(Block::Z, layout) {}

    std::unique_ptr<Base> clone() const override {
        return std::make_unique<Z>(*this);
    }
};

class S : public BaseWithLayout<4> {
    static constexpr LayoutArray layout =
        {{{{{0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {1, 1, 0, 0}}},
          {{{0, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 0, 0}}},
          {{{0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {1, 1, 0, 0}}},
          {{{0, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 1, 0}}}}};

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
