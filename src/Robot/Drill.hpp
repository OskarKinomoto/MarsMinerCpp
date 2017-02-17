#pragma once

#include "../Interfaces/TickInterface.hpp"

class Drill  : public  TickInterface{
public:
    enum class Model {
        Standard,
        StandardPlus,
    };

    Model model;

public:
    void Tick(float dt) override;

public:
    void Heated();

public:
    float DrillingSpeed();
    float CoolingTime();

public:
    static float DrillingSpeed(Model m);
    static float CoolingTime(Model m);

private:
    float cooling = 0;

};
