#pragma once

#include "../Interfaces/PaintInterface.hpp"\

class Grass : public PaintInterface{
public:
    void Paint(Painter p, Camera c) override;

private:
    constexpr static int GrassTiles = 14;
    const static SizeI size;
};
