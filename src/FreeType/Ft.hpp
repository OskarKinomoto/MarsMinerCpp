#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

class Ft {
 public:
  Ft();
  Ft(FT_Library ptr);

  Ft(Ft& ft);
  Ft(Ft&&) = default;
  Ft& operator=(const Ft& ft);

  ~Ft();

  FT_Library ptr;

 private:
  static int counter;
};
