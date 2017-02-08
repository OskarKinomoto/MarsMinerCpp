#pragma once

#include <memory>
#include <string>

#include "../Utils/Vector2.hpp"

class Texture {
public:
    enum class Type {
        Standard,
        Text,
    };

    Texture(std::string path);
    virtual void Use();
    virtual ~Texture();

    Vector2 size;
    Vector2 textSize;
private:
    unsigned int texID;
};

typedef std::unique_ptr<Texture> TexturePtr;
