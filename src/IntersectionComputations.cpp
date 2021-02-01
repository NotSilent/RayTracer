//
// Created by SILENT on 31/01/2021.
//

#include "IntersectionComputations.h"

IntersectionComputations::IntersectionComputations(
        float distance, Sphere object, Tuple point, Tuple eye, Tuple normal) :
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
}

float IntersectionComputations::getDistance() const {
    return _distance;
}

Sphere IntersectionComputations::getObject() const {
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