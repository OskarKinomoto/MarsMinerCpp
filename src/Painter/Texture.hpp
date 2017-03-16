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

    enum class GLType {
        RGBA,
        RED,
    };

    Texture() = default;
    Texture(std::string path);
    Texture(void *buf, SizeUI size, GLType glType);
    virtual void Use();
    virtual ~Texture();

    SizeUI size;
private:
    uint texID;
};

typedef std::unique_ptr<Texture> TexturePtr;
