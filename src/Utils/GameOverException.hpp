#pragma once

#include "Exception.hpp"

class GameOverException {
public:
enum class Type {
    Fuel,
    Life,
};

GameOverException(Type type);

Type type;
};
