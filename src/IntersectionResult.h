//
// Created by SILENT on 28/01/2021.
//

#ifndef RAYTRACERCHALLENGE_INTERSECTIONRESULT_H
#define RAYTRACERCHALLENGE_INTERSECTIONRESULT_H

#include <initializer_list>
#include <optional>
#include <vector>

#include "Intersection.h"

class IntersectionResult {
public:
    IntersectionResult();

    IntersectionResult(std::initializer_list<Intersection> intersections);

    [[nodiscard]] std::optional<Intersection> getHit() const;

    [[nodiscard]] unsigned int getCount() const;

    [[nodiscard]] Intersection get(unsigned int index) const;

    void add(IntersectionResult &&other);

private:
    std::vector<Intersection> _intersections;
};

#endif //RAYTRACERCHALLENGE_INTERSECTIONRESULT_H
