//
// Created by SILENT on 21/01/2021.
//

#include <numeric>
#include "math.h"
#include "FMath.h"

bool FMath::approximately(float lhs, float rhs) {
    //Tests need smaller precision
    //TODO: Create some engine utils class and change it to constexpr
#ifndef NDEBUG
    return fabsf(lhs - rhs) <= (std::numeric_limits<float>::epsilon() * 10);
#else
    return fabsf(lhs - rhs) <= std::numeric_limits<float>::epsilon();
#endif
}