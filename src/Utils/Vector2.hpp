#pragma once

#include <ostream>
#include <vector>
#include <cmath>

template <typename T>
class Vector {
 public:
  union {
    struct {
      T x;
      T y;
    };
    struct {
      T width;
      T height;
    };
  };

  Vector() : x(0), y(0) {}

  template <typename U, typename V>
  Vector(U x, V y) : x(x), y(y) {}

  float LenghtSquared() const { return x * x + y * y; }

  float Lenght() const { return std::sqrt(x * x + y * y); }

  float Angle() const { return std::atan2(y, x); }

  T Area() const { return x * y; }

  Vector<T>& operator+=(Vector<T> v) {
    x += v.x;
    y += v.y;
    return *this;
  }

  template <typename U>
  Vector<T>& operator=(Vector<U> v) {
    x = v.x;
    y = v.y;
    return *this;
  }

  Vector<T> Reverse() const { return {1.0f / x, 1.0f / y}; }

 public:
  Vector<T> operator+(Vector<T> b) const { return {x + b.x, y + b.y}; }
  Vector<T> operator-(Vector<T> b) const { return {x - b.x, y - b.y}; }

  template <typename U>
  Vector<T> operator*(U s) const {
    return {x * s, y * s};
  }

  template <typename U>
  Vector<T> operator/(U s) const {
    return {x / s, y / s};
  }
};

Vector<float> operator+(const Vector<float>& a, const Vector<int>& b);

Vector<float> operator+(const Vector<float>& a, const Vector<uint>& b);

template <typename T, typename U>
Vector<U> operator/(T s, Vector<U> v) {
  return {s / v.x, s / v.y};
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Vector<T>& v) {
  stream << "(" << v.x << "," << v.y << ")";
  return stream;
}

template <typename T>
using Position = Vector<T>;
template <typename T>
using Size = Vector<T>;

typedef Size<uint> SizeUI;
typedef Size<int> SizeI;
typedef Size<float> SizeF;
typedef Size<double> SizeD;

typedef Vector<int> VectorI;
typedef Vector<float> VectorF;
typedef Vector<double> VectorD;

typedef Position<int> PositionI;
typedef Position<float> PositionF;
typedef Position<double> PositionD;

typedef std::vector<Vector<float>> VectorsF;
