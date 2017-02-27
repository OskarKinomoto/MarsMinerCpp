#pragma once

#include <memory>
#include <string>

#include "../Utils/Utils.hpp"

class Texture {
public:
    enum class Type {
        Standard,
        Text,
    };

    Texture(std::string path);
    virtual void Use();
    virtual ~Texture();

    SizeI size;
    SizeI textSize;
private:
    unsigned int texID;
};

typedef std::unique_ptr<Texture> TexturePtr;
