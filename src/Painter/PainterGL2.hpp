#pragma once

#include "Painter.hpp"

class PainterGL2 : public PainterBase {
public:
    void SetUp() override;
    void CleanView() override;

    void BeginQuads() override;
    void Square(PositionF position, SizeI size, Layer layer) override;
    void Sprite(PositionF position, SizeI size, const Layer layer, Sprite::Name sprite, int offset = 0) override;
    void EndQuads() override;

    void Translate(VectorF v) override;

    void Gradient(PositionF start, class Color c1, PositionF end, class Color c2, Layer layer) override;
    void Color(class Color color) override;

    void Textures(bool enable) override;

    void Resize(int width, int height) override;
    float Width() const override;
    float Height() const override;
private:
    bool texturesEnabled = false;
    int width = 800;
    int height = 600;
};
