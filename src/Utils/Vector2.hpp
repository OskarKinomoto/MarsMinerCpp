#pragma once

class Vector2 {
public:
    float x = 0;
    float y = 0;

    Vector2() = default;
    Vector2(float x, float y);

    float LenghtSquared();
    float Lenght();
};


Vector2 operator+(Vector2 a, Vector2 b);

typedef Vector2 Position;
typedef Vector2 Size;
