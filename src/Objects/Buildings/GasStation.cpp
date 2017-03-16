#include "GasStation.hpp"

GasStation::GasStation(Robot& r)
    : BuildingBase("Gas station",
                   3,
                   2,
                   Sprite::Name::BuildingGasStation,
                   -4,
                   r) {}
