#pragma once

#include <vector>

#include "Tile.hpp"

class Tiles : public PaintInterface {
private:
    std::vector<Tile> tiles;

public:
    Tiles();

    decltype (tiles[0]) &operator()(size_t x, size_t y);

    // PaintInterface interface
public:
    void Paint(Painter p, Camera c) override;
};
