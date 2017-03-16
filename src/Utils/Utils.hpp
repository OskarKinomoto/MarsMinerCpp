#pragma once

#include <string>
#include <sstream>
#include <memory>
#include <assert.h>

#include "Action.hpp"
#include "Color.hpp"
#include "Exception.hpp"
#include "Layer.hpp"
#include "Log.hpp"
#include "OpenglVersion.hpp"
#include "Tools.hpp"
#include "Vector2.hpp"
#include "GameOverException.hpp"

typedef std::string String;
typedef const std::string& StringC;

typedef unsigned int uint;
typedef unsigned char uchar;

typedef std::unique_ptr<void, decltype(&free)> voidptr;

inline constexpr unsigned char operator "" _uchar( unsigned long long arg ) noexcept
{
    return static_cast< unsigned char >( arg );
}

template<typename T>
constexpr T pi = T(3.1415926535897932385);

#ifdef __GNUC__
#define maybe_unused gnu::unused
#endif

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define SWAP_MAX(to,b) (to) = MAX((to), (b))
