#include "Buildings.hpp"

Buildings::Buildings(Robot& r) {
  Load(r);
}

void Buildings::Load(Robot& r) {
  buildings.push_back(EnhancementShop(r));
  buildings.push_back(GasStation(r));
  buildings.push_back(RepairShop(r));
  buildings.push_back(Shop(r));
}

void Buildings::Paint(Painter p, Camera c) {
  for (auto& b : buildings) {
    b.Paint(p, c);
  }
}
