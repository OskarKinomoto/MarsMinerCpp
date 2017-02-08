#include "Sprite.hpp"

#include "../Utils/Log.hpp"

namespace {

const int SIZE = 128;

}

Vector2 Sprite::size{};
Vector2 Sprite::range{};
TexturePtr Sprite::texture{};

void Sprite::UseTexture() { if (texture) texture->Use(); }

void Sprite::Load()
{
    texture = TexturePtr{new Texture{"img/sprite.png"}};

    range = texture->size / SIZE;
    size = 1.0f / range;

    LOGVV("Sprite – Range – " << range);
    LOGVV("Sprite – Size – " << size);
}

Vector2 Sprite::Coordinates(Sprite::Name sprite,
                            Sprite::VertexPosition vertexPosition, int offset) {
  int i = (static_cast<int>(sprite) + offset) % static_cast<int>(range.x);
  int j = (static_cast<int>(sprite) + offset) / static_cast<int>(range.x);

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
