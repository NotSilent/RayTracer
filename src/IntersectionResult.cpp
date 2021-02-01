//
// Created by SILENT on 28/01/2021.
//

#include "IntersectionResult.h"
#include "Intersection.h"
#include <algorithm>

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

    bool found = false;
    uint32_t index = 0;
    float min = std::numeric_limits<float>::max();

    for (uint32_t i = 0; i < _intersections.size(); ++i) {
        if (_intersections[i].getDistance() < min && _intersections[i].getDistance() >= 0) {
            min = _intersections[i].getDistance();
            index = i;

            found = true;
        }
    }

    if (found)
        return _intersections[index];
    else {
        return std::nullopt;
    }
}

void IntersectionResult::add(IntersectionResult &&other) {
    _intersections.insert(_intersections.end(),
                          other._intersections.begin(),
                          other._intersections.end());

    std::sort(_intersections.begin(), _intersections.end());
}
