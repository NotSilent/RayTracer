//
// Created by SILENT on 26/01/2021.
//

#ifndef RAYTRACERCHALLENGE_SPHERE_H
#define RAYTRACERCHALLENGE_SPHERE_H

#include "Intersection.h"
#include "Matrix.h"

class Ray;

class IntersectionResult;

class Sphere {
public:
    Sphere();

    Sphere(const Mat4 &other);

    bool operator==(const Sphere &other) const;

    [[nodiscard]] Mat4 getTransform() const;

    void setTransform(const Mat4 &transform);

    [[nodiscard]] IntersectionResult getIntersectionResult(const Ray &ray) const;

private:
    Mat4 _transform;
};


#endif //RAYTRACERCHALLENGE_SPHERE_H
