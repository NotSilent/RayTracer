//
// Created by SILENT on 29/01/2021.
//

#ifndef RAYTRACERCHALLENGE_POINTLIGHT_H
#define RAYTRACERCHALLENGE_POINTLIGHT_H

#include "Color.h"
#include "Tuple.h"

class PointLight {
public:
    PointLight(const Tuple &position, const Color &intensity);

    [[nodiscard]] Color getIntensity() const;

    [[nodiscard]] Tuple getPosition() const;

private:
    Color _intensity;
    Tuple _position;
};


#endif //RAYTRACERCHALLENGE_POINTLIGHT_H
