//
// Created by SILENT on 03/02/2021.
//

#ifndef RAYTRACER_CHECKERSPATTERN_H
#define RAYTRACER_CHECKERSPATTERN_H

#include "Pattern.h"

class CheckersPattern : public Pattern {
public:
    CheckersPattern(const Color &a, const Color &b);

    CheckersPattern(const Mat4 &transform, const Color &a, const Color &b);

    [[nodiscard]] virtual Color
    getPoint(const Tuple &point) const override;
};


#endif //RAYTRACER_CHECKERSPATTERN_H
