#include "Mineral.hpp"

#include <random>

std::vector<Mineral*> Mineral::list{};

const Mineral Mineral::None{};
const Mineral Mineral::Gold{Sprite::Name::TileGold, 20};
const Mineral Mineral::Lapis{Sprite::Name::TileLapis, 10};
const Mineral Mineral::Silver{Sprite::Name::TileSilver, 15};
const Mineral Mineral::Platinium{Sprite::Name::TilePlatinium, 40};
const Mineral Mineral::Rubin{Sprite::Name::TileRubin, 35};
const Mineral Mineral::Copper{Sprite::Name::TileCopper, 7};
const Mineral Mineral::Saphire{Sprite::Name::TileSaphire, 12};
const Mineral Mineral::Salt{Sprite::Name::TileSalt, 3};
const Mineral Mineral::Emerald{Sprite::Name::TileEmerald, 17};
const Mineral Mineral::Fe{Sprite::Name::TileFe, 9};

Sprite::Name Mineral::GetSprite() const {
  return sprite;
}

Mineral* Mineral::RandomByDepth(int /*TileDepth*/) {
  return list.at(static_cast<uint>(std::rand()) % list.size());
}

Mineral::Mineral() : notNull(false), sprite(Sprite::Name::None), price(0) {}

Mineral::Mineral(Sprite::Name sprite, int price)
    : notNull(true), sprite(sprite), price(price) {
  list.push_back(this);
}
