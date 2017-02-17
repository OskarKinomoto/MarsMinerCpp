#pragma once

#include "../Interfaces/PaintInterface.hpp"
#include "../Interfaces/TickInterface.hpp"

#include "../Utils/Vector2.hpp"

#include "../Objects/BreakingTile.hpp"
#include "../Objects/Mineral.hpp"

#include "Engine.hpp"
#include "Drill.hpp"
#include "Cargo.hpp"

class Robot : public PaintInterface, public TickInterface {
public:
    void Paint(Painter p, Camera c) override;
    void Tick(float dt) override;

public:
    float HeightInFeets();
    Vector2 Center();
    Vectors Verticies();
    Vector2 BottomTile(const Vectors &tiles);

public:
    Engine engine;
    Drill drill;
    Cargo cargo;

public:
    Vector2 position;
    Vector2 velocity;
    BreakingTile breakingTile;

public:
    const static Size size;

private:
    static float deepLogDt;
    static float margin;

private:
    float s = 0;
    Mineral mineral;

private:
    void TickMove(float dt);
    void TickBreak(float dt);
    void RecieveMineral();
};
