#include "Controler.hpp"

Controler::Controler(Action stop, Camera c, SizeUI size) : c(c), buildings(m.robot), surface(size) {
  keyboard.SetEvent(Keyboard::Key::Esc, stop);
}

Controler::~Controler() {}

void Controler::Tick(float dt) {
  if (dt > 0.2f)
      dt = 0.2f;

  m.robot.engine.SetFromKeyboard(
      keyboard.Down(Keyboard::Key::Left), keyboard.Down(Keyboard::Key::Right),
      keyboard.Down(Keyboard::Key::Up), keyboard.Down(Keyboard::Key::Down));

  clouds.Tick(dt);
  m.Tick(dt);

  c.SetPosition(m.robot.position, Model::LeftTile, Model::RightTile);
}

void Controler::Paint(Painter p, Camera c) {
  p.CleanView();
  c.Begin();

  c.TranslateBack();

  background.Paint(p, c);
  clouds    .Paint(p, c);
  grass     .Paint(p, c);
  m.tiles   .Paint(p, c);
  buildings .Paint(p, c);
  m.robot   .Paint(p, c);
  surface   .Paint(p, c);
}

void Controler::Load() {
  Sprite::Load();
  freeType.Load();
}
