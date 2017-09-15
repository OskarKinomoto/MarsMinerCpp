#include "Surface.hpp"

#include "../FreeType/FreeType.hpp"

Surface::Surface(SizeUI size)
{
    Size(size);
}


void Surface::Paint(Painter p, Camera c)
{
    Texture tex = FreeType::Neuropol48.GenTexture("|(ŻŹÓŁĘćąpj)");

    c.Translate();
    p.Translate(-p.Size()/2);

    p.Textures(true);
    tex.Use();
    p.Color({255,128,0});
    p.BeginQuads();
    p.Square({0, 0}, tex.size, Layer::Surface);
    p.EndQuads();
    p.Color(Color::White);

    p.Translate(p.Size()/2);
    c.TranslateBack();

}

bool Surface::MouseEvent(Mouse)
{
    return true;
}
