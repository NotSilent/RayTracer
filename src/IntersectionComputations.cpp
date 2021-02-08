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
        const Tuple &point, const Tuple &eye, const Tuple &normal, const Tuple &reflection) :
        _distance(distance),
        _object(std::move(object)),
        _point(point),
        _eye(eye),
        _normal(normal),
        _reflection(reflection),
        _inside(false),
        _refractiveIndexExit(1.0f),
        _refractiveIndexEnter(1.0f) {
    if (Tuple::dot(getNormal(), getEye()) < 0.0f) {
        _normal = -getNormal();
        _inside = true;
    }

    _overPoint = _point + _normal * FMath::EPSILON;
    _underPoint = _point - _normal * FMath::EPSILON;
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

Tuple IntersectionComputations::getReflection() const {
    return _reflection;
}


bool IntersectionComputations::isInside() const {
    return _inside;
}

Tuple IntersectionComputations::getOverPoint() const {
    return _overPoint;
}

Tuple IntersectionComputations::getUnderPoint() const {
    return _underPoint;
}

float IntersectionComputations::getRefractiveIndexExit() const {
    return _refractiveIndexExit;
}

float IntersectionComputations::getRefractiveIndexEnter() const {
    return _refractiveIndexEnter;
}

void IntersectionComputations::setRefractiveIndexExit(float value) {
    _refractiveIndexExit = value;
}

void IntersectionComputations::setRefractiveIndexEnter(float value) {
    _refractiveIndexEnter = value;
}

float IntersectionComputations::getReflectance() const {
    return getShlick(getEye(), getNormal(),
                     getRefractiveIndexExit(), getRefractiveIndexEnter());
}

float IntersectionComputations::getShlick(
        const Tuple &eye, const Tuple &normal,
        float refractiveIndexExit, float refractiveIndexEnter) const {
    float cos = Tuple::dot(eye, normal);

    if (refractiveIndexExit > refractiveIndexEnter) {
        float n = refractiveIndexExit / refractiveIndexEnter;
        float sin2T = (n * n) * (1.0f - (cos * cos));

        if (sin2T > 1.0f) {
            return 1.0f;
        }

        float cosT = FMath::sqrt(1.0f - sin2T);
        cos = cosT;
    }

    float argument = (refractiveIndexExit - refractiveIndexEnter) /
                     (refractiveIndexExit + refractiveIndexEnter);
    float r0 = argument * argument;

    return r0 + (1.0f - r0) * std::powf(1 - cos, 5);
}