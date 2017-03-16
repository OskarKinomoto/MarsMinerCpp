#include "RepairShop.hpp"

RepairShop::RepairShop(Robot& r)
    : BuildingBase("Repair shop", 3, 2, Sprite::Name::RepairShop, 11, r) {}
