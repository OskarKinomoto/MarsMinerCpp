#pragma once

#include <vector>

#include "../Objects/Mineral.hpp"

class Cargo {
public:
    enum class Model {
        Standard,
        StandardPlus,
    };

public:
    Model model = Model::Standard;

    std::vector<const Mineral*> minerals;

public:
    bool Add(const Mineral *mineral);

public:
    size_t max();

public:
    static size_t max(Model m);
};
