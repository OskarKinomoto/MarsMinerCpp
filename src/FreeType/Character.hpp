#pragma once

#include <unicode/unistr.h>

#include "../Utils/Utils.hpp"
#include "../Painter/Texture.hpp"

class Character {
public:
    Character() = default;
    Character(std::shared_ptr<Texture> tex, SizeUI offset, uint advance);
    std::shared_ptr<Texture> tex;
    SizeUI offset;
    uint advance;
};
