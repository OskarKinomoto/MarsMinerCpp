#include <iostream>
#include <random>
#include <ctime>

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
  std::srand(std::time(0));

  SizeI beginSize{1280,720};

  PainterGL2 painter{};
  SDL_OpenGL sdl{painter, {2, 1}, beginSize};
  CameraGL2 camera{[&](){return sdl.size();}};
  Controler c([&](){sdl.stop();}, camera, {beginSize.x, beginSize.y});
  painter.SetUp();

  c.Load();

  sdl.KeyboardEvent = [&](auto k, auto s) { c.keyboard.Update(k, s); };
  sdl.PaintEvent = [&](auto& p){c.Paint(p, camera);};
  sdl.PhysicsEvent = [&](auto dt){c.Tick(dt);};
  sdl.run();

  return 0;
}
