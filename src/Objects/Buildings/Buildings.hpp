#pragma once

#include <vector>

#include "BuildingBase.hpp"
#include "GasStation.hpp"
#include "Shop.hpp"
#include "RepairShop.hpp"
#include "EnhancementShop.hpp"

#include "../Tiles.hpp"

class Buildings : public PaintInterface {
public:
    std::vector<BuildingBase> buildings;

    Buildings(Robot &r);

    void Load(Robot &r);

    void SetStones(Tiles &tiles);

    // PaintInterface interface
public:
    void Paint(Painter p, Camera c) override;
};
