//
// Created by SILENT on 02/02/2021.
//

#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H

#include "Shape.h"

class Material;

class Tuple;

class IntersectionResult;

class Ray;

class Plane : public Shape {
public:
    Plane();

    explicit Plane(const Mat4 &transform);

    explicit Plane(const Material &other);

    Plane(const Mat4 &transform, const Material &material);

private:
    [[nodiscard]] Tuple
    getNormalImplementation(const Tuple &localPoint) override;

    [[nodiscard]] IntersectionResult
    getIntersectionResultImplementation(const Ray &localRay) override;
};


#endif //RAYTRACER_PLANE_H
