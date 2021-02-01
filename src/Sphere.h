//
// Created by SILENT on 26/01/2021.
//

#ifndef RAYTRACERCHALLENGE_SPHERE_H
#define RAYTRACERCHALLENGE_SPHERE_H

#include "Matrix.h"
#include "Material.h"

class Ray;

class IntersectionResult;

class Sphere {
public:
    Sphere();

    explicit Sphere(const Mat4 &transform);

    explicit Sphere(const Material &other);

    Sphere(const Mat4 &transform, const Material &material);

    bool operator==(const Sphere &other) const;

    [[nodiscard]] Mat4 getTransform() const;

    void setTransform(const Mat4 &transform);

    [[nodiscard]] Tuple getNormalAt(const Tuple &point) const;

    [[nodiscard]] IntersectionResult getIntersectionResult(const Ray &ray) const;

    [[nodiscard]] Material getMaterial() const;

    void setMaterialAmbient(float value);

private:
    Mat4 _transform;

    Material _material;
};

static_assert(std::is_trivially_copyable<Sphere>::value, "Sphere has to be trivially copyable!");

#endif //RAYTRACERCHALLENGE_SPHERE_H
