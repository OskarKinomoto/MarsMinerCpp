#include "Layer.hpp"

const Layer Layer::Background{-9};
const Layer Layer::CloudsLow{-8.1f};
const Layer Layer::Clouds{-8};
const Layer Layer::Grass{-8};
const Layer Layer::Tiles{-7};
const Layer Layer::Minerals{-5};
const Layer Layer::Buildings{-3};
const Layer Layer::Robot{0};
const Layer Layer::Surface{4};
const Layer Layer::Text{8};

const Layer Layer::operator++(int)const {
  return {z + 0.01f};
}

const Layer Layer::operator+(float s) const {
  return {z + s};
}

Layer::operator float() {
  return z;
}

Layer::Layer(float layer) : z(layer) {}
