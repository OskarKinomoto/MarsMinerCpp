#include "Tiles.hpp"

#include <cmath>

#include "Model.hpp"

Tiles::Tiles() {
  size_t XSize = Model::MapXSize;
  tiles.resize(static_cast<size_t>(XSize * Model::MaxDepth));

  for (size_t x = 0; x < XSize; x++)
    for (size_t y = 0; y < Model::MaxDepth; y++)
      this->operator()(x, y) = Tile(Model::LeftX + x, -y);

  /*
   * 	foreach (var b in bs) {
              var left = (int)Math.Floor(b.left() / Tile.Size);
              var right = (int)Math.Floor(b.right() / Tile.Size);

              for (int x = left; x < right; ++x)
                  tiles[x - Model.MinX, 0].breakable = false;
                  */
}

decltype(Tiles::tiles[0]) & Tiles::operator()(size_t x, size_t y) {
  return tiles.at(x + y * Model::MapXSize);
}

void Tiles::Paint(Painter p, Camera c) {

  int yStart = static_cast<int>((-c.position.y - p.Height() / 2) / Tile::Size - 1);
  int yEnd =
      static_cast<int>(std::floor((-c.position.y + p.Height() / 2) / Tile::Size + 1));
  int xStart = static_cast<int>((-c.position.x - p.Width() / 2) / Tile::Size - 1);
  int xEnd = static_cast<int>((-c.position.x + p.Width() / 2) / Tile::Size + 1);

  // Tiles are only underground
  if (yEnd > 0)
    yEnd = 0;

  if (yStart <= -Model::MaxDepth)
    yStart = -Model::MaxDepth - 1;

  // Tiles only between MinX – MaxX
  if (xEnd > Model::RightX)
    xEnd = Model::RightX;

  if (xStart < Model::LeftX)
    xStart = Model::LeftX;

  if (yStart - yEnd > 0)
    return;

  p.Textures(true);
  Sprite::UseTexture();
  p.BeginQuads();

  for (int x = xStart; x < xEnd; ++x)
    for (int y = yStart; y <= yEnd; ++y)
        this->operator()(x - Model::LeftTile, -y).Paint(p, c);

  for (auto& tile : tiles) {
      tile.Paint(p,c);
  }

  p.EndQuads();
}
