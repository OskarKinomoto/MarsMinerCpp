#include "Drill.hpp"

#include "../Utils/Exception.hpp"

void Drill::Tick(float dt)
{
    cooling -= dt;

    if(cooling < 0)
        cooling = 0;
}

void Drill::Heated()
{
    cooling = CoolingTime();
}

float Drill::DrillingSpeed()
{
    return DrillingSpeed(model);
}

float Drill::CoolingTime()
{
    return CoolingTime(model);
}

float Drill::DrillingSpeed(Drill::Model m)
{
    switch (m) {
      case Model::Standard:
        return 100;
      case Model::StandardPlus:
        return DrillingSpeed(Model::Standard) * 1.2f;
    }

    throw Exception{"Drill DrillingSpeed"};
}

float Drill::CoolingTime(Drill::Model m)
{
    switch (m) {
      case Model::Standard:
        return .3f;
      case Model::StandardPlus:
        return CoolingTime(Model::Standard) / 1.2f;
    }

    throw Exception{"Drill CoolingTime"};
}
