#pragma once

#include <vector>

#include "Tile.hpp"

#include "../Utils/Utils.hpp"
#include "CollisionTile.hpp"

class Robot;

class Tiles : public PaintInterface {
private:
    std::vector<Tile> tiles;

public:
    Tiles();

public:
    decltype (tiles[0]) &operator()(size_t x, size_t y);

public:
    Vectors TilesOnRobot(const Robot &r);
    CollisionTiles GenCollisionTiles(Vectors robotOnTiles);

public:
    void Paint(Painter p, Camera c) override;

private:
    Vectors PossibleTilesOnRobot(Vector2 robotPosition);
    bool CheckTileCords(int xx, int yy);
};
