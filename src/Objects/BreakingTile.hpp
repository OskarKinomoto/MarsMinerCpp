#pragma once

#include "../Utils/Utils.hpp"

class Tile;

class BreakingTile {
public:
    Tile *tile = nullptr;
    bool destroyed = true;
    PositionF position{};

public:
    BreakingTile() = default;
    BreakingTile(Tile *tile);

public:
    void Destroy();
    void Reset();

private:
    void positionInit();
};
