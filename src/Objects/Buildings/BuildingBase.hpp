#pragma once

#include <string>

#include "../../Interfaces/PaintInterface.hpp"
#include "../../Robot/Robot.hpp"
#include "../../Utils/Utils.hpp"

class BuildingBase : public PaintInterface {
protected:
    BuildingBase(StringC name, int texWidth, int texHeight, Sprite::Name sprite, int leftPos, Robot& r);

public:
   // ? Action onClose;

    float Left();
    float Right();

protected:
    bool CanEnter();

protected:
    int texWidth;
    int texHeight;
    Sprite::Name sprite;

    int LeftXPosition;
    int RightXPosition;

    Robot &robot;

    // TODO Window window;

    // PaintInterface interface
public:
    void Paint(Painter p, Camera c) override;
};
