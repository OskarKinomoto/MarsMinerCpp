#pragma once

#include "../Utils/Action.hpp"
#include "../Controler/Keyboard.hpp"
#include "../Painter/Painter.hpp"


class SDL_OpenGL {
public:
    SDL_OpenGL(Painter p, int major, int minor);
    void run();
    void stop();
    ~SDL_OpenGL();

    ActionArgs<Painter> PaintEvent;
    ActionArgs<float> PhysicsEvent;
    ActionArgs2<Keyboard::Key, Keyboard::State> KeyboardEvent;
    ActionArgs2<float, float> ResizeEvent;
    Painter painter;
    int FPS = 60;

private:
    void *window;
    void *glContext;
    bool loop = true;

    void eventLoop();
};
