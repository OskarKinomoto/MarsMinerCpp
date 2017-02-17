#pragma once

#include "Tile.hpp"

class BreakingTile {
public:
    Tile *tile = nullptr;
    bool destroyed = true;
    Position position;

public:
    BreakingTile() = default;
    BreakingTile(Tile *tile);

private:
    void positionInit();
};
