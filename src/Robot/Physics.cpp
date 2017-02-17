#include "Physics.hpp"

#define ABS(x) ((x < 0) ? (-x) : (x))

float Physics::DragConst = 8e-4f;
float Physics::FrictionConst = 65e-2f;
float Physics::GravityConst = -80.f;
float Physics::HeightConst = 2e-2f;

Vector2 Physics::Forces(const Robot &robot)
{
    return /*Gravity() +*/ DragForce(robot.velocity);
}

Vector2 Physics::Gravity()
{
    return {0, GravityConst};
}

Vector2 Physics::DragForce(Vector2 velocity)
{
    return {
        -velocity.x * ABS(velocity.x) * DragConst,
        -velocity.y * ABS(velocity.y) * DragConst
    };
}
