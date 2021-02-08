//
// Created by SILENT on 28/01/2021.
//

#include <sstream>
#include <utility>
#include "Intersection.h"
#include "IntersectionComputations.h"

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

//TODO: Make this static and take intersection as parameter
IntersectionComputations Intersection::getComputations(const Ray &ray) const {
    const auto position = ray.getPosition(getDistance());
    const auto normal = _object->getNormal(position);

    return IntersectionComputations(
            getDistance(),
            _object,
            position,
            -ray.getDirection(),
            normal,
            ray.getDirection().getReflected(normal));
}

IntersectionComputations
Intersection::getComputations(
        const Ray &ray, const std::vector<Intersection> &intersections) const {
    float n1 = 0.0f;
    float n2 = 0.0f;

    std::vector<std::shared_ptr<Shape>> container;

    for (auto &intersection : intersections) {
        bool isHit = *this == intersection;
        if (isHit) {
            if (container.empty()) {
                n1 = 1.0f;
            } else {
                n1 = (container.end() - 1)->get()->getMaterial().getRefractiveIndex();
            }
        }

        auto iter = std::find(container.begin(),
                              container.end(),
                              intersection.getObject());

        if (iter != container.end()) {
            container.erase(iter);
        } else {
            container.push_back(intersection.getObject());
        }

        if (isHit) {
            if (container.empty()) {
                n2 = 1.0f;
            } else {
                n2 = (container.end() - 1)->get()->getMaterial().getRefractiveIndex();
            }

            break;
        }
    }

    auto comps = getComputations(ray);
    comps.setRefractiveIndexExit(n1);
    comps.setRefractiveIndexEnter(n2);

    return comps;
}
