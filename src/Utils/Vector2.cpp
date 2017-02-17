#include "Vector2.hpp"

#include <cmath>

Vector2::Vector2(float x, float y) : x(x), y(y) {}

float Vector2::LenghtSquared() {
  return x * x + y * y;
}

float Vector2::Lenght() {
    return static_cast<float>(std::sqrt(x * x + y * y));
}

float Vector2::Angle()
{
    return std::atan2(y, x);
}

Vector2 &Vector2::operator+=(Vector2 v)
{
  x += v.x;
  y += v.y;
  return *this;
}

Vector2 operator+(Vector2 a, Vector2 b) {
  return {a.x + b.x, a.y + b.y};
}

Vector2 operator-(Vector2 a, Vector2 b) {
  return {a.x - b.x, a.y - b.y};
}

Vector2 operator*(Vector2 v, float s) {
  return {v.x * s, v.y * s};
}

Vector2 operator/(Vector2 v, float s) {
  return {v.x / s, v.y / s};
}

Vector2 operator/(float s, Vector2 v)
{
    return {s / v.x, s / v.y};
}

std::ostream &operator<<(std::ostream &stream, const Vector2 &v)
{
    stream << "(" << v.x << "," << v.y << ")";
    return stream;
}
