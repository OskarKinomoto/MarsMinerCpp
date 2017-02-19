#include "Model.hpp"

#include "../Utils/Log.hpp"

Model::Model()
{
    LOGV("Model – Max depth: " << MaxDepth);
    LOGV("Model – Map tile width: " << MapXSize);

    LOGV("Model – LeftX: " << LeftX);
    LOGV("Model – RightX: " << RightX);

    LOGV("Model – LeftTile: " << LeftTile);
    LOGV("Model – RightTile: " << RightTile);
}


void Model::Tick(float dt)
{
    robot.SetCollisionTiles(tiles.GenCollisionTiles(tiles.TilesOnRobot(robot)));
    robot.Tick(dt);
}
