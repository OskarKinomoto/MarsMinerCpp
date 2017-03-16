#include "Font.hpp"

#include "FreeType.hpp"

#include FT_ADVANCES_H

std::vector<uchar> Font::buf;

Font::Font() {
  LOGV("Font def");
}

Font& Font::operator=(Font&& f) {
  std::swap(face, f.face);
  std::swap(fontSize, f.fontSize);
  std::swap(ft, f.ft);
  return *this;
}

Font::Font(Ft ft, StringC path, uint size) : fontSize(size) {
  if (FT_New_Face(ft.ptr, path.c_str(), 0, &face))
    LOGV("Font – Failed to load font " << path);
  else
    LOGV("Font – " << path << " loaded");

  FT_Set_Pixel_Sizes(face, 0, size);
}

Font::~Font() {
  if (face)
    FT_Done_Face(face);
  face = nullptr;
}

void Font::Load(UChar32 c) {
  if (FT_Load_Char(face, static_cast<ulong>(c), FT_LOAD_RENDER)) {
    LOGV("FreeType – Failed to load Glyph");
    return;
  }

  SizeUI size{face->glyph->bitmap.width, face->glyph->bitmap.rows};

  auto buf_min_size = size.Area() * FreeType::modeBit;
  if (buf.size() < buf_min_size)
    buf.resize(buf_min_size);

  for (uint x = 0; x < size.height; ++x) {
    for (uint y = 0; y < size.width; ++y) {
      uint i = x * size.width + y;
      uint ii = i * 4;
      buf[ii + 0] = 255;
      buf[ii + 1] = 255;
      buf[ii + 2] = 255;
      buf[ii + 3] = face->glyph->bitmap.buffer[i];
    }
  }

  std::unique_ptr<Texture> t{new Texture{&buf[0], size, Texture::GLType::RGBA}};

  SizeUI offset{face->glyph->bitmap_left, face->glyph->bitmap_top};
}

Texture Font::GenTexture(const UnicodeString& str) {
  auto size = str.length();

  uint width = 0;

  for (int i = 0; i < size; ++i) {
    UChar32 c = str.charAt(i);
    FT_Fixed advance = 0;
    auto gindex = FT_Get_Char_Index(face, static_cast<ulong>(c));
    if (int error = FT_Get_Advance(face, gindex, FT_LOAD_RENDER, &advance)) {
      throw Exception("FT_Get_Advance: " + std::to_string(error));
    }
    uint adv = static_cast<uint>(advance >> 16);
    width += adv;
  }

  uint height = static_cast<uint>(face->size->metrics.height >> 6);
  // uint height = fontSize * 2;
  auto requiredBufSize = height * width * FreeType::modeBit;

  if (buf.size() < requiredBufSize)
    buf.resize(requiredBufSize);

  // baseline in fontSize

  uint textCursorPosition = 0;
  int underbaseline = static_cast<int>(fontSize);

  for (int i = 0; i < size; ++i) {
    if (FT_Load_Char(face, str[i], FT_LOAD_RENDER))
      throw Exception{"FreeType – Failed to load Glyph"};

    auto& glyph = *face->glyph;

    uint curX = textCursorPosition + static_cast<uint>(glyph.bitmap_left);
    uint curY = fontSize - static_cast<uint>(glyph.bitmap_top);
    SizeUI glyphSize = {glyph.bitmap.width, glyph.bitmap.rows};

    SWAP_MAX(underbaseline,
             static_cast<int>(glyph.bitmap.rows - glyph.bitmap_top));

    // if (FreeType:modeBit) ...

    for (uint y = 0; y < glyphSize.height; ++y) {
      for (uint x = 0; x < glyphSize.width; ++x) {
        uint posX = curX + x;
        uint posY = curY + y;
        uint buf_i = (posY * width + posX) * 4;
        uint glyph_i = y * glyphSize.width + x;  // todo move to increment

        buf[buf_i + 0] = 255;
        buf[buf_i + 1] = 255;
        buf[buf_i + 2] = 255;
        buf[buf_i + 3] = glyph.bitmap.buffer[glyph_i];
      }
    }

    textCursorPosition += glyph.advance.x >> 6;
  }
  // todo buf to texture (buf, tex_size, baseline_pos, real size?)
  return Texture{&buf[0], {width, height}, Texture::GLType::RGBA};
}
