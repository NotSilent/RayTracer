//
// Created by SILENT on 31/01/2021.
//

#ifndef RAYTRACERCHALLENGE_INTERSECTIONCOMPUTATIONS_H
#define RAYTRACERCHALLENGE_INTERSECTIONCOMPUTATIONS_H

#include "Tuple.h"

class Shape;

class IntersectionComputations {
public:
    IntersectionComputations(
            float distance, std::shared_ptr<Shape> object,
            Tuple point, Tuple eye, Tuple normal);

    [[nodiscard]] float getDistance() const;

    [[nodiscard]] std::shared_ptr<Shape> getObject() const;

    [[nodiscard]] Tuple getPoint() const;

    [[nodiscard]] Tuple getEye() const;

    [[nodiscard]] Tuple getNormal() const;

    [[nodiscard]] Tuple getOverPoint() const;

    [[nodiscard]] bool isInside() const;

private:
    float _distance;
    std::shared_ptr<Shape> _object;
    Tuple _point;
    Tuple _eye;
    Tuple _normal;
    Tuple _overPoint;
    bool _inside;
};

#endif //RAYTRACERCHALLENGE_INTERSECTIONCOMPUTATIONS_H
