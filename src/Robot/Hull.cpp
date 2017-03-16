#include "Hull.hpp"

#include "../Utils/Utils.hpp"

void Hull::Hit(float velocityBegin, float velocityEnd) {
  auto diff = velocityBegin - velocityEnd - Endurance();

  if (diff > 0)
    LooseLife(diff * HitMultiply());
}

void Hull::LooseLife(float lifeAmount) {
  // TODO dev mode

  current -= lifeAmount;

  LOGV("Hull: " << current << "/" << Max());

  if (current <= 0) {
    throw GameOverException{GameOverException::Type::Life};
  }
}

float Hull::Max() {
  return Max(model);
}

float Hull::Endurance() {
  return Endurance(model);
}

float Hull::HitMultiply() {
  return HitMultiply(model);
}

float Hull::Max(Hull::Model m) {
  switch (m) {
    case Model::Standard:
      return 500;
    case Model::StandardPlus:
      return Max(Model::Standard) * 1.2f;
  }

  throw Exception{"Hull Max"};
}

float Hull::Endurance(Hull::Model m) {
  switch (m) {
    case Model::Standard:
      return 150;
    case Model::StandardPlus:
      return Endurance(Model::Standard) * 1.2f;
  }

  throw Exception{"Hull Endurance"};
}

float Hull::HitMultiply(Hull::Model m) {
  switch (m) {
    case Model::Standard:
      return 1;
    case Model::StandardPlus:
      return HitMultiply(Model::Standard) / 0.9f;
  }

  throw Exception{"Hull HitMultiply"};
}
