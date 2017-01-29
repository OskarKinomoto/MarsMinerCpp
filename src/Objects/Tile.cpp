#include "Tile.hpp"

#include "Model.hpp"

#include "../Utils/Exception.hpp"

#include <random>

namespace {

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> holesRnd(0, 11);
std::uniform_int_distribution<> mineralsRnd(0, 10);

constexpr Sprite::Name RockTile(int x, int y)
{
    int i = ((x + 991) * (y + 293)) % 8;

    switch (i) {
    case 0:
        return Sprite::Name::TileNonBreakable1;
    case 1:
        return Sprite::Name::TileNonBreakable2;
    case 2:
        return Sprite::Name::TileNonBreakable3;
    case 3:
        return Sprite::Name::TileNonBreakable4;
    case 4:
        return Sprite::Name::TileNonBreakable5;
    case 5:
        return Sprite::Name::TileNonBreakable6;
    case 6:
        return Sprite::Name::TileNonBreakable7;
    case 7:
    default:
        return Sprite::Name::TileNonBreakable8;
    }
}

}

Tile::Tile() : x(0), y(0)
{

}

Tile::Tile(int x, int y, bool exists) : x(x), y(y)
{
    state = exists ? State::Exist : State::None;
    collisionable = exists;
}

Tile::Tile(int x, int y) : x(x), y(y), position(x * Size, y * Size)
{
    if (y != 0 && -y != Model::MaxDepth - 20) {
        state = GenerateTile() ? State::Exist : State::None;

        if (state == State::Exist && mineralsRnd(gen) == 0) {
            state = State::Mineral;
            mineral = Mineral::RandomByDepth(y);
        }
    } else if(-y == Model::MaxDepth - 20) {
        state = State::Exist;
        breakable = false;
    } else {
        state = State::Exist;
    }

    collisionable = Exists();
}

void Tile::Destroy()
{
    collisionable = false;
    mineral = Mineral::None;
    state = State::None;
}

bool Tile::Exists() const
{
    return state != State::None;
}

bool Tile::Breakable() const
{
    return state != State::NonBreakable;
}

void Tile::Breakable(bool b)
{
    if (Exists())
        state = b ? State::Exist : State::NonBreakable;
}

Mineral Tile::GetMineral() const
{
    return mineral;
}

bool Tile::Collisionable() const
{
    return collisionable;
}

bool Tile::GenerateTile()
{
    return holesRnd(gen) != 0;
}

void Tile::Paint(Painter p, Camera)
{
    if (state == State::None)
        return;

    Sprite::Name sprite = Sprite::Name::TileFull;

    p.Sprite(position, Vector2(Size, Size), Layer::Tiles, sprite);

    sprite = static_cast<Sprite::Name>(-1);
    switch (state) {
    case State::NonBreakable:
        sprite = RockTile(x, y);
        break;
    case State::Mineral:
        sprite = mineral.GetSprite();
        break;

    case State::Exist:
    case State::None:
        break;
    }

    if (static_cast<int>(sprite) != -1)
        p.Sprite(position, Vector2{Size, Size}, Layer::Tiles++, sprite);
}

