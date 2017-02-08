cmake_minimum_required(VERSION 3.0.2)

project(MarsMiner VERSION 1 LANGUAGES CXX)

SET(CMAKE_CXX_FLAGS_PROFILING "-O0 -g -pg")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "-O2 -g")
SET(CMAKE_CXX_FLAGS_CCOV "-O2 -g --coverage")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include(FindOpenGL)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(GLEW REQUIRED glew)
pkg_search_module(PNG REQUIRED libpng16)

# Set compiler warning flags
ADD_DEFINITIONS("-Werror") # Make all warnings into errors.
ADD_DEFINITIONS("-Wall") # Generate all warnings
ADD_DEFINITIONS("-Wextra") # Generate even more extra warnings

file(COPY img DESTINATION bin/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

ADD_SUBDIRECTORY(src)
