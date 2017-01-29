#pragma once

#include <functional>


template<typename T, typename T2>
using ActionArgs2 = std::function<void(T, T2)>;

template<typename T>
using ActionArgs = std::function<void(T)>;

typedef std::function<void()> Action;

