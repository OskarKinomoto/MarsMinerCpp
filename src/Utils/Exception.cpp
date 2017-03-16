#include "Exception.hpp"

Exception::Exception(std::string str) : str(std::move(str)) {}

const char* Exception::what() const noexcept {
  return str.c_str();
}
