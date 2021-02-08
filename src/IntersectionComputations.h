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
            const Tuple &point, const Tuple &eye, const Tuple &normal, const Tuple &reflection);

    [[nodiscard]] float getDistance() const;

    [[nodiscard]] std::shared_ptr<Shape> getObject() const;

    [[nodiscard]] Tuple getPoint() const;

    [[nodiscard]] Tuple getEye() const;

    [[nodiscard]] Tuple getNormal() const;

    [[nodiscard]] Tuple getOverPoint() const;

    [[nodiscard]] Tuple getUnderPoint() const;

    [[nodiscard]] Tuple getReflection() const;

    [[nodiscard]] bool isInside() const;

    [[nodiscard]] float getRefractiveIndexExit() const;

    [[nodiscard]] float getRefractiveIndexEnter() const;

    [[nodiscard]] float getReflectance() const;

    void setRefractiveIndexExit(float refractiveIndexOne);

    void setRefractiveIndexEnter(float refractiveIndexTwo);

private:
    float _distance;
    std::shared_ptr<Shape> _object;
    Tuple _point;
    Tuple _eye;
    Tuple _normal;
    Tuple _overPoint;
    Tuple _underPoint;

private:
    Tuple _reflection;
    bool _inside;
    float _refractiveIndexExit;
    float _refractiveIndexEnter;

    [[nodiscard]] float getShlick(
            const Tuple &eye, const Tuple &normal,
            float refractiveIndexExit, float refractiveIndexEnter) const;
};

#endif //RAYTRACERCHALLENGE_INTERSECTIONCOMPUTATIONS_H
