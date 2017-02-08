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
/*
    p.BeginQuads();
    p.Color(Color::Red);
    p.Square(Position{0,0}, Size{-300,50}, Layer::Robot);
    p.Color(Color::Blue);
    p.Square(Position{-300,50}, Size{-300,50}, Layer::Robot);
    p.EndQuads();*/
}


void Controler::Load()
{
    Sprite::Load();
}
