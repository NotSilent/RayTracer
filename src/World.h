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

    [[nodiscard]] uint32_t getObjectCount() const;

    [[nodiscard]] PointLight getLight() const;

    [[nodiscard]] std::shared_ptr<Shape> getObject(uint32_t index) const;

    void setLight(const PointLight &light);

    void setObjectMaterialAmbient(uint32_t index, float value);

    void addObject(std::shared_ptr<Shape> object);

    [[nodiscard]] bool containsObject(const Shape &object) const;

    [[nodiscard]] IntersectionResult getIntersectionResult(const Ray &ray);

    [[nodiscard]] Color getShadeHit(const IntersectionComputations &comps);

    [[nodiscard]] Color getColor(const Ray &ray);

    [[nodiscard]] bool isInShadow(const Tuple &point);

    static World createDefaultWorld();

private:
    PointLight _light;
    std::vector<std::shared_ptr<Shape>> _objects;
};


#endif //RAYTRACERCHALLENGE_WORLD_H
