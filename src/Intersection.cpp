//
// Created by SILENT on 28/01/2021.
//

#include <sstream>
#include <utility>
#include "Intersection.h"
#include "IntersectionComputations.h"
#include "Ray.h"

float Intersection::getDistance() const {
    return _distance;
}

std::shared_ptr<Shape> Intersection::getObject() const {
    return _object;
}

Intersection::Intersection(float distance, std::shared_ptr<Shape> object) :
        _distance(distance), _object(std::move(object)) {
}

bool Intersection::operator==(const Intersection &other) const {
    return getDistance() == other.getDistance() &&
           getObject() == other.getObject();
}

bool Intersection::operator<(const Intersection &other) const {
    return getDistance() < other.getDistance();
}


std::ostream &operator<<(std::ostream &os, const Intersection &value) {
    std::stringstream ss;

    ss << "{" << value.getDistance() << "}";

    os << ss.str();

    return os;
}

IntersectionComputations Intersection::getComputations(const Ray &ray) const {
    const auto position = ray.getPosition(getDistance());

    return IntersectionComputations(
            getDistance(),
            _object,
            position,
            -ray.getDirection(),
            _object->getNormal(position));
}
