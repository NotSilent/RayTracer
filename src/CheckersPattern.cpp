//
// Created by SILENT on 03/02/2021.
//

#include "CheckersPattern.h"

CheckersPattern::CheckersPattern(const Color &a, const Color &b) :
        Pattern(a, b) {
}

CheckersPattern::CheckersPattern(const Mat4 &transform, const Color &a, const Color &b) :
        Pattern(transform, a, b) {
}

Color CheckersPattern::getPoint(const Tuple &point) const {
    const auto val = floor(point.getX()) + floor(point.getY()) + floor(point.getZ());
    if ((static_cast<int32_t>(val)) % 2 == 0) {
        return getA();
    }

    return getB();
}