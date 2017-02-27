#include "SDL_OpenGL.hpp"

#include <array>
#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include "../Utils/Exception.hpp"
#include "../Utils/Log.hpp"

namespace {

void CheckSDLError(std::string str) {
  std::string error = SDL_GetError();

  if (error != "") {
    SDL_ClearError();
    throw Exception(str + " – SDL Error: " + error + "\n");
  }
}

void SetOpenGLAttributes(int major, int minor) {
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

const size_t FPSCounterSize = 30;
std::array<unsigned int, FPSCounterSize> lastFrames;
size_t lastFrameItr = 0;

} /* namespace */

SDL_OpenGL::SDL_OpenGL(Painter p, OpenglVersion version, SizeI windowSize)
    : painter(p) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    throw Exception{"Failed to init SDL\n"};

  window = SDL_CreateWindow("MarsMiner", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, windowSize.width,
                            windowSize.height, SDL_WINDOW_OPENGL);

  if (!window)
    CheckSDLError("Unable to create window");

  glContext = SDL_GL_CreateContext(static_cast<SDL_Window*>(window));

  SetOpenGLAttributes(version.major, version.minor);
  SDL_GL_SetSwapInterval(vsync);

#ifndef __APPLE__
  glewExperimental = GL_TRUE;
  glewInit();
#endif

  LOGV(glGetString(GL_VENDOR) << " " << glGetString(GL_VERSION));
  LOGVV(glGetString(GL_RENDERER));
  LOGVVV(glGetString(GL_EXTENSIONS));

  p.Resize(windowSize.width, windowSize.height);

  SDL_GL_SwapWindow(static_cast<SDL_Window*>(window));
}

void SDL_OpenGL::run() {
  auto ticks = SDL_GetTicks();
  auto minimumFrameTime = 1000.0f / FPS;
  while (loop) {
    eventLoop();

    auto current_ticks = SDL_GetTicks();
    auto dt = current_ticks - ticks;

    if (PhysicsEvent)
      PhysicsEvent(dt / 1000.0f);

    if (PaintEvent)
      PaintEvent(painter);

    SDL_GL_SwapWindow(static_cast<SDL_Window*>(window));

    if (vsync) {
      auto delayms = static_cast<int>(minimumFrameTime - dt);
      if (delayms > 0)
        SDL_Delay(static_cast<unsigned int>(delayms));
    }

    ticks = current_ticks;
    lastFrames[lastFrameItr] = dt;

    lastFrameItr++;
    if (lastFrameItr >= FPSCounterSize) {
      lastFrameItr = 0;
      int time = 0;
      for (auto timeframe : lastFrames)
        time += timeframe;
      if (logFPS)
        LOGVVV("FPS: " << 1000.0f * FPSCounterSize / (time));
    }
  }
}

void SDL_OpenGL::stop() {
  loop = false;
}

SDL_OpenGL::~SDL_OpenGL() {
  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(static_cast<SDL_Window*>(window));
  SDL_Quit();
}

SizeI SDL_OpenGL::size()
{
    int w = 0;
    int h = 0;
    SDL_GetWindowSize(static_cast<SDL_Window*>(window), &w, &h);
    return {w, h};
}

namespace {
Keyboard::Key sdlKeyTo(SDL_Keycode sdlkey) {
  Keyboard::Key k = Keyboard::Key::None;

  switch (sdlkey) {
    case SDLK_ESCAPE:
      k = Keyboard::Key::Esc;
      break;
    case SDLK_DOWN:
      k = Keyboard::Key::Down;
      break;
    case SDLK_UP:
      k = Keyboard::Key::Up;
      break;
    case SDLK_LEFT:
      k = Keyboard::Key::Left;
      break;
    case SDLK_RIGHT:
      k = Keyboard::Key::Right;
      break;
    case SDLK_RETURN:
    case SDLK_RETURN2:
    case SDLK_KP_ENTER:
      k = Keyboard::Key::Enter;
      break;
    case SDLK_e:
      k = Keyboard::Key::E;
      break;
    default:
      break;
  }
  return k;
}
}

void SDL_OpenGL::eventLoop() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT)
      loop = false;

    if (event.type == SDL_KEYDOWN) {
      Keyboard::Key k = sdlKeyTo(event.key.keysym.sym);
      if (KeyboardEvent && k != Keyboard::Key::None)
        KeyboardEvent(k, Keyboard::State::Down);
    }

    if (event.type == SDL_KEYUP) {
      Keyboard::Key k = sdlKeyTo(event.key.keysym.sym);
      if (KeyboardEvent && k != Keyboard::Key::None)
        KeyboardEvent(k, Keyboard::State::Up);
    }
  }
}
