#include "Shop.hpp"

Shop::Shop(Robot &r): BuildingBase("Marketplace",
                                   4,
                                   2,
                                   Sprite::Name::Shop,
                                   3,
                                   r) {}
