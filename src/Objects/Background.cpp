#include "Background.hpp"

#include "Model.hpp"

void Background::Paint(Painter p, Camera)
{
    p.Textures(false);
    p.BeginQuads();

    p.Gradient(PositionF{Model::LeftTile, 0}, Color{.2f, .6f, .9f},
               PositionF{Model::RightTile, 100 * Tile::Size}, Color{0.f,0.f,.1f},
               Layer::Background);

    p.Gradient(PositionF{Model::LeftTile, 0}, Color{.37f, .22f, .07f},
               PositionF{Model::RightTile, -50 * Tile::Size}, Color{.26f, .15f, .03f},
               Layer::Background);

    p.Gradient(PositionF{Model::LeftTile, -50 * Tile::Size}, Color{.26f, .15f, .03f},
               PositionF{Model::RightTile, -100 * Tile::Size}, Color{.15f, .08f, .01f},
               Layer::Background);
    p.EndQuads();
}
