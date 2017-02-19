#pragma once

#include "../Interfaces/TickInterface.hpp"

class Drill  : public  TickInterface{
public:
    enum class Model {
        Standard,
        StandardPlus,
    };

    Model model = Model::Standard;

public:
    void Tick(float dt) override;

public:
    void Heated();

public:
    float DrillingSpeed();
    float CoolingTime();
    bool Cooled();

public:
    static float DrillingSpeed(Model m);
    static float CoolingTime(Model m);

public:
    static float MoveToHeatDrillSquared;

private:
    float cooling = 0;

};
