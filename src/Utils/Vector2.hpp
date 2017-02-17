#pragma once

#include <ostream>
#include <vector>

class Vector2 {
 public:
  union {
      struct {
        float x;
        float y;
      };
      struct {
        float width;
        float height;
      };
  };

  Vector2(float x = 0, float y = 0);

  float LenghtSquared();
  float Lenght();
  float Angle();

  Vector2 &operator+=(Vector2 v);
};

Vector2 operator+(Vector2 a, Vector2 b);
Vector2 operator-(Vector2 a, Vector2 b);
Vector2 operator*(Vector2 v, float s);
Vector2 operator/(Vector2 v, float s);
Vector2 operator/(float s, Vector2 v);

std::ostream& operator<<(std::ostream& stream, const Vector2& v);

typedef Vector2 Position;
typedef Vector2 Size;

typedef std::vector<Vector2> Vectors;
