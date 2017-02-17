#include "OpenglVersion.hpp"

#include "Exception.hpp"

bool OpenglVersion::Validate(int major, int minor) {
  switch (major) {
    case 1:
      if (minor == 2)
        return true;
      break;

    case 2:
      switch (minor) {
        case 0:
        case 1:
          return true;
      }
      break;

    case 3:
    case 4:
      switch (minor) {
        case 0:
        case 1:
        case 2:
        case 3:
          return true;
      }
      break;
  }

  return false;
}

OpenglVersion::OpenglVersion(int major, int minor)
    : major(major), minor(minor) {

  if (!Validate(major, minor))
    throw Exception{
      std::string{"Incorrect openGL version: "} + std::to_string(major) +
      std::string{"."} + std::to_string(minor)
    };
}
