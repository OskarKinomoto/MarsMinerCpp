#pragma once

#include "Tiles.hpp"

class Model {
public:
    static const int MaxDepth = 300;
    static const int MapXSize = 40;
    static const int LeftX = -MapXSize / 2;
    static const int RightX = MapXSize / 2 - 1;

    static const int LeftTile = LeftX * Tile::Size;
    static const int RightTile = RightX * Tile::Size;

public:
    Model() = default;

public:
    Tiles tiles;
};
