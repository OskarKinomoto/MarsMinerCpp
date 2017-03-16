#pragma once

class Color {
public:
    float r;
    float g;
    float b;
    float a;

    Color() = default;
    Color(float r, float g, float b, float a = 1);
    Color(int r, int g, int b, int a = 255);

    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color White;
    static const Color Transparent;
};
