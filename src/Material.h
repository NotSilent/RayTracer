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

    [[nodiscard]] Color getColor() const;

    [[nodiscard]] float getAmbient() const;

    [[nodiscard]] float getDiffuse() const;

    [[nodiscard]] float getSpecular() const;

    [[nodiscard]] float getShininess() const;

    bool operator!=(const Material &other) const;

    bool operator==(const Material &other) const;

    static std::shared_ptr<Material> getDefaultMaterial();

    [[nodiscard]] Color lightning(
            const PointLight &light,
            const Tuple &point, const Tuple &eyeVector, const Tuple &normalVector) const;

private:
    Color _color;
    float _ambient;
    float _diffuse;
    float _specular;
    float _shininess;
};


#endif //RAYTRACERCHALLENGE_MATERIAL_H
