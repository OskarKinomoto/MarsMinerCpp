#include "Tiles.hpp"

#include <cmath>
#include <algorithm>

#include "Model.hpp"

#include "../Robot/Robot.hpp"

Tiles::Tiles() {
  size_t XSize = Model::MapXSize;
  tiles.resize(static_cast<size_t>(XSize * Model::MaxDepth));

  for (size_t x = 0; x < XSize; x++)
    for (size_t y = 0; y < Model::MaxDepth; y++)
      *at(x, y) = Tile(Model::LeftX + x, -y);
}

Tile* Tiles::operator()(size_t x, size_t y) {
  size_t index = x + y * Model::MapXSize;

  if (index >= tiles.size())
    throw Exception{"Tiles – Out of range"};

  return &tiles[index];
}

Tile* Tiles::at(size_t x, size_t y) {
  return this->operator()(x, y);
}

VectorsF Tiles::TilesOnRobot(const Robot& r) {
  VectorsF ret{};

  auto PossibleTiles = PossibleTilesOnRobot(r.position);
  auto RobotVertices = r.Verticies();

  for (auto& tile : PossibleTiles) {
    VectorF tileReal{tile.x + Model::LeftX, -tile.y - 1};

    bool isAnyVertexInTile = false;
    for (auto& RobotVertex : RobotVertices) {
      if (Tile::VertexInTile(tileReal, RobotVertex)) {
        isAnyVertexInTile = true;
        break;
      }
    }

    if (isAnyVertexInTile)
      ret.push_back(tile);
  }

  return ret;
}

CollisionTiles Tiles::GenCollisionTiles(VectorsF robotOnTiles) {
  CollisionTiles ret{};
  auto Add = [&](int xx, int yy, CollisionTile::Position pos) {
    if (CheckTileCords(xx, yy) && at(xx, yy)->Collisionable())
      ret.push_back({at(xx, yy), pos});
  };

  for (auto& tile : robotOnTiles) {
    int xx = tile.x;
    int yy = tile.y;

    Add(xx + 1, yy, CollisionTile::Position::Right);
    Add(xx - 1, yy, CollisionTile::Position::Left);
    Add(xx, yy + 1, CollisionTile::Position::Bottom);
    Add(xx, yy - 1, CollisionTile::Position::Top);
  }

  std::sort(ret.begin(), ret.end());
  return ret;
}

void Tiles::Paint(Painter p, Camera c) {
  int yStart =
      static_cast<int>((-c.position.y - p.Height() / 2) / Tile::Size - 1);
  int yEnd = static_cast<int>(
      std::floor((-c.position.y + p.Height() / 2) / Tile::Size + 1));
  int xStart =
      static_cast<int>((-c.position.x - p.Width() / 2) / Tile::Size - 1);
  int xEnd = static_cast<int>((-c.position.x + p.Width() / 2) / Tile::Size + 1);

  // Tiles are only underground
  if (yEnd > 0)
    yEnd = 0;

  if (yStart <= -Model::MaxDepth)
    yStart = -Model::MaxDepth - 1;

  // Tiles only between MinX – MaxX
  if (xEnd > Model::RightX)
    xEnd = Model::RightX;

  if (xStart < Model::LeftX)
    xStart = Model::LeftX;

  p.Textures(true);
  Sprite::UseTexture();
  p.BeginQuads();

  for (int x = xStart; x < xEnd; ++x)
    for (int y = yStart; y <= yEnd; ++y)
      at(x - Model::LeftTile, -y)->Paint(p, c);

  for (auto& tile : tiles) {
    tile.Paint(p, c);
  }

  p.EndQuads();
}

VectorsF Tiles::PossibleTilesOnRobot(VectorF robotPosition) {
  VectorsF ret{};

  auto xs = robotPosition.x / Tile::Size;
  auto ys = robotPosition.y / Tile::Size;

  int yy = static_cast<int>(std::ceil(ys * -1)) - 1;
  int xx = static_cast<int>(std::floor(xs)) - Model::LeftX;

  auto Add = [&](float x, float y) { ret.push_back({x, y}); };

  Add(xx, yy);
  Add(xx + 1, yy);
  Add(xx, yy - 1);
  Add(xx + 1, yy - 1);

  return ret;
}

bool Tiles::CheckTileCords(int xx, int yy) {
  return xx >= 0 && yy >= 0 && xx < Model::MapXSize && yy < Model::MaxDepth;
}
