#pragma once

#include "../Interfaces/PaintInterface.hpp"
#include "../Interfaces/TickInterface.hpp"
#include "../Painter/Texture.hpp"

class Clouds : public PaintInterface, public TickInterface {
public:
    Clouds();

private:
    constexpr static float WindConstL1 = 70;
    constexpr static float WindConstL2 = 40;

    Texture tex1;
    Texture tex2;

    PositionF pos1;
    PositionF pos2;

public:
    void Tick(float dt) override;
    void Paint(Painter p, Camera c) override;
};
