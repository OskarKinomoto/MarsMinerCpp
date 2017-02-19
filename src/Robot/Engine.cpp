#include "Engine.hpp"

#include <cmath>
#include "../Utils/Exception.hpp"
#include "../Utils/Log.hpp"

constexpr float AngleMargin = M_PI / 12;

RobotBreaking Engine::Breaking() {
  if (-state.angle > -AngleMargin + M_PI / 2 &&
      -state.angle < AngleMargin + M_PI / 2)
    return RobotBreaking::Down;

  if (state.angle > -AngleMargin + M_PI / 2 &&
      state.angle < AngleMargin + M_PI / 2)
    return RobotBreaking::Up;

  if (state.angle < AngleMargin && state.angle > -AngleMargin)
    return RobotBreaking::Right;

  if (state.angle < AngleMargin + M_PI && state.angle > -AngleMargin + M_PI)
    return RobotBreaking::Left;

  return RobotBreaking::None;
}

Vector2 Engine::Force() {
  Vector2 force{};

  if (state.running) {
    force.x = cos(state.angle) * HorizontalForce();

    auto y = sin(state.angle);
    if (y > 0)
      force.y = y * UpForce();
    else if (y < 0)
      force.y = y * DownForce();
  }
  return force;
}

float Engine::UpForce() {
  return UpForce(model);
}

float Engine::DownForce() {
  return DownForce(model);
}

float Engine::HorizontalForce() {
    return HorizontalForce(model);
}

void Engine::SetFromKeyboard(bool left, bool right, bool up, bool down)
{
    Vector2 keyboardArrows{};
    if (left ^ right) {
        if (left)
            keyboardArrows.x = -1;
        if (right)
            keyboardArrows.x = 1;
    }

    if (down ^ up) {
        if (down)
            keyboardArrows.y = -1;
        if (up)
            keyboardArrows.y = 1;
    }

    state.running = (left ^ right) | (up ^ down);
    state.angle = keyboardArrows.Angle();

    //LOGVV("Engine: " << (state.running ? "" : "not ") << "running; angle: " << state.angle);
}

float Engine::UpForce(Engine::Model m) {
  switch (m) {
    case Model::Standard:
      return 180;
    case Model::StandardPlus:
      return UpForce(Model::Standard) * 1.2f;
  }

  throw Exception{"Engine UpForce"};
}

float Engine::DownForce(Engine::Model m) {
  switch (m) {
    case Model::Standard:
      return 100;
    case Model::StandardPlus:
      return DownForce(Model::Standard) * 1.2f;
  }

  throw Exception{"Engine DownForce"};
}

float Engine::HorizontalForce(Engine::Model m) {
  switch (m) {
    case Model::Standard:
      return 200;
    case Model::StandardPlus:
      return DownForce(Model::Standard) * 1.2f;
  }

  throw Exception{"Engine HorizontalForce"};
}
