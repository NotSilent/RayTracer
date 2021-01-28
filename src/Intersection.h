//
// Created by SILENT on 28/01/2021.
//

#ifndef RAYTRACERCHALLENGE_INTERSECTION_H
#define RAYTRACERCHALLENGE_INTERSECTION_H

#include <ostream>

class Sphere;

class Intersection {
public:
    Intersection(float distance, const Sphere &object);

    bool operator==(const Intersection &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Intersection &value);

    [[nodiscard]] float getDistance() const;

    [[nodiscard]] Sphere getObject() const;

private:
    float _distance;
    const Sphere &_object;
};

#endif //RAYTRACERCHALLENGE_INTERSECTION_H
