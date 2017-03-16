#pragma once

#include "../Utils/Vector2.hpp"
#include "../Interfaces/PaintInterface.hpp"
#include "BreakingTile.hpp"

#include "Mineral.hpp"

#include <cstdlib>

class Tile : public PaintInterface {
 public:
  static constexpr int Size = 60;

  int x;
  int y;

  PositionF position;

  Tile();
  Tile(int x, int y, bool exists);
  Tile(int x, int y);

  void Destroy();

  bool Exists() const;
  bool Breakable() const;
  void Breakable(bool);
  const Mineral *GetMineral() const;
  bool Collisionable() const;
  BreakingTile SetCollision();

  static bool VertexInTile(VectorF tile, VectorF point);

 private:
  enum class State {
    None,
    Exist,
    Mineral,
    NonBreakable,
  };

  State state;
  bool collisionable;
  bool breakable;

  const Mineral *mineral = nullptr;

  bool GenerateTile();

  // PaintInterface interface
 public:
  void Paint(Painter p, Camera c) override;
};
