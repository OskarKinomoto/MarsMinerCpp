#pragma once

#include "../Utils/Action.hpp"
#include "../Utils/OpenglVersion.hpp"
#include "../Utils/Vector2.hpp"
#include "../Controler/Keyboard.hpp"
#include "../Painter/Painter.hpp"

class SDL_OpenGL {
public:
    SDL_OpenGL(Painter p, OpenglVersion version, Size windowSize);
    void run();
    void stop();
    ~SDL_OpenGL();

    Size size();

    ActionArgs<Painter> PaintEvent;
    ActionArgs<float> PhysicsEvent;
    ActionArgs2<Keyboard::Key, Keyboard::State> KeyboardEvent;
    ActionArgs2<float, float> ResizeEvent;
    Painter painter;

    int FPS = 120;
    bool vsync = true;
    bool logFPS = false;

private:
    void *window;
    void *glContext;
    bool loop = true;

    void eventLoop();
};
