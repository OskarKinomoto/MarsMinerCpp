#include "Layer.hpp"

const Layer Layer::Background{-9};
const Layer Layer::Clouds{-8};
const Layer Layer::Grass{-8};
const Layer Layer::Tiles{-7};
const Layer Layer::Minerals{-5};
const Layer Layer::Buildings{-3};
const Layer Layer::Robot{0};
const Layer Layer::Window{4};

const Layer Layer::operator++(int) const
{
    return {z + 0.01f};
}

Layer::operator float()
{
    return z;
}

Layer::Layer(float layer) : z(layer)
{

}
