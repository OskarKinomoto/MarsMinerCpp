#pragma once

#include "KObject.hpp"

class Surface : public KObject{
public:
    Surface(SizeUI size);

    // PaintInterface interface
public:
    void Paint(Painter p, Camera c) override;

    // MouseInterface interface
public:
    bool MouseEvent(Mouse m) override;
};
