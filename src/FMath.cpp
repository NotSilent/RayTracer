//
// Created by SILENT on 21/01/2021.
//

#include <numeric>
#include "math.h"
#include "FMath.h"

bool FMath::approximately(float lhs, float rhs) {
    return fabsf(lhs - rhs) <= std::numeric_limits<float>::epsilon();
}