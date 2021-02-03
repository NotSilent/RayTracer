//
// Created by SILENT on 03/02/2021.
//

#include "StripePattern.h"

StripePattern::StripePattern(const Color &a, const Color &b) :
        Pattern(a, b) {
}

StripePattern::StripePattern(const Mat4 &transform, const Color &a, const Color &b) :
        Pattern(transform, a, b) {
}

Color StripePattern::getPoint(const Tuple &point) const {
    if ((static_cast<int32_t>(std::floor(point.getX())) % 2) == 0) {
        return getA();
    }

    return getB();
}
