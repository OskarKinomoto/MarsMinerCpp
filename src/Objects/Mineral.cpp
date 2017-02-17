#include "Mineral.hpp"

const Mineral Mineral::None{};
const Mineral Mineral::Gold{Sprite::Name::TileGold};

Sprite::Name Mineral::GetSprite()
{
    return sprite;
}

Mineral Mineral::RandomByDepth(int /*TileDepth*/)
{
    return Gold;
}

Mineral::Mineral() : notNull(false)
{

}

Mineral::Mineral(Sprite::Name sprite) : notNull(true), sprite(sprite)
{

}
