#include "CollisionTile.hpp"

#include "Tile.hpp"
#include "../Robot/Robot.hpp"

CollisionTile::CollisionTile(Tile* tile, CollisionTile::Position position)
    : tile(tile), position(position) {}

bool CollisionTile::Breakable() {
  return tile->Breakable();
}

float CollisionTile::Right() {
  return tile->x * Tile::Size - Robot::size.x - 1;
}

float CollisionTile::Left() {
  return (tile->x + 1) * Tile::Size + 1;
}

float CollisionTile::Top() {
  return (tile->y - 1) * Tile::Size - Robot::size.x - 1;
}

float CollisionTile::Bottom() {
  return tile->y * Tile::Size + 1;
}

bool CollisionTile::Collide(Vector2 robot) {
  switch (position) {
    case Position::Bottom:
      return robot.y <= Bottom();
    case Position::Left:
      return robot.x <= Left();
    case Position::Top:
      return robot.y >= Top();
    case Position::Right:
      return robot.x >= Right();
  }

  throw Exception{"CollisionTile::Colide"};
}

bool operator<(const CollisionTile& a, const CollisionTile& b) {
  return static_cast<int>(a.position) < static_cast<int>(b.position);
}
