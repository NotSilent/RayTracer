//
// Created by SILENT on 28/01/2021.
//

#ifndef RAYTRACERCHALLENGE_INTERSECTION_H
#define RAYTRACERCHALLENGE_INTERSECTION_H

#include <ostream>
#include "Sphere.h"

class IntersectionComputations;

class Intersection {
public:
    Intersection(float distance, std::shared_ptr<Shape> object);

    bool operator==(const Intersection &other) const;

    bool operator<(const Intersection &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Intersection &value);

    [[nodiscard]] float getDistance() const;

    [[nodiscard]] std::shared_ptr<Shape> getObject() const;

    [[nodiscard]] IntersectionComputations getComputations(const Ray &ray) const;

private:
    float _distance;
    std::shared_ptr<Shape> _object;
};

#endif //RAYTRACERCHALLENGE_INTERSECTION_H
