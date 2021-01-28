//
// Created by SILENT on 28/01/2021.
//

#include "IntersectionResult.h"
#include "Intersection.h"

IntersectionResult::IntersectionResult() {

}

IntersectionResult::IntersectionResult(std::initializer_list<Intersection> intersections) :
        _intersections(intersections) {

}

unsigned int IntersectionResult::getCount() const {
    return _intersections.size();
}

Intersection IntersectionResult::get(const unsigned int index) const {
    return _intersections[index];
}

std::optional<Intersection> IntersectionResult::getHit() const {
    if (_intersections.empty()) {
        return std::nullopt;
    }

    int index = -1;
    float min = std::numeric_limits<float>::max();

    for (unsigned int i = 0; i < _intersections.size(); ++i) {
        if (_intersections[i].getDistance() < min && _intersections[i].getDistance() >= 0) {
            min = _intersections[i].getDistance();
            index = i;
        }
    }

    if (index == -1)
        return std::nullopt;
    else {
        return _intersections[index];
    }
}