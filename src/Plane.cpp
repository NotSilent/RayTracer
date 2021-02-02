//
// Created by SILENT on 02/02/2021.
//

#include "Plane.h"
#include "IntersectionResult.h"
#include "FMath.h"

Plane::Plane() : Shape() {}

Plane::Plane(const Mat4 &transform) : Shape(transform) {
}

Plane::Plane(const Material &other) : Shape(other) {
}

Plane::Plane(const Mat4 &transform, const Material &material) :
        Shape(transform, material) {
}

Tuple Plane::getNormalImplementation(const Tuple &localPoint) {
    return Tuple::vector(0.0f, 1.0f, 0.0f);
}

IntersectionResult Plane::getIntersectionResultImplementation(const Ray &localRay) {
    if (std::abs(localRay.getDirection().getY()) < std::numeric_limits<float>::epsilon() * 10000.0f) {
        return {};
    }

    float distance = -localRay.getOrigin().getY() / localRay.getDirection().getY();

    return {Intersection(distance, shared_from_this())};
}