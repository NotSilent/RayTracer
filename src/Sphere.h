//
// Created by SILENT on 26/01/2021.
//

#ifndef RAYTRACERCHALLENGE_SPHERE_H
#define RAYTRACERCHALLENGE_SPHERE_H

#include "Shape.h"

class Sphere : public Shape {
public:
    Sphere();

    explicit Sphere(const Mat4 &transform);

    explicit Sphere(const Material &other);

    Sphere(const Mat4 &transform, const Material &material);

    [[nodiscard]] static Sphere createGlass();

private:
    [[nodiscard]] Tuple
    getNormalImplementation(const Tuple &localPoint) override;

    [[nodiscard]] IntersectionResult
    getIntersectionResultImplementation(const Ray &localRay) override;
};

#endif //RAYTRACERCHALLENGE_SPHERE_H
