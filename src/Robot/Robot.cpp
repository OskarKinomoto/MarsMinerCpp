#include "Robot.hpp"

#include <iomanip>
#include <assert.h>

#include "../Painter/Sprite.hpp"
#include "../Objects/Model.hpp"

#include "../Utils/Log.hpp"

#include "Physics.hpp"

#define SetXPos(X)  \
  do {              \
    position.x = X; \
    velocity.x = 0; \
  } while (0);

const Size Robot::size{Tile::Size * 0.8f, Tile::Size * 0.8f};
float Robot::deepLogDt = 1.f;
float Robot::margin = 5.f;

void Robot::Paint(Painter p, Camera) {
  p.Textures(true);
  Sprite::UseTexture();

  p.BeginQuads();
  p.Sprite(position, size, Layer::Robot, Sprite::Name::RobotLeft);
  p.EndQuads();
}

void Robot::Tick(float dt) {
  TickMove(dt);
}

float Robot::HeightInFeets() {
  return (position.y / Tile::Size) * 0.25f;
}

Vector2 Robot::Center() {
  return position + (size / 2.0f);
}

Vectors Robot::Verticies() {
  Vectors ret(4);
  ret.at(0) = position;
  ret.at(1) = {position.x, position.y + size.y};
  ret.at(2) = {position.x + size.y, position.y};
  ret.at(3) = {position.x + size.y, position.y + size.y};
  return ret;
}

Vector2 Robot::BottomTile(const Vectors& tiles) {
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

void Robot::TickMove(float dt) {
  drill.Tick(dt);

  Vector2 forces = engine.Force() + Physics::Forces(*this);

  velocity += forces * dt;
  position += velocity * dt;

  // Limit at screen edges
  if (position.x < Model::LeftTile + margin)
    SetXPos(Model::LeftTile + margin);

  if (position.x + size.x > Model::RightTile - margin)
    SetXPos(Model::RightTile - size.x - margin);

  // Log robot
  s += dt;
  if (s > deepLogDt) {
    s -= deepLogDt;
    LOGVV("Robot – Deep: " << std::fixed << std::setprecision(2)
                           << HeightInFeets() << "m");
  }
}

void Robot::TickBreak(float dt) {
  // drill.UseFuel(fuel);

  auto d = breakingTile.position - position;
  auto dist = d.Lenght();
  auto move = drill.DrillingSpeed() * dt;

  if (dist <= move) {
    position = breakingTile.position;
    breakingTile = BreakingTile{};

    // RecieveMineral();
    // SetState(State::User);
    drill.Heated();

  } else {
    position += d * move / dist;
  }
}

void Robot::RecieveMineral()
{
    if (mineral.notNull)
        cargo.Add(mineral);

    mineral = Mineral::None;
}
