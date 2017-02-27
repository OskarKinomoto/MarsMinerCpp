#pragma once

#include "Enums.hpp"

#include "../Utils/Utils.hpp"

class Engine {
public:
    enum class Model {
        Standard,
        StandardPlus,
    };

    struct State {
        bool running;
        float angle;

        State(bool running = false, float angle = 0) : running(running), angle(angle) {}
    };

    State state;
    Model model = Model::Standard;

    RobotBreaking Breaking();
    VectorF Force();

    float UpForce();
    float DownForce();
    float HorizontalForce();

    void SetFromKeyboard(bool left, bool right, bool up, bool down);

public:
    static float UpForce(Model m);
    static float DownForce(Model m);
    static float HorizontalForce(Model m);

};
