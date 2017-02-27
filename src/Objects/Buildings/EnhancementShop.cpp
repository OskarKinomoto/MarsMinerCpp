#include "EnhancementShop.hpp"

EnhancementShop::EnhancementShop(Robot& r)
    : BuildingBase("Enhancment Shop",
                   4,
                   2,
                   Sprite::Name::EnhancementShop,
                   -11,
                   r) {}
