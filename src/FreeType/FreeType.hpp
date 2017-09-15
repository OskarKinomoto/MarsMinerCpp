#pragma once

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <unicode/unistr.h>

#include "../Painter/Painter.hpp"
#include "../Utils/Utils.hpp"

#include "Character.hpp"
#include "Font.hpp"
#include "Ft.hpp"

class FreeType {
public:
    FreeType();
    ~FreeType();

    void Load();

    static Font Neuropol48;
    static Font Neuropol24;

private:
    Ft ft_ptr;

    static constexpr const int modeBit = 4;

    std::unique_ptr<unsigned char[]> buf;

    friend Font;
};
