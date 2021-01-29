//
// Created by SILENT on 21/01/2021.
//

#include <limits>
#include "FMath.h"

bool FMath::approximately(float lhs, float rhs) {
    //Tests need smaller precision
    //TODO: Create some engine utils class and change it to constexpr
#ifndef NDEBUG
    return fabsf(lhs - rhs) < 1e-4f;
#else
    return fabsf(lhs - rhs) < std::numeric_limits<float>::epsilon();
#endif
}

float FMath::sqrt(float value) {
    return sqrtf(value);
}

float FMath::sin(float value) {
    return sinf(value);
}

float FMath::cos(float value) {
    return cosf(value);
}
