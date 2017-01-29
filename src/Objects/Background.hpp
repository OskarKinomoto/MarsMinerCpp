#pragma once

#include "../Interfaces/PaintInterface.hpp"

class Background : public PaintInterface {
public:
    void Paint(Painter p, Camera) override;
};
