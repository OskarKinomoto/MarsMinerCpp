#include "Vector2.hpp"

#include <cmath>

template class Vector<int>;
template class Vector<float>;
template class Vector<double>;

template <typename T>
float Vector<T>::LenghtSquared() {
  return x * x + y * y;
}

template <typename T>
float Vector<T>::Lenght() {
  return std::sqrt(x * x + y * y);
}

template <typename T>
float Vector<T>::Angle() {
  return std::atan2(y, x);
}

template <typename T>
Vector<T>& Vector<T>::operator+=(Vector<T> v) {
  x += v.x;
  y += v.y;

  return *this;
}

template<typename T>
Vector<T> Vector<T>::Reverse() const
{
    return {1.0f / x, 1.0f / y};
}

template <typename T>
Vector<T> Vector<T>::operator+(Vector<T> b)  const{
  return {x + b.x, y + b.y};
}

template <typename T>
Vector<T> Vector<T>::operator-(Vector<T> b)  const{
  return {x - b.x, y - b.y};
}

template <typename T>
Vector<T> Vector<T>::operator*(unsigned int s)  const{
  return {x * s, y * s};
}

template <typename T>
Vector<T> Vector<T>::operator*(int s)  const{
  return {x * s, y * s};
}

template <typename T>
Vector<T> Vector<T>::operator*(float s)  const{
  return {x * s, y * s};
}

template <typename T>
Vector<T> Vector<T>::operator*(double s) const {
  return {x * s, y * s};
}

template <typename T>
Vector<T> Vector<T>::operator/(unsigned int s) const {
  return {x * static_cast<float>(s), y / static_cast<float>(s)};
}

template <typename T>
Vector<T> Vector<T>::operator/(int s) const {
  return {x / static_cast<float>(s), y / static_cast<float>(s)};
}

template <typename T>
Vector<T> Vector<T>::operator/(float s) const {
  return {x / s, y / s};
}

template <typename T>
Vector<T> Vector<T>::operator/(double s) const {
  return {x / s, y / s};
}

template<typename T, typename U>
Vector<U> operator/(T s, Vector<U> v)
{
    return {s / v.x, s / v.y};
}

Vector<float> operator+(const Vector<float> &a, const Vector<int> &b)
{
    return {a.x + b.x, a.y + b.y};
}
