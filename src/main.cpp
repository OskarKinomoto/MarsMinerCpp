#include <iostream>

#include <SDL2/SDL.h>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include <GL/gl.h>
#include <GL/glext.h>

#include "SDL/SDL_OpenGL.hpp"
#include "Controler/Controler.hpp"
#include "Painter/PainterGL2.hpp"
#include "Painter/CameraGL2.hpp"
#include "Painter/Texture.hpp"

using namespace std;

int main() {
  PainterGL2 painter{};
  SDL_OpenGL sdl{painter, 2, 1};
  CameraGL2 camera;
  Controler c([&](){sdl.stop();}, camera);
  painter.SetUp();

  c.Load();

  sdl.KeyboardEvent = [&](auto k, auto s) { c.keyboard.Update(k, s); };
  sdl.PaintEvent = [&](auto& p){c.Paint(p, camera);};
  sdl.run();

  return 0;
}
