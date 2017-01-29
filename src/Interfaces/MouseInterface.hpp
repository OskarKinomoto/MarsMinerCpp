#pragma once

#include "../Controler/Mouse.hpp"

class MouseInterface {
public:
    virtual bool MouseEvent(Mouse m) = 0;
    virtual ~MouseInterface() = default;
};
