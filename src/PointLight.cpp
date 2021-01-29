//
// Created by SILENT on 29/01/2021.
//

#include "PointLight.h"

PointLight::PointLight(const Tuple &position, const Color &intensity) :
        _position(position), _intensity(intensity) {
}

Color PointLight::getIntensity() const {
    return _intensity;
}

Tuple PointLight::getPosition() const {
    return _position;
}
