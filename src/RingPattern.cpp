//
// Created by SILENT on 03/02/2021.
//

#include "RingPattern.h"

RingPattern::RingPattern(const Color &a, const Color &b)
        : Pattern(a, b) {
}

RingPattern::RingPattern(const Mat4 &transform, const Color &a, const Color &b)
        : Pattern(transform, a, b) {
}

Color RingPattern::getPoint(const Tuple &point) const {
    const auto sqrtX = point.getX() * point.getX();
    const auto sqrtZ = point.getZ() * point.getZ();
    const auto distance = std::sqrt(sqrtX + sqrtZ);
    if ((static_cast<int32_t>(std::floor(distance)) % 2 == 0)) {
        return getA();
    }

    return getB();
}
