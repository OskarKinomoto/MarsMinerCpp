#pragma once

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <unicode/unistr.h>

#include "../Utils/Utils.hpp"

#include "../Painter/Painter.hpp"

#include "Ft.hpp"
#include "Character.hpp"

class Font {
public:
    Font();
    Font &operator=(Font &&);
    Font(Ft ft, StringC path, uint size);
    ~Font();

    void Load(UChar32 c);

    Texture GenTexture(const UnicodeString &str);
private:
    FT_Face face = nullptr;
    static std::vector<uchar> buf;
    uint fontSize;
    Ft ft;
};
