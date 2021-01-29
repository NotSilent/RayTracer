//
// Created by SILENT on 26/01/2021.
//

#ifndef RAYTRACERCHALLENGE_SPHERE_H
#define RAYTRACERCHALLENGE_SPHERE_H

#include "Intersection.h"
#include "Matrix.h"

class Ray;

class IntersectionResult;

class Material;

class Sphere {
public:
    Sphere();

    explicit Sphere(const Mat4 &other);

    bool operator==(const Sphere &other) const;

    [[nodiscard]] Mat4 getTransform() const;

    void setTransform(const Mat4 &transform);

    [[nodiscard]] Tuple getNormalAt(const Tuple &point) const;

    [[nodiscard]] IntersectionResult getIntersectionResult(const Ray &ray) const;

    [[nodiscard]] std::shared_ptr<Material> getMaterial() const;

private:
    Mat4 _transform;

    std::shared_ptr<Material> _material;
};


#endif //RAYTRACERCHALLENGE_SPHERE_H
