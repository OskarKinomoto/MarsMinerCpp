#include "Ft.hpp"

#include "../Utils/Utils.hpp"

int Ft::counter = 0;

Ft::Ft(FT_Library ptr) : ptr(ptr) {
  counter++;
}

Ft::Ft(Ft& ft) : ptr(ft.ptr) {
  counter++;
}

Ft::Ft() : ptr(nullptr) {}

Ft::~Ft() {
  if (ptr) {
    counter--;
    if (counter == 0)
      FT_Done_FreeType(ptr);
  }
}

Ft& Ft::operator=(const Ft& ft) {
  if (!ptr) {
    ptr = ft.ptr;
    counter++;
  }

  return *this;
}
