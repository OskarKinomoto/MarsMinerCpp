#pragma once

#include "../Utils/Color.hpp"
#include "../Utils/Layer.hpp"
#include "../Utils/Vector2.hpp"

#include "Sprite.hpp"

class PainterBase {
public:
    virtual void SetUp() = 0;
    virtual void CleanView() = 0;

    virtual void BeginQuads() = 0;
    virtual void Square(PositionF position, SizeUI size, Layer layer) = 0;
    virtual void Sprite(PositionF position, SizeUI size, const Layer layer, Sprite::Name sprite, int offset = 0) = 0;
    virtual void EndQuads() = 0;

    virtual void Translate(VectorF v) = 0;

    virtual void Gradient(PositionF start, Color c1, PositionF end, Color c2, Layer layer) = 0;
    virtual void Color(Color color) = 0;

    virtual void Textures(bool enable) = 0;

    virtual void Resize(int width, int height) = 0;
    virtual float Width() const = 0;
    virtual float Height() const = 0;

    virtual VectorF Size() const = 0;

    virtual ~PainterBase() = default;
};

typedef PainterBase& Painter;
