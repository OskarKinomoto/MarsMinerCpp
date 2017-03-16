#include "Buildings.hpp"

#include "../Model.hpp"

Buildings::Buildings(Robot& r) {
  Load(r);
}

void Buildings::Load(Robot& r) {
  buildings.push_back(EnhancementShop(r));
  buildings.push_back(GasStation(r));
  buildings.push_back(RepairShop(r));
  buildings.push_back(Shop(r));
}

void Buildings::SetStones(Tiles &tiles)
{
    for (auto& b : buildings) {
      auto left = b.Left() / Tile::Size - Model::LeftX;
      auto right = b.Right()/ Tile::Size - Model::LeftX;
      for (; left < right; left++) {
          tiles.at(left, 0)->SetRock();
      }
    }
}

void Buildings::Paint(Painter p, Camera c) {
  for (auto& b : buildings) {
    b.Paint(p, c);
  }
}
