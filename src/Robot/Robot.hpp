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
public:
    enum class State {
        Move,
        Break,
    };
private:
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
    PositionF Center();
    VectorsF Verticies() const;
    VectorF BottomTile(const VectorsF &tiles);
    void SetMineralToRecieve(const Mineral *mineral);
    void SetCollisionTiles(std::vector<CollisionTile> &&tiles);
    bool IsBreaking();
    void SetState(State state);

public:
    Engine engine;
    Drill drill;
    Cargo cargo;
    Hull hull;

public:
    PositionF position{};
    VectorF velocity{};
    BreakingTile breakingTile{};
    RobotBreaking isBreaking = RobotBreaking::None;
    PossibleBreaking possibleBreaking{};
    std::vector<CollisionTile> collisionTiles;

public:
    const static SizeI size;

public:
    bool tileDestroy = false;
    bool newDestroy = false;

private:
    static float deepLogDt;
    static float margin;

private:
    float s = 0;
    const Mineral *mineral = nullptr;
    State state = State::Move;
    Sprite::Name sprite = Sprite::Name::RobotLeft;

    bool collisionTilesWasSet = false;

private:
    void TickMove(float dt);
    void TickBreak(float dt);
    void RecieveMineral();
    void StopMoving();
};

typedef const Robot& RobotC;
