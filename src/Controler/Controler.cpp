#include "Controler.hpp"

Controler::Controler(Action stop, Camera c) : c(c), buildings(m.robot)
{
    keyboard.SetEvent(Keyboard::Key::Esc, stop);
}

Controler::~Controler()
{

}

void Controler::Tick(float dt)
{
    m.robot.engine.SetFromKeyboard(keyboard.Down(Keyboard::Key::Left),
                                   keyboard.Down(Keyboard::Key::Right),
                                   keyboard.Down(Keyboard::Key::Up),
                                   keyboard.Down(Keyboard::Key::Down));

    clouds.Tick(dt);
    m.Tick(dt);

    c.SetPosition(m.robot.position, Model::LeftTile, Model::RightTile);
}

void Controler::Paint(Painter p, Camera c)
{
    p.CleanView();
    c.Begin();

    c.TranslateBack();

    background.Paint(p, c);
    clouds.Paint(p, c);
    grass.Paint(p, c);
    m.tiles.Paint(p,c);
    buildings.Paint(p,c);
    m.robot.Paint(p,c);
    // window
}


void Controler::Load()
{
    Sprite::Load();
}
