#include "Surface.hpp"

#include "../FreeType/FreeType.hpp"

Surface::Surface(SizeUI size)
{
    Size(size);
}


void Surface::Paint(Painter p, Camera)
{
    Texture tex = FreeType::Neuropol48.GenTexture("|(ŻŹÓŁĘćąpj)");

    p.Textures(true);
    tex.Use();
    p.Color({255,255,0});
    p.BeginQuads();
    p.Square({0, 0}, tex.size, Layer::Surface);
    p.EndQuads();
    p.Color(Color::White);
}

bool Surface::MouseEvent(Mouse)
{
    return true;
}
