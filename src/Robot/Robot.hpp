#pragma once

#include "../Interfaces/PaintInterface.hpp"
#include "../Interfaces/TickInterface.hpp"

#include "../Utils/Vector2.hpp"

#include "../Objects/BreakingTile.hpp"
#include "../Objects/Mineral.hpp"
#include "../Objects/CollisionTile.hpp"

#include "Engine.hpp"
#include "Drill.hpp"
#include "Cargo.hpp"
#include "Hull.hpp"

#include "Enums.hpp"

class Robot : public PaintInterface, public TickInterface {
private:
    enum class State {
        Move,
        Break,
    };

    class PossibleBreaking {
    public:
        bool LeftRight = false;
        bool Down = false;
        RobotBreaking breaking = RobotBreaking::None;

        bool IsDown();
        bool IsLeft();
        bool IsRight();
        void All(bool value);
    };

public:
    void Paint(Painter p, Camera c) override;
    void Tick(float dt) override;

public:
    float HeightInFeets();
    Vector2 Center();
    Vectors Verticies() const;
    Vector2 BottomTile(const Vectors &tiles);
    void SetCollisionTiles(std::vector<CollisionTile> &&tiles);

public:
    Engine engine;
    Drill drill;
    Cargo cargo;
    Hull hull;

public:
    Vector2 position{};
    Vector2 velocity{};
    BreakingTile breakingTile{};
    RobotBreaking isBreaking = RobotBreaking::None;
    PossibleBreaking possibleBreaking{};
    std::vector<CollisionTile> collisionTiles;

public:
    const static Size size;

private:
    static float deepLogDt;
    static float margin;

private:
    float s = 0;
    Mineral mineral{};
    State state = State::Move;
    Sprite::Name sprite = Sprite::Name::RobotLeft;

    bool collisionTilesWasSet = false;

private:
    void TickMove(float dt);
    void TickBreak(float dt);
    void RecieveMineral();
    void SetState(State state);
    void StopMoving();
};
