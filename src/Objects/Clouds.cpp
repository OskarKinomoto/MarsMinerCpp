#include "Clouds.hpp"

#include "../Objects/Model.hpp"

Clouds::Clouds()
    : tex1("img/clouds.png"),
      tex2("img/clouds-low.png"),
      pos1(0, 200),
      pos2(100, 75) {}

void Clouds::Tick(float dt) {
  pos1.x += dt * WindConstL1;
  pos2.x += dt * WindConstL2;

  if (pos1.x >= tex1.size.x)
    pos1.x -= tex1.size.x;

  if (pos2.x >= tex2.size.x)
    pos2.x -= tex2.size.x;
}

void Clouds::Paint(Painter p, Camera) {
  p.Textures(true);

  tex2.Use();
  p.BeginQuads();
  p.Square(pos2 + Vector2{Model::LeftTile, 0}, tex2.size, Layer::CloudsLow);
  p.Square(pos2 + Vector2{Model::LeftTile - tex2.size.x, 0}, tex2.size,
           Layer::CloudsLow);
  p.Square(pos2 + Vector2{Model::LeftTile + tex2.size.x, 0}, tex2.size,
           Layer::CloudsLow);
  p.EndQuads();

  tex1.Use();
  p.BeginQuads();
  p.Square(pos1 + Vector2{Model::LeftTile, 0}, tex1.size, Layer::Clouds);
  p.Square(pos1 + Vector2{Model::LeftTile - tex1.size.x, 0}, tex1.size,
           Layer::Clouds);
  p.Square(pos1 + Vector2{Model::LeftTile + tex1.size.x, 0}, tex1.size,
           Layer::Clouds);
  p.EndQuads();
}
