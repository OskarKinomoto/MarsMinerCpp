#include "Texture.hpp"

#include "../Utils/Exception.hpp"
#include "../Utils/Log.hpp"

#include <libpng16/png.h>
#include <GL/gl.h>

#include <memory>
#include <iostream>

namespace {

void glError() {
  auto ret = glGetError();
  if (ret != GL_NO_ERROR) {
    switch (ret) {
      case GL_INVALID_ENUM:
        throw Exception("GL_INVALID_ENUM");
      case GL_INVALID_VALUE:
        throw Exception("GL_INVALID_VALUE");
      case GL_INVALID_OPERATION:
        throw Exception("GL_INVALID_OPERATION");
      case GL_INVALID_FRAMEBUFFER_OPERATION:
        throw Exception("GL_INVALID_FRAMEBUFFER_OPERATION");
      default:
        throw Exception("GL_UNKNOWN");
    }
  }
}
}

namespace {

typedef std::unique_ptr<FILE, decltype(&fclose)> FilePtr;

GLuint png_texture_load(const std::string& path, int* width, int* height) {
  png_structp png_ptr = nullptr;
  png_infop info_ptr = nullptr;
  png_infop end_info = nullptr;

  try {
    png_byte header[8];
    int bitDepth, colorType;
    png_uint_32 pngWidth, pngHeight;
    // png_byte** rowPtrs = nullptr;

    FilePtr fp(fopen(path.c_str(), "rb"), &fclose);
    if (fp == 0)  // TODO errno exception
      throw Exception{"texture: " + path + " – does not exists!"};

    fread(header, 1, 8, fp.get());
    if (png_sig_cmp(header, 0, 8))
      throw Exception{"libpng: " + path + " – is not a PNG!"};

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr,
                                     nullptr);

    if (!png_ptr)
      throw Exception{"libpng: " + path + " – png_create_read_struct"};

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
      throw Exception{"libpng: " + path + " – png_create_info_struct"};

    end_info = png_create_info_struct(png_ptr);
    if (!end_info)
      throw Exception{"libpng: " + path + " – png_create_info_struct"};

    if (setjmp(png_jmpbuf(png_ptr)))
      throw Exception{"libpng: " + path + " – error"};

    png_init_io(png_ptr, fp.get());
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    png_get_IHDR(png_ptr, info_ptr, &pngWidth, &pngHeight, &bitDepth,
                 &colorType, nullptr, nullptr, nullptr);

    if (width)
      *width = pngWidth;

    if (height)
      *height = pngHeight;

    if (bitDepth != 8)
      throw Exception{"libpng: " + path + " – unsupported bit depth " +
                      std::to_string(bitDepth)};

    GLint format;
    switch (colorType) {
      case PNG_COLOR_TYPE_RGB:
        format = GL_RGB;
        break;
      case PNG_COLOR_TYPE_RGB_ALPHA:
        format = GL_RGBA;
        break;
      default:
        throw Exception{"libpng: " + path + " – unknown color type " +
                        std::to_string(colorType)};
    }

    png_read_update_info(png_ptr, info_ptr);

    auto rowbytes = png_get_rowbytes(png_ptr, info_ptr);
    rowbytes += 3 - ((rowbytes - 1) % 4);

    std::unique_ptr<png_byte, decltype(&free)> image_data{
        static_cast<png_byte*>(
            malloc(rowbytes * pngHeight * sizeof(png_byte) + 15)),
        &free};

    if (!image_data)
      throw Exception{"libpng: " + path +
                      " – could not allocate memory for PNG image data"};

    std::unique_ptr<png_byte*, decltype(&free)> rowPtrs(
        static_cast<png_byte**>(malloc(pngHeight * sizeof(png_byte*))), &free);

    if (!rowPtrs)
      throw Exception{"libpng: " + path +
                      " – could not allocate memory for PNG row pointers"};

    for (unsigned int i = 0; i < pngHeight; i++)
      rowPtrs.get()[pngHeight - 1 - i] = image_data.get() + i * rowbytes;

    png_read_image(png_ptr, rowPtrs.get());

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, format, *width, *height, 0, format,
                 GL_UNSIGNED_BYTE, image_data.get());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);

    LOGVV("Texture – " << path << " – loaded");
    LOGVVV("Size: " << *width << "x" << *height);

    return texture;

  } catch (...) {
    png_structp* ptr1 = png_ptr ? &png_ptr : nullptr;
    png_infop* ptr2 = png_ptr ? &info_ptr : nullptr;
    png_infop* ptr3 = png_ptr ? &end_info : nullptr;
    png_destroy_read_struct(ptr1, ptr2, ptr3);
    throw;
  }
}
}

Texture::Texture(std::string path) {
  int width;
  int height;
  texID = png_texture_load(path.c_str(), &width, &height);

  size = {width, height};
}

void Texture::Use() {
  glBindTexture(GL_TEXTURE_2D, texID);
  glError();
}

Texture::~Texture() {
  glDeleteTextures(1, &texID);
  texID = 0;
  glError();
}
