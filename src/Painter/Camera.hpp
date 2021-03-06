#pragma once

#include "../Utils/Vector2.hpp"

class CameraBase {
public:
    PositionF position;

public:
    virtual void SetPosition(PositionF position, int min, int max) = 0;
    virtual void Begin() = 0;
    virtual void Translate() = 0;
    virtual void TranslateBack() = 0;
    virtual ~CameraBase() = default;
};

typedef CameraBase& Camera;
