//
// Created by SILENT on 29/01/2021.
//

#ifndef RAYTRACERCHALLENGE_WORLD_H
#define RAYTRACERCHALLENGE_WORLD_H

#include <vector>
#include "Sphere.h"
#include "PointLight.h"

class IntersectionResult;

class Ray;

class Color;

class IntersectionComputations;

class World {
public:
    World() = default;

    [[nodiscard]] uint32_t getLightCount() const;

    [[nodiscard]] uint32_t getObjectCount() const;

    [[nodiscard]] PointLight getLight(uint32_t index) const;

    [[nodiscard]] Sphere getObject(uint32_t index) const;

    void setLight(uint32_t index, const PointLight &light);

    void setObjectMaterialAmbient(uint32_t index, float value);

    void addLight(const PointLight &light);

    void addObject(const Sphere &object);

    [[nodiscard]] bool containsLight(const PointLight &light) const;

    [[nodiscard]] bool containsObject(const Sphere &object) const;

    [[nodiscard]] IntersectionResult getIntersectionResult(const Ray &ray) const;

    [[nodiscard]] Color getShadeHit(const IntersectionComputations &comps) const;

    [[nodiscard]] Color getColor(const Ray &ray) const;

    [[nodiscard]] bool isInShadow(const Tuple &point) const;

    static World createDefaultWorld();

private:
    std::vector<PointLight> _lights;
    std::vector<Sphere> _objects;
};


#endif //RAYTRACERCHALLENGE_WORLD_H
