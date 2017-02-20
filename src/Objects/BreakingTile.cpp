#include "BreakingTile.hpp"

#include "../Robot/Robot.hpp"

#include "Tile.hpp"

BreakingTile::BreakingTile(Tile *tile) : tile(tile), destroyed(false)
{
    positionInit();
}

void BreakingTile::Destroy()
{
    if (tile)
        tile->Destroy();
}

void BreakingTile::Reset()
{
    tile = nullptr;
    destroyed = false;
    position = {};
}

void BreakingTile::positionInit()
{
    position = Vector2{tile->x * Tile::Size + (Tile::Size - Robot::size.x) / 2,
            static_cast<float>((tile->y - 1) * Tile::Size + 1)};
}
