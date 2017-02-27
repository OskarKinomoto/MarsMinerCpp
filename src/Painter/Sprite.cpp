#include "Sprite.hpp"

#include "../Utils/Log.hpp"

namespace {

const int SIZE = 128;

}

VectorF Sprite::size{};
VectorF Sprite::range{};
TexturePtr Sprite::texture{};

void Sprite::UseTexture() { texture->Use(); }

void Sprite::Load()
{
    texture = TexturePtr{new Texture{"img/sprite.png"}};

    range = texture->size / SIZE;
    size = range.Reverse();

    LOGVV("Sprite – Range – " << range);
    LOGVV("Sprite – Size – " << size);
}

VectorF Sprite::Coordinates(Sprite::Name sprite,
                            Sprite::VertexPosition vertexPosition, int offset) {
  int i = (static_cast<int>(sprite) + offset) % static_cast<int>(range.x);
  int j = (static_cast<int>(sprite) + offset) / static_cast<int>(range.x);
  j = 15 - j;

  switch (vertexPosition) {
    case VertexPosition::LeftBottom:
      return {i * size.x, j * size.y};

    case VertexPosition::LeftTop:
      return {(i + 1) * size.x, j * size.y};

    case VertexPosition::RightBottom:
      return {(i + 1) * size.x, (j + 1) * size.y};

    case VertexPosition::RightTop:
      return {i * size.x, (j + 1) * size.y};
  }

  throw new std::exception();
}
