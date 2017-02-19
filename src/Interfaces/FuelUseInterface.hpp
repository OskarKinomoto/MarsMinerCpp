#pragma once

#include "../Robot/Fuel.hpp"

class FuelUseInterface {
public:
    virtual void UseFuel(Fuel &fuel, float dt) = 0;
    virtual ~FuelUseInterface() = default;
};
