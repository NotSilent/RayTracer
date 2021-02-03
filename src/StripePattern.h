//
// Created by SILENT on 03/02/2021.
//

#ifndef RAYTRACER_STRIPEPATTERN_H
#define RAYTRACER_STRIPEPATTERN_H

#include "Pattern.h"

class Shape;

class StripePattern : public Pattern {
public:
    StripePattern(const Color &a, const Color &b);

    StripePattern(const Mat4 &transform, const Color &a, const Color &b);

    [[nodiscard]] virtual Color
    getPoint(const Tuple &point) const override;
};


#endif //RAYTRACER_STRIPEPATTERN_H
