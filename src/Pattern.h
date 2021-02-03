//
// Created by SILENT on 03/02/2021.
//

#ifndef RAYTRACER_PATTERN_H
#define RAYTRACER_PATTERN_H

#include "Color.h"
#include "Matrix.h"

class Shape;

class Pattern {
public:
    Pattern(const Color &a, const Color &b);

    Pattern(const Mat4 &transform, const Color &a, const Color &b);

    [[nodiscard]] Color getA() const;

    [[nodiscard]] Color getB() const;

    [[nodiscard]] virtual Color
    getPoint(const Tuple &point) const = 0;

    [[nodiscard]] Color getColor(const Shape &shape, const Tuple &point) const;

private:
    Color _a;
    Color _b;
    Mat4 _transform;
};


#endif //RAYTRACER_PATTERN_H
