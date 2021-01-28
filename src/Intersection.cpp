//
// Created by SILENT on 28/01/2021.
//

#include <sstream>
#include "Intersection.h"
#include "Sphere.h"

float Intersection::getDistance() const {
    return _distance;
}

Sphere Intersection::getObject() const {
    return _object;
}

Intersection::Intersection(const float distance, const Sphere &object) :
        _distance(distance), _object(object) {
}

bool Intersection::operator==(const Intersection &other) const {
    return getDistance() == other.getDistance() &&
           getObject() == other.getObject();
}

std::ostream &operator<<(std::ostream &os, const Intersection &value) {
    std::stringstream ss;

    ss << "{" << value.getDistance() << "}";

    os << ss.str();

    return os;
}

