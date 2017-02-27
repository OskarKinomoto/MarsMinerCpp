#include "BuildingBase.hpp"

#include "../Tile.hpp"

BuildingBase::BuildingBase([[maybe_unused]] StringC name,
                           int texWidth,
                           int texHeight,
                           Sprite::Name sprite,
                           int leftPos,
                           Robot& r)
    : texWidth(texWidth), texHeight(texHeight), sprite(sprite), robot(r) {
  LeftXPosition = leftPos * Tile::Size;
  RightXPosition = LeftXPosition + texWidth * Tile::Size;
}

float BuildingBase::Left() {
  return LeftXPosition;
}

float BuildingBase::Right() {
  return RightXPosition;
}

bool BuildingBase::CanEnter() {
  return -1 < robot.position.y && robot.position.y < 2 &&
         LeftXPosition - Robot::size.x / 2 < robot.position.x &&
         robot.position.x < RightXPosition - Robot::size.x / 2;
}

void BuildingBase::Paint(Painter p, Camera) {
  PositionF position{static_cast<float>(LeftXPosition),
                   static_cast<float>((texHeight - 1) * Tile::Size)};
  SizeI size{Tile::Size, Tile::Size};

  Sprite::UseTexture();
  p.Textures(true);
  p.BeginQuads();
  for (int i = 0; i < texHeight; ++i)
    for (int j = 0; j < texWidth; ++j)
      p.Sprite(position + PositionF{Tile::Size * j, -i * Tile::Size},
                     size, Layer::Buildings, sprite, i * texWidth + j);
  p.EndQuads();
}
