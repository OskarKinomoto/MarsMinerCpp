#pragma once

#include "../Painter/Painter.hpp"
#include "../Painter/Camera.hpp"

class PaintInterface {
public:
    virtual void Paint(Painter p, Camera c) = 0;
    virtual ~PaintInterface() = default;
};
