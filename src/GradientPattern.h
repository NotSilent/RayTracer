//
// Created by SILENT on 03/02/2021.
//

#ifndef RAYTRACER_GRADIENTPATTERN_H
#define RAYTRACER_GRADIENTPATTERN_H

#include "Pattern.h"

class GradientPattern : public Pattern {
public:
    GradientPattern(const Color &a, const Color &b);

    GradientPattern(const Mat4 &transform, const Color &a, const Color &b);

    [[nodiscard]] virtual Color
    getPoint(const Tuple &point) const override;
};


#endif //RAYTRACER_GRADIENTPATTERN_H
