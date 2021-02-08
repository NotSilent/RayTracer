//
// Created by SILENT on 21/01/2021.
//

#include <limits>
#include "FMath.h"

bool FMath::approximately(float lhs, float rhs) {
    return fabsf(lhs - rhs) < EPSILON;
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

float FMath::tan(float value) {
    return tanf(value);
}

bool FMath::isZero(float value) {
    return approximately(value, 0.0f);
}

bool FMath::isOne(float value) {
    return approximately(value, 1.0f);
}
