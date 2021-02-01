//
// Created by SILENT on 31/01/2021.
//

#ifndef RAYTRACERCHALLENGE_INTERSECTIONCOMPUTATIONS_H
#define RAYTRACERCHALLENGE_INTERSECTIONCOMPUTATIONS_H


#include "Sphere.h"

class IntersectionComputations {
public:
    IntersectionComputations(
            float distance, Sphere object, Tuple point, Tuple eye, Tuple normal);

    [[nodiscard]] float getDistance() const;

    [[nodiscard]] Sphere getObject() const;

    [[nodiscard]] Tuple getPoint() const;

    [[nodiscard]] Tuple getEye() const;

    [[nodiscard]] Tuple getNormal() const;

    [[nodiscard]] bool isInside() const;

private:
    float _distance;
    Sphere _object;
    Tuple _point;
    Tuple _eye;
    Tuple _normal;
    bool _inside;
};

static_assert(std::is_trivially_copyable<IntersectionComputations>::value,
              "Try to make it trivially copyable");

#endif //RAYTRACERCHALLENGE_INTERSECTIONCOMPUTATIONS_H
