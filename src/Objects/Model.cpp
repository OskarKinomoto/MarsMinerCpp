#include "Model.hpp"

#include "../Utils/Log.hpp"

Tile * Model::TileToBreak(const Vectors& tilesOnRobot,
                        RobotBreaking robotStatusBreking) {
  auto robotTilePosition = tilesOnRobot[0];
  auto robotTilePosToTile = [&](int x, int y) {
    return tiles(robotTilePosition.x + x, robotTilePosition.y + y);
  };

  Tile *tileToBreak = nullptr;
  switch (robotStatusBreking) {
    case RobotBreaking::Left:
      tileToBreak = robotTilePosToTile(-1, 0);
      break;
    case RobotBreaking::Right:
      tileToBreak = robotTilePosToTile(1, 0);
      break;
    case RobotBreaking::Down:
      robotTilePosition = robot.BottomTile(tilesOnRobot);
      tileToBreak = robotTilePosToTile(0, 1);
      break;
    default:
      break;
  }

  return tileToBreak;
}

void Model::ProcessBreakingTile(Vectors tilesOnRobot,
                                RobotBreaking robotStatusBreking,
                                bool robotOldStatus) {
  Tile *tileToBreak = TileToBreak(tilesOnRobot, robotStatusBreking);

  if (!tileToBreak)
      return;

  if (tileToBreak->Exists()) {
    if (tileToBreak->Breakable()) {
      robot.breakingTile = tileToBreak->SetCollision();
      robot.SetMineralToRecieve(tileToBreak->GetMineral());
    } else {
      robot.SetState(Robot::State::Move);
    }
  } else if (!robotOldStatus && robot.IsBreaking()) {
    robot.SetState(Robot::State::Move);
  }
}

Model::Model() {
  LOGV("Model – Max depth: " << MaxDepth);
  LOGV("Model – Map tile width: " << MapXSize);

  LOGV("Model – LeftX: " << LeftX);
  LOGV("Model – RightX: " << RightX);

  LOGV("Model – LeftTile: " << LeftTile);
  LOGV("Model – RightTile: " << RightTile);
}

void Model::Tick(float dt) {
  auto breakingTileOld = robot.breakingTile;
  auto robotOldStatus = robot.IsBreaking();
  auto tilesOnRobot = tiles.TilesOnRobot(robot);
  robot.SetCollisionTiles(tiles.GenCollisionTiles(tilesOnRobot));

  if(robot.tileDestroy)
      breakingTileOld.Destroy();

  if (robot.newDestroy)
    ProcessBreakingTile(tilesOnRobot, robot.isBreaking, robotOldStatus);

  robot.Tick(dt);
}
