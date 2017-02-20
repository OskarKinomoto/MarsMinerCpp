#pragma once

#include "../Utils/Utils.hpp"

#include <vector>
#include <memory>

class Tile;

class CollisionTile {
 public:
  enum class Position {
    Bottom = 0,
    Left = 1,
    Top = 2,
    Right = 3,
  };

 public:
  CollisionTile(Tile *tile, Position position);

 public:
  Tile *tile;
  Position position;

 public:
  bool Breakable();
  float Right();
  float Left();
  float Top();
  float Bottom();
  bool Collide(Vector2 robot);
};

bool operator<(const CollisionTile& a, const CollisionTile& b);

typedef std::vector<CollisionTile> CollisionTiles;
