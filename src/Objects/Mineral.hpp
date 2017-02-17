#pragma once

#include "../Painter/Sprite.hpp"

class Mineral {
public:
    static const Mineral None;
    static const Mineral Gold;

    Sprite::Name GetSprite();

    static Mineral RandomByDepth(int TileDepth);

public:
    Mineral();

public:
    bool notNull;

private:
    Mineral(Sprite::Name sprite);

private:
    Sprite::Name sprite;
};
