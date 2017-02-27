#pragma once

#include "Tiles.hpp"

#include "../Interfaces/TickInterface.hpp"
#include "../Robot/Robot.hpp"

class Model : public TickInterface{
public:
    static const int MaxDepth = 300;
    static const int MapXSize = 40;
    static const int LeftX = -MapXSize / 2;
    static const int RightX = MapXSize / 2 - 1;

    static const int LeftTile = LeftX * Tile::Size;
    static const int RightTile = RightX * Tile::Size;

public:
    Model();

public:
    Tiles tiles;
    Robot robot;

    // TickInterface interface
public:
    void Tick(float dt) override;

private:
    void ProcessBreakingTile(VectorsF tilesOnRobot, RobotBreaking robotStatusBreking, bool robotOldStatus);
    Tile *TileToBreak(const VectorsF &tilesOnRobot, RobotBreaking robotStatusBreking);
};
