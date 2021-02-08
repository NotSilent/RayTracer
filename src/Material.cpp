//
// Created by SILENT on 29/01/2021.
//

#include "Material.h"

#include <utility>
#include "PointLight.h"

Material::Material() :
        _color(1.0f, 1.0f, 1.0f),
        _ambient(0.1f), _diffuse(0.9f), _specular(0.9f),
        _shininess(200.0f), _reflectivity(0.0f),
        _transparency(0.0f), _refractiveIndex(1.0f) {
}

Material::Material(const Color &color, float ambient, float diffuse, float specular,
                   float shininess, float reflectivity,
                   float transparency, float refractiveIndex) :
        _color(color),
        _ambient(ambient),
        _diffuse(diffuse),
        _specular(specular),
        _shininess(shininess),
        _reflectivity(reflectivity),
        _transparency(transparency),
        _refractiveIndex(refractiveIndex) {
}

Color Material::getColor() const {
    return _color;
}

float Material::getAmbient() const {
    return _ambient;
}

float Material::getDiffuse() const {
    return _diffuse;
}

float Material::getSpecular() const {
    return _specular;
}

float Material::getShininess() const {
    return _shininess;
}

float Material::getReflectivity() const {
    return _reflectivity;
}

bool Material::operator!=(const Material &other) const {
    return _color != other._color ||
           _ambient != other._ambient ||
           _diffuse != other._diffuse ||
           _specular != other._specular ||
           _shininess != other._shininess;
}

bool Material::operator==(const Material &other) const {
    return !(*this != other);
}

Color Material::lightning(const PointLight &light, std::shared_ptr<Shape> object,
                          const Tuple &point, const Tuple &eyeVector, const Tuple &normalVector,
                          bool isInShadow) const {
    Color effectiveColor;
    if (_pattern != nullptr) {
        effectiveColor = _pattern->getColor(object, point) * light.getIntensity();
    } else {
        effectiveColor = getColor() * light.getIntensity();
    }

    const auto lightVector = (light.getPosition() - point).getNormalized();
    const auto ambient = effectiveColor * getAmbient();
    const auto lightDotNormal = Tuple::dot(lightVector, normalVector);

    if (isInShadow || lightDotNormal < 0.0f) {
        return ambient;
    } else {
        const auto diffuse = effectiveColor * getDiffuse() * lightDotNormal;
        const auto reflectVector = (-lightVector).getReflected(normalVector);
        const auto reflectDotEye = Tuple::dot(reflectVector, eyeVector);

        if (reflectDotEye <= 0.0f) {
            return ambient + diffuse;
        } else {
            const float factor = pow(reflectDotEye, getShininess());
            const auto specular = light.getIntensity() * getSpecular() * factor;

            return ambient + diffuse + specular;
        }
    }
}

void Material::setColor(const Color &value) {
    _color = value;
}

void Material::setAmbient(float value) {
    _ambient = value;
}

void Material::setReflectivity(float value) {
    _reflectivity = value;
}

std::shared_ptr<Pattern> Material::getPattern() const {
    return _pattern;
}

void Material::setPattern(std::shared_ptr<Pattern> pattern) {
    _pattern = std::move(pattern);
}

float Material::getTransparency() const {
    return _transparency;
}

float Material::getRefractiveIndex() const {
    return _refractiveIndex;
}

void Material::setTransparency(float value) {
    _transparency = value;
}

void Material::setRefractiveIndex(float value) {
    _refractiveIndex = value;
}
