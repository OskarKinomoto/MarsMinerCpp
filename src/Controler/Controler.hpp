#pragma once

#include "Keyboard.hpp"

#include "../Interfaces/LoadInterface.hpp"
#include "../Interfaces/PaintInterface.hpp"
#include "../Interfaces/TickInterface.hpp"

#include "../Objects/Background.hpp"
#include "../Objects/Buildings/Buildings.hpp"
#include "../Objects/Clouds.hpp"
#include "../Objects/Grass.hpp"
#include "../Objects/Model.hpp"

#include "../Painter/Camera.hpp"
#include "../Painter/Painter.hpp"


#include "../FreeType/FreeType.hpp"
#include "../Window/Surface.hpp"

class Controler : public PaintInterface, public TickInterface, public LoadInterface {
public:
    Controler(Action stop, Camera c, SizeUI size);
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

    Background background{};
    Clouds clouds{};
    Grass grass{};
    Buildings buildings;

private:
    FreeType freeType{};
    Surface surface;
};
