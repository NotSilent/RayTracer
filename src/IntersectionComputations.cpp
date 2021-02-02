//
// Created by SILENT on 31/01/2021.
//

#include <memory>
#include "IntersectionComputations.h"

IntersectionComputations::IntersectionComputations(
        float distance, std::shared_ptr<Shape> object,
        Tuple point, Tuple eye, Tuple normal) :
        _distance(distance),
        _object(object),
        _point(point),
        _eye(eye),
        _normal(normal),
        _inside(false) {
    if (Tuple::dot(getNormal(), getEye()) < 0.0f) {
        _normal = -getNormal();
        _inside = true;
    }

    //TODO: Figure out good epsilon
    _overPoint = _point + _normal * std::numeric_limits<float>::epsilon() * 10000.0f;
}

float IntersectionComputations::getDistance() const {
    return _distance;
}

std::shared_ptr<Shape> IntersectionComputations::getObject() const {
    return _object;
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
