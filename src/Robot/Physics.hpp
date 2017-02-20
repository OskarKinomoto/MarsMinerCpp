#pragma once

#include "Robot.hpp"

class Physics {
public:
    static float DragConst;
    static float FrictionConst;
    static float GravityConst;
    static float HeightConst;

public:
    static Vector2 Forces(const Robot& robot);

private:
    static Vector2 Gravity();
    static Vector2 DragForce(Vector2 velocity);
    static Vector2 HightForce(float height);
    static Vector2 FrictionForce(bool engine, Vector2 velocity);
};
