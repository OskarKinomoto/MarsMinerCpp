#include "Color.hpp"

const Color Color::Red(255, 0, 0);
const Color Color::Blue(0, 0, 255);
const Color Color::Green(0, 255, 0);


Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

Color::Color(int r, int g, int b) : Color(r / 255.f, g / 255.f, b / 255.f) {}
