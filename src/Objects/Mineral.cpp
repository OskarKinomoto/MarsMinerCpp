#include "Mineral.hpp"

const Mineral Mineral::None{};
const Mineral Mineral::Gold{};

Sprite::Name Mineral::GetSprite()
{
    return sprite;
}

Mineral Mineral::RandomByDepth(int /*TileDepth*/)
{
    return Gold;
}
