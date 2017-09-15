#include "FreeType.hpp"

Font FreeType::Neuropol48;
Font FreeType::Neuropol24;

FreeType::FreeType() : buf(new uchar[500 * 100 * modeBit]) {
  FT_Library ft = nullptr;
  if (FT_Init_FreeType(&ft))
    LOGV("FreeType – Could not init FreeType Library");
  else
    LOGV("FreeType – Initialised");
  ft_ptr = {ft};
}

FreeType::~FreeType() {}

void FreeType::Load() {
    Neuropol48 = Font{ft_ptr, "fonts/neuropol.ttf", 48};
    Neuropol24 = Font{ft_ptr, "fonts/neuropol.ttf", 24};
}
