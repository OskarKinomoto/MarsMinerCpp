#include "Character.hpp"

Character::Character(std::shared_ptr<Texture> tex, SizeUI offset, uint advance)
    : tex(std::move(tex)), offset(offset), advance(advance) {}
