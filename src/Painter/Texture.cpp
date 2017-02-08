#include "Texture.hpp"

#include "../Utils/Exception.hpp"
#include "../Utils/Log.hpp"

#include <libpng16/png.h>
#include <GL/gl.h>

#include <memory>
#include <iostream>

namespace {

void glError()
{
    auto ret = glGetError();
    if (ret != GL_NO_ERROR) {
        switch(ret) {
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

GLuint png_texture_load(const std::string &path, int* width, int* height) {
  // This function was originally written by David Grayson for
  // https://github.com/DavidEGrayson/ahrs-visualizer

  png_byte header[8];
  png_structp png_ptr = nullptr;
  png_infop info_ptr = nullptr;
  png_infop end_info = nullptr;
  png_byte** row_pointers = nullptr;

  try {
  FilePtr fp(fopen(path.c_str(), "rb"), &fclose);
  if (fp == 0) // TODO errno exception
    throw Exception{"texture: " + path + " – does not exists!"};

  // read the header
  fread(header, 1, 8, fp.get());

  if (png_sig_cmp(header, 0, 8))
    throw Exception{"libpng: " + path + " – is not a PNG!"};

  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

  if (!png_ptr)
    throw Exception{"libpng: " + path + " – png_create_read_struct"};

  // create png info struct
  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
      throw Exception{"libpng: " + path + " – png_create_info_struct"};

  // create png info struct
  end_info = png_create_info_struct(png_ptr);
  if (!end_info)
    throw Exception{"libpng: " + path + " – png_create_info_struct"};

  // the code in this if statement gets called if libpng encounters an error
  if (setjmp(png_jmpbuf(png_ptr)))
      throw Exception{"libpng: " + path + " – error"};

  // init png reading
  png_init_io(png_ptr, fp.get());

  // let libpng know you already read the first 8 bytes
  png_set_sig_bytes(png_ptr, 8);

  // read all the info up to the image data
  png_read_info(png_ptr, info_ptr);

  // variables to pass to get info
  int bit_depth, color_type;
  png_uint_32 temp_width, temp_height;

  // get info about png
  png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth,
               &color_type, nullptr, nullptr, nullptr);

  if (width)
    *width = temp_width;

  if (height)
    *height = temp_height;

  // printf("%s: %lux%lu %d\n", file_name, temp_width, temp_height, color_type);

  if (bit_depth != 8)
      throw Exception{"libpng: " + path + " – unsupported bit depth " + std::to_string(bit_depth)};

  GLint format;
  switch (color_type) {
    case PNG_COLOR_TYPE_RGB:
      format = GL_RGB;
      break;
    case PNG_COLOR_TYPE_RGB_ALPHA:
      format = GL_RGBA;
      break;
    default:
      throw Exception{"libpng: " + path + " – unknown color type " + std::to_string(color_type)};
  }

  // Update the png info struct.
  png_read_update_info(png_ptr, info_ptr);

  // Row size in bytes.
  auto rowbytes = png_get_rowbytes(png_ptr, info_ptr);

  // glTexImage2d requires rows to be 4-byte aligned
  rowbytes += 3 - ((rowbytes - 1) % 4);

  std::unique_ptr<png_byte, decltype(&free)> image_data
  {static_cast<png_byte*>
              (malloc(rowbytes * temp_height * sizeof(png_byte) + 15)), &free};

  if (!image_data)
      throw Exception{"libpng: " + path + " – could not allocate memory for PNG image data"};

  // row_pointers is for pointing to image_data for reading the png with libpng
  row_pointers = static_cast<png_byte**>(malloc(temp_height * sizeof(png_byte*)));

  if (!row_pointers)
      throw Exception{"libpng: " + path + " – could not allocate memory for PNG row pointers"};

  // set the individual row_pointers to point at the correct offsets of
  // image_data
  for (unsigned int i = 0; i < temp_height; i++)
    row_pointers[temp_height - 1 - i] = image_data.get() + i * rowbytes;

  // read the png into image_data through row_pointers
  png_read_image(png_ptr, row_pointers);

  // Generate the OpenGL texture object
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, format,
               temp_width, temp_height,
               0, format,
               GL_UNSIGNED_BYTE, image_data.get());
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // clean up
  png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
  free(row_pointers);

  LOGVV("Texture – " << path << " – loaded");
  LOGVVV("Size: " << *width << "x" << *height);

  return texture;

  } catch (...) {
      png_structp *ptr1 = png_ptr ? &png_ptr : nullptr;
      png_infop *ptr2 = png_ptr ? &info_ptr : nullptr;
      png_infop *ptr3 = png_ptr ? &end_info : nullptr;
      png_destroy_read_struct(ptr1, ptr2, ptr3);
      throw;
  }
}
}

Texture::Texture(std::string path) {
    int width;
    int height;
  texID = png_texture_load(path.c_str(), &width, &height);

  size = {static_cast<float>(width), static_cast<float>(height)};
}

void Texture::Use()
{
    glBindTexture(GL_TEXTURE_2D, texID);
    glError();
}

Texture::~Texture()
{
    glDeleteTextures(1, &texID);
    texID = 0;
    glError();
}
