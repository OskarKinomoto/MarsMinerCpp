#pragma once

class Color {
public:
    float r;
    float g;
    float b;

    Color() = default;
    Color(float r, float g, float b);
    Color(int r, int g, int b);

    static const Color Red;
    static const Color Green;
    static const Color Blue;
};
