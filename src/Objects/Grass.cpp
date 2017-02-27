#include "Grass.hpp"

#include "../Objects/Model.hpp"

const SizeI Grass::size{60, 40};

void Grass::Paint(Painter p, Camera) {
  Sprite::UseTexture();
  p.Textures(true);
  p.BeginQuads();

  int phase = 0;
  for (int i = Model::LeftX; i < Model::RightX; ++i) {
    phase++;
    p.Sprite({static_cast<float>(Tile::Size * i), 0}, size, Layer::Grass,
             Sprite::Name::Grass, phase % GrassTiles);
    p.Sprite({static_cast<float>(Tile::Size * i), -Tile::Size + 23}, size,
             Layer::Grass, Sprite::Name::GrassRoots, phase % GrassTiles);
  }

  p.EndQuads();
}
