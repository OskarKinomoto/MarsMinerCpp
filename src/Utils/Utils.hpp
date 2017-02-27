#pragma once

#include <string>

#include "Action.hpp"
#include "Color.hpp"
#include "Exception.hpp"
#include "Layer.hpp"
#include "Log.hpp"
#include "OpenglVersion.hpp"
#include "Tools.hpp"
#include "Vector2.hpp"

typedef std::string String;
typedef const std::string& StringC;

#ifdef __GNUC__
#define maybe_unused gnu::unused
#endif
