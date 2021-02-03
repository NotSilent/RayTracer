//
// Created by SILENT on 03/02/2021.
//

#include "Pattern.h"
#include "Shape.h"

Pattern::Pattern(const Color &a, const Color &b) :
        _a(a), _b(b), _transform(Mat4::identity()) {
}

Pattern::Pattern(const Mat4 &transform, const Color &a, const Color &b) :
        _a(a), _b(b), _transform(transform) {
}

Color Pattern::getA() const {
    return _a;
}

Color Pattern::getB() const {
    return _b;
}

Color Pattern::getColor(const Shape &shape, const Tuple &point) const {
    const auto objectPoint = shape.getTransform().inversed() * point;
    const auto patternPoint = _transform.inversed() * objectPoint;

    return getPoint(patternPoint);
}
