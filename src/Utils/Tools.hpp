#pragma once

constexpr float epsilon = 1e-3f;

inline bool isZero(float f) {
    return f < epsilon && f > -epsilon;
}

