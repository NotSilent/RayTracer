//
// Created by SILENT on 31/01/2021.
//

#include <memory>
#include <utility>
#include "IntersectionComputations.h"
#include "FMath.h"
#include "Shape.h"

IntersectionComputations::IntersectionComputations(
        float distance, std::shared_ptr<Shape> object,
        Tuple point, Tuple eye, Tuple normal) :
        _distance(distance),
        _object(std::move(object)),
        _point(point),
        _eye(eye),
        _normal(normal),
        _inside(false) {
    if (Tuple::dot(getNormal(), getEye()) < 0.0f) {
        _normal = -getNormal();
        _inside = true;
    }

    _overPoint = _point + _normal * FMath::EPSILON;
}

float IntersectionComputations::getDistance() const {
    return _distance;
}

const Shape &IntersectionComputations::getObject() const {
    return *_object;
}


Tuple IntersectionComputations::getPoint() const {
    return _point;
}

Tuple IntersectionComputations::getEye() const {
    return _eye;
}

Tuple IntersectionComputations::getNormal() const {
    return _normal;
}

bool IntersectionComputations::isInside() const {
    return _inside;
}

Tuple IntersectionComputations::getOverPoint() const {
    return _overPoint;
}
