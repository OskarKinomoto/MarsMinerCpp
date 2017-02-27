#include "Robot.hpp"

#include <iomanip>
#include <assert.h>
#include <cmath>

#include "../Painter/Sprite.hpp"
#include "../Objects/Model.hpp"

#include "../Utils/Log.hpp"

#include "Physics.hpp"

#define SetXPos(X)  \
  do {              \
    position.x = X; \
    velocity.x = 0; \
  } while (0);

#define SetYPos(Y)  \
  do {              \
    position.y = Y; \
    velocity.y = 0; \
  } while (0);

const SizeI Robot::size{Tile::Size * 0.8f, Tile::Size * 0.8f};
float Robot::deepLogDt = 1.f;
float Robot::margin = 5.f;

namespace {

constexpr float angleMarginForRobotDirection = 0.1f;
}

void Robot::Paint(Painter p, Camera) {
  p.Textures(true);
  Sprite::UseTexture();

  p.BeginQuads();
  p.Sprite(position, size, Layer::Robot, sprite);
  p.EndQuads();
}

void Robot::Tick(float dt) {
  if (tileDestroy) {
    tileDestroy = false;
    breakingTile.Reset();
  }

  newDestroy = false;

  switch (state) {
    case State::Move:
      TickMove(dt);
      break;
    case State::Break:
      TickBreak(dt);
      break;
  }
}

float Robot::HeightInFeets() {
  return (position.y / Tile::Size) * 0.25f;
}

PositionF Robot::Center() {
  return position + (size * 0.5f);
}

VectorsF Robot::Verticies() const {
  VectorsF ret(4);
  ret.at(0) = position;
  ret.at(1) = {position.x, position.y + size.y};
  ret.at(2) = {position.x + size.y, position.y};
  ret.at(3) = {position.x + size.y, position.y + size.y};
  return ret;
}

VectorF Robot::BottomTile(const VectorsF& tiles) {
  if (tiles.size() == 1)
    return tiles[0];

  assert(tiles.size() == 2);

  auto center = Center();

  auto left = (tiles[0].x + Model::LeftX) * Tile::Size;
  auto right = (tiles[0].x + Model::LeftX + 1) * Tile::Size;

  if (left < center.x && center.x < right)
    return tiles[0];

  return tiles[1];
}

void Robot::SetMineralToRecieve(Mineral mineral) {
  this->mineral = mineral;
}

void Robot::SetCollisionTiles(std::vector<CollisionTile>&& tiles) {
  collisionTiles = std::move(tiles);
  collisionTilesWasSet = true;
}

bool Robot::IsBreaking() {
  return state == State::Break;
}

void Robot::TickMove(float dt) {
  assert(collisionTilesWasSet);

  drill.Tick(dt);

  bool canBreak = drill.Cooled() && engine.state.running;

  isBreaking = RobotBreaking::None;
  possibleBreaking.breaking = engine.Breaking();

  bool wasMovingAtBeginOfTick = velocity.LenghtSquared() > 0;

  if (engine.state.running) {
    auto a = std::cos(engine.state.angle);

    if (a < -angleMarginForRobotDirection)
      sprite = Sprite::Name::RobotLeft;
    if (a > angleMarginForRobotDirection)
      sprite = Sprite::Name::RobotRight;

    // TODO: engine.UseFuel(fuel, dt);
  }

  auto forces = engine.Force() + Physics::Forces(*this);

  velocity += forces * dt;

  if (std::abs(velocity.y) < 1e-3f && engine.Breaking() != RobotBreaking::Down)
    velocity.y = 0;

  if (std::abs(velocity.y) > 1e-1f)
    possibleBreaking.LeftRight = false;

  if (std::abs(velocity.x) > 5.f)
    possibleBreaking.Down = false;

  auto oldPosition = position;

  position += velocity * dt;

  // Limit at screen edges
  if (position.x < Model::LeftTile + margin)
    SetXPos(Model::LeftTile + margin);

  if (position.x + size.x > Model::RightTile - margin)
    SetXPos(Model::RightTile - size.x - margin);

  float velocityBeforeCollisions =
      wasMovingAtBeginOfTick ? velocity.Lenght() : 0;

  // Magick algorithm – collisions and tile breaking
  for (CollisionTile& tile : collisionTiles) {
    if (!tile.Collide(position))
      continue;

    switch (tile.position) {
      case CollisionTile::Position::Bottom:
        if (possibleBreaking.IsDown() && tile.Breakable() && canBreak) {
          if (isBreaking == RobotBreaking::None && velocity.y != 0) {
            isBreaking = RobotBreaking::Down;
            possibleBreaking.Down = false;
          }
        } else {
          possibleBreaking.All(true);
          SetYPos(tile.Bottom());
        }
        break;

      case CollisionTile::Position::Left:
        if (possibleBreaking.IsLeft() && tile.Breakable() && canBreak)
          isBreaking = RobotBreaking::Left;
        else
          SetXPos(tile.Left());
        break;

      case CollisionTile::Position::Top:
        SetYPos(tile.Top());
        break;

      case CollisionTile::Position::Right:
        if (possibleBreaking.IsRight() && tile.Breakable() && canBreak)
          isBreaking = RobotBreaking::Right;
        else
          SetXPos(tile.Right());
        break;
    }
  }

  if (isBreaking != RobotBreaking::None) {
    newDestroy = true;
    SetState(State::Break);
  } else if (std::abs(oldPosition.LenghtSquared() - position.LenghtSquared()) >
             Drill::MoveToHeatDrillSquared) {
    drill.Heated();
  }

  if (wasMovingAtBeginOfTick) {
    auto velocityAfterCollisions = velocity.Lenght();
    hull.Hit(velocityBeforeCollisions, velocityAfterCollisions);
  }

  // Log robot
  s += dt;
  if (s > deepLogDt) {
    s -= deepLogDt;
    LOGVV("Robot – Deep: " << std::fixed << std::setprecision(2)
                           << HeightInFeets() << "m");
  }

  collisionTilesWasSet = false;
}

void Robot::TickBreak(float dt) {
  // drill.UseFuel(fuel, dt);

  auto d = breakingTile.position - position;
  auto dist = d.Lenght();
  auto move = drill.DrillingSpeed() * dt;

  if (dist <= move) {
    position = breakingTile.position;
    RecieveMineral();
    SetState(State::Move);
    drill.Heated();
    tileDestroy = true;
  } else {
    position += d * move / dist;
  }
}

void Robot::RecieveMineral() {
  if (mineral.notNull)
    cargo.Add(mineral);

  mineral = Mineral::None;
}

void Robot::SetState(Robot::State state) {
  this->state = state;

  switch (state) {
    case State::Move:
      break;

    case State::Break:
      StopMoving();
      break;
  }
}

void Robot::StopMoving() {
  velocity = {};
}

bool Robot::PossibleBreaking::IsDown() {
  return breaking == RobotBreaking::Down && Down;
}

bool Robot::PossibleBreaking::IsLeft() {
  return breaking == RobotBreaking::Left && LeftRight;
}

bool Robot::PossibleBreaking::IsRight() {
  return breaking == RobotBreaking::Right && LeftRight;
}

void Robot::PossibleBreaking::All(bool value) {
  LeftRight = value;
  Down = value;
}
