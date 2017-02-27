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
    Tile* operator()(size_t x, size_t y);

public:
    VectorsF TilesOnRobot(const Robot &r);
    CollisionTiles GenCollisionTiles(VectorsF robotOnTiles);

public:
    void Paint(Painter p, Camera c) override;

private:
    VectorsF PossibleTilesOnRobot(VectorF robotPosition);
    bool CheckTileCords(int xx, int yy);
};
