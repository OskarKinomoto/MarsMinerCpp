#pragma once

#include "../Utils/Vector2.hpp"

#include "Texture.hpp"

class Sprite {
 public:
  enum class Name {
    None = -1,
    RobotLeft = 0,
    RobotRight = 1,
    TileFull = 2,
    Empty3 = 3,
    CloseCircle = 4,
    CloseCircleFocus = 5,
    ButtonLeft = 6,
    ButtonCenter = 7,
    ButtonRight = 8,
    ButtonFocusLeft = 9,
    ButtonFocusCenter = 10,
    ButtonFocusRight = 11,
    TileGold = 12,
    TileLapis = 13,
    TileSilver = 14,
    TileSaphire = 15,
    TilePlatinium = 16,
    TileCopper = 17,
    TileRubin = 18,
    TileNonBreakable1 = 19,
    TileNonBreakable2 = 20,
    TileNonBreakable3 = 21,
    TileNonBreakable4 = 22,
    TileSalt = 23,
    TileEmerald = 24,
    BuildingGasStation = 25,  // – 30
    Shop = 31,                // – 38
    RepairShop = 39,          // – 44
    EnhancementShop = 45,     // – 52
    TileNonBreakable5 = 53,
    TileNonBreakable6 = 54,
    TileNonBreakable7 = 55,
    TileNonBreakable8 = 56,
    TileFe = 57,
    Grass = 58,  // – 64
    GrassRoots = 73,  // – ?
  };

  enum class VertexPosition {
    LeftTop,
    LeftBottom,
    RightTop,
    RightBottom,
  };

  static void UseTexture();
  static void Load();
  static VectorF Coordinates(Name sprite, VertexPosition vertexPosition,
                             int offset = 0);

 private:
  static TexturePtr texture;
  static VectorF range;
  static VectorF size;
};
