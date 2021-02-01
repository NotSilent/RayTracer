//
// Created by SILENT on 29/01/2021.
//

#ifndef RAYTRACERCHALLENGE_MATERIAL_H
#define RAYTRACERCHALLENGE_MATERIAL_H


#include "Color.h"

class PointLight;

class Material {
public:
    Material();

    Material(const Color &color, float ambient, float diffuse, float specular, float shininess);

    [[nodiscard]] Color getColor() const;

    [[nodiscard]] float getAmbient() const;

    [[nodiscard]] float getDiffuse() const;

    [[nodiscard]] float getSpecular() const;

    [[nodiscard]] float getShininess() const;

    bool operator!=(const Material &other) const;

    bool operator==(const Material &other) const;

    [[nodiscard]] Color lightning(
            const PointLight &light,
            const Tuple &point, const Tuple &eyeVector, const Tuple &normalVector,
            bool isInShadow) const;

    void setAmbient(float value);

private:
    Color _color;
    float _ambient;
    float _diffuse;
    float _specular;
    float _shininess;
};


#endif //RAYTRACERCHALLENGE_MATERIAL_H
