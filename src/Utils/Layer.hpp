#pragma once

class Layer {
public:
    static const Layer Background;
    static const Layer Clouds;
    static const Layer Grass;
    static const Layer Tiles;
    static const Layer Buildings;
    static const Layer Minerals;
    static const Layer Robot;
    static const Layer Window;

    const Layer operator++(int) const;

    explicit operator float();
private:
    Layer(float layer);

    float z;

};
