#pragma once

#include <ostream>
#include <vector>

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

  template<typename U, typename V>
  Vector(U x,V y) : x(x), y(y) {}
  /*
  explicit Vector(const Vector<int> &v);
  explicit Vector(const Vector<float> &v);
  explicit Vector(const Vector<double> &v);
*/
  float LenghtSquared();
  float Lenght();
  float Angle();

  Vector<T> &operator+=(Vector<T> v);

  template<typename U>
  Vector<T> &operator=(Vector<U> v) {
    x = v.x;
    y = v.y;
    return *this;
  }

  Vector<T> Reverse() const;

public:
  Vector<T> operator+(Vector<T> b) const;
  Vector<T> operator-(Vector<T> b) const;

  Vector<T> operator*(unsigned int s) const;
  Vector<T> operator*(int s) const;
  Vector<T> operator*(float s) const;
  Vector<T> operator*(double s) const;

  Vector<T> operator/(unsigned int s) const;
  Vector<T> operator/(int s) const;
  Vector<T> operator/(float s) const;
  Vector<T> operator/(double s) const;
};

Vector<float> operator+(const Vector<float> &a, const Vector<int> &b);


template <typename T, typename U>
Vector<U> operator/(T s, Vector<U> v);

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Vector<T>& v) {
    stream << "(" << v.x << "," << v.y << ")";
    return stream;
}

template <typename T> using Position = Vector<T>;
template <typename T> using Size = Vector<T>;

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
