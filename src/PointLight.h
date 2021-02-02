//
// Created by SILENT on 29/01/2021.
//

#ifndef RAYTRACERCHALLENGE_POINTLIGHT_H
#define RAYTRACERCHALLENGE_POINTLIGHT_H

#include "Color.h"
#include "Tuple.h"

class PointLight {
public:
    PointLight() = default;

    PointLight(const Tuple &position, const Color &intensity);

    bool operator!=(const PointLight &other) const;

    bool operator==(const PointLight &other) const;

    [[nodiscard]] Color getIntensity() const;

    [[nodiscard]] Tuple getPosition() const;

private:
    Tuple _position;
    Color _intensity;
};


#endif //RAYTRACERCHALLENGE_POINTLIGHT_H
