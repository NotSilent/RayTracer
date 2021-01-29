//
// Created by SILENT on 21/01/2021.
//

#ifndef RAYTRACERCHALLENGE_FMATH_H
#define RAYTRACERCHALLENGE_FMATH_H

#include <numbers>

enum class Axis {
    X, Y, Z
};

class FMath {
public:
    static constexpr float PI = static_cast<float>(std::numbers::pi);

    static bool approximately(float lhs, float rhs);

    static float sqrt(float value);

    static float sin(float value);

    static float cos(float value);
};

#endif //RAYTRACERCHALLENGE_FMATH_H
