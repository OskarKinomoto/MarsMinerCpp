#include "Engine.hpp"

#include <cmath>

constexpr float AngleMargin = pi<float> / 12;

RobotBreaking Engine::Breaking() {
  if (-state.angle > -AngleMargin + pi<float> / 2 &&
      -state.angle < AngleMargin + pi<float> / 2)
    return RobotBreaking::Down;

  if (state.angle > -AngleMargin + pi<float> / 2 &&
      state.angle < AngleMargin + pi<float> / 2)
    return RobotBreaking::Up;

  if (state.angle < AngleMargin && state.angle > -AngleMargin)
    return RobotBreaking::Right;

  if (state.angle < AngleMargin + pi<float> && state.angle > -AngleMargin + pi<float>)
    return RobotBreaking::Left;

  return RobotBreaking::None;
}

VectorF Engine::Force() {
  VectorF force{};

  if (state.running) {
    force.x = std::cos(state.angle) * HorizontalForce();

    auto y = std::sin(state.angle);
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
    VectorI keyboardArrows{};
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
