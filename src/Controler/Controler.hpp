#pragma once

#include "Keyboard.hpp"
#include "../Painter/Painter.hpp"
#include "../Painter/Camera.hpp"

#include "../Interfaces/PaintInterface.hpp"
#include "../Interfaces/TickInterface.hpp"
#include "../Interfaces/LoadInterface.hpp"

#include "../Objects/Model.hpp"
#include "../Objects/Background.hpp"

class Controler : public PaintInterface, public TickInterface, public LoadInterface {
public:
    Controler(Action stop, Camera c);
    ~Controler();

    void Tick(float dt) override;
    void Paint(Painter p, Camera c) override;
    void Load() override;

    Keyboard keyboard;
    Camera c;
private:
    enum class State {
        MainMenu,
                    Loaded,
                    InGame,
                    InBuilding,
                    InGameMenu,
                    GameOver,
                    Closing
    };

    State state = State::MainMenu;

    Model m;
    Background background;
};
