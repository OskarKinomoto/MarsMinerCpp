#pragma once

#include "Robot.hpp"

class Physics {
public:
    static float DragConst;
    static float FrictionConst;
    static float GravityConst;
    static float HeightConst;

public:
    static VectorF Forces(const Robot& robot);

private:
    static VectorF Gravity();
    static VectorF DragForce(VectorF velocity);
    static VectorF HightForce(float height);
    static VectorF FrictionForce(bool engine, VectorF velocity);
};
