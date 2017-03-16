#include "Physics.hpp"

#include <cmath>

#define SIGN(x) ((x < 0) ? -1 : 1)
#define ABS(x) ((x < 0) ? (-x) : (x))

float Physics::DragConst = 8e-4f;
float Physics::FrictionConst = 65e-2f;
float Physics::GravityConst = -80.f;
float Physics::HeightConst = 2e-2f;

VectorF Physics::Forces(const Robot& robot) {
  return Gravity() + DragForce(robot.velocity) + HightForce(robot.position.x) +
         FrictionForce(robot.engine.state.running, robot.velocity);
}

VectorF Physics::Gravity() {
  return {0, GravityConst};
}

VectorF Physics::DragForce(VectorF velocity) {
  return {-velocity.x * ABS(velocity.x) * DragConst,
          -velocity.y * ABS(velocity.y) * DragConst};
}

VectorF Physics::HightForce(float height) {
  return {0, (height <= 0 ? 0 : -height * HeightConst)};
}

VectorF Physics::FrictionForce(bool engine, VectorF velocity) {
  VectorF ret{};

  if (isZero(velocity.y) && !isZero(velocity.x)) {
    ret.x = -velocity.x * FrictionConst;

    if (!engine) {
      ret.x += -10 * SIGN(velocity.x) * std::pow(ABS(velocity.x), 1.0f / 3) *
               FrictionConst * 3;
    }
  }

  return ret;
}
