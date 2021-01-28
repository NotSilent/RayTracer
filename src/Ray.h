//
// Created by SILENT on 26/01/2021.
//

#ifndef RAYTRACERCHALLENGE_RAY_H
#define RAYTRACERCHALLENGE_RAY_H


#include <vector>
#include <optional>
#include "Tuple.h"
#include "Matrix.h"

class Ray {
public:
    Ray(const Tuple &origin, const Tuple &direction);

    friend Ray operator*(const Mat4 &lhs, const Ray &rhs);

    [[nodiscard]] Tuple getOrigin() const;

    [[nodiscard]] Tuple getDirection() const;

    [[nodiscard]] Tuple getPosition(float distance) const;

private:
    Tuple _origin;
    Tuple _direction;
};


#endif //RAYTRACERCHALLENGE_RAY_H
