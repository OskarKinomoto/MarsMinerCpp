#include "Vector2.hpp"

Vector<float> operator+(const Vector<float>& a, const Vector<int>& b) {
  return {a.x + b.x, a.y + b.y};
}

Vector<float> operator+(const Vector<float>& a, const Vector<uint>& b) {
  return {a.x + b.x, a.y + b.y};
}
