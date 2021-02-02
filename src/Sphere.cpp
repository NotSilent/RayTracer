//
// Created by SILENT on 26/01/2021.
//

#include "Sphere.h"
#include "IntersectionResult.h"
#include "Ray.h"

Sphere::Sphere() : Shape() {}

Sphere::Sphere(const Mat4 &transform) : Shape(transform) {
}

Sphere::Sphere(const Material &other) : Shape(other) {
}

Sphere::Sphere(const Mat4 &transform, const Material &material) :
        Shape(transform, material) {
}

Tuple Sphere::getNormalImplementation(const Tuple &localPoint) {
    return localPoint - Tuple::point(0.0f, 0.0f, 0.0f);
}

IntersectionResult Sphere::getIntersectionResultImplementation(const Ray &localRay) {
    const auto sphereToRay = localRay.getOrigin() - Tuple::point(0.0f, 0.0f, 0.0f);

    const auto a = Tuple::dot(localRay.getDirection(), localRay.getDirection());
    const auto b = 2.0f * Tuple::dot(localRay.getDirection(), sphereToRay);
    const auto c = Tuple::dot(sphereToRay, sphereToRay) - 1.0f;

    const float discriminant = (b * b) - (4 * a * c);

    if (discriminant < 0.0f) {
        return IntersectionResult();
    }

    float d1 = (-b - FMath::sqrt(discriminant)) / (2.0f * a);
    float d2 = (-b + FMath::sqrt(discriminant)) / (2.0f * a);

    const Intersection i1(d1, shared_from_this());
    const Intersection i2(d2, shared_from_this());

    if (d2 < d1) {
        return {i2, i1};
    }

    return {i1, i2};
}