#pragma once

#include "../Interfaces/PaintInterface.hpp"\

class Grass : public PaintInterface{
public:
    void Paint(Painter p, Camera c) override;

private:
    constexpr static int GrassTiles = 7;
    const static Vector2 size;
};
