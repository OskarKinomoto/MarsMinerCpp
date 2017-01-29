#include "Controler.hpp"

Controler::Controler(Action stop, Camera c) : c(c)
{
    keyboard.SetEvent(Keyboard::Key::Esc, stop);
}

Controler::~Controler()
{

}

void Controler::Tick(float)
{

}

void Controler::Paint(Painter p, Camera c)
{
    p.CleanView();

    background.Paint(p, c);
    // clouds
    // grass
    m.tiles.Paint(p,c);
    // buildings
    // robot
    // window
}


void Controler::Load()
{
    Sprite::Load();
}
