//
// Created by SILENT on 03/02/2021.
//

#include "GradientPattern.h"

GradientPattern::GradientPattern(const Color &a, const Color &b)
        : Pattern(a, b) {
}

GradientPattern::GradientPattern(const Mat4 &transform, const Color &a, const Color &b)
        : Pattern(transform, a, b) {
}

Color GradientPattern::getPoint(const Tuple &point) const {
    const float absoluteX = std::abs(point.getX());
    const auto distance = getB() - getA();
    const auto fraction = absoluteX - floor(absoluteX);

    return getA() + distance * fraction;
}
