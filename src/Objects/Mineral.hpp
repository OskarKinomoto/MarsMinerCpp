#pragma once

#include <vector>

#include "../Painter/Sprite.hpp"



class Mineral {
public:
    static const Mineral None;
    static const Mineral Gold;
    static const Mineral Lapis;
    static const Mineral Silver;
    static const Mineral Platinium;
    static const Mineral Rubin;
    static const Mineral Copper;
    static const Mineral Saphire;
    static const Mineral Salt;
    static const Mineral Emerald;
    static const Mineral Fe;

    Sprite::Name GetSprite() const;

    static Mineral *RandomByDepth(int TileDepth);

public:
    Mineral();

public:
    bool notNull;

private:
    Mineral(Sprite::Name sprite, int price);

private:
    const Sprite::Name sprite;
    const int price;

private:
    static std::vector<Mineral*> list;
};
