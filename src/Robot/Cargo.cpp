#include "Cargo.hpp"

#include "../Utils/Exception.hpp"

bool Cargo::Add(const Mineral *mineral)
{
    if (minerals.size() == max())
        return false;

    minerals.push_back(mineral);

    return true;
}

size_t Cargo::max()
{
    return max(model);
}

size_t Cargo::max(Cargo::Model m)
{
    switch (m) {
      case Model::Standard:
        return 100;
      case Model::StandardPlus:
        return static_cast<size_t>(max(Model::Standard) * 1.2f);
    }

    throw Exception{"Cargo max"};
}
