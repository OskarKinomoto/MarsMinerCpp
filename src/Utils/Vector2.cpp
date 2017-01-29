#include "Vector2.hpp"

#include <cmath>

Vector2::Vector2(float x, float y) : x(x), y(y) {}

float Vector2::LenghtSquared() { return x * x + y * y; }

float Vector2::Lenght() {
  return static_cast<float>(std::pow(x * x + y * y, .5));
}

Vector2 operator+(Vector2 a, Vector2 b)
{
    return Vector2{a.x + b.x, a.y + b.y};
}
