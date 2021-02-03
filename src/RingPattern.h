//
// Created by SILENT on 03/02/2021.
//

#ifndef RAYTRACER_RINGPATTERN_H
#define RAYTRACER_RINGPATTERN_H

#include "Pattern.h"

class RingPattern : public Pattern {
public:
    RingPattern(const Color &a, const Color &b);

    RingPattern(const Mat4 &transform, const Color &a, const Color &b);

    [[nodiscard]] virtual Color
    getPoint(const Tuple &point) const override;
};


#endif //RAYTRACER_RINGPATTERN_H
