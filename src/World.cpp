//
// Created by SILENT on 29/01/2021.
//

#include "World.h"
#include "IntersectionResult.h"
#include "Ray.h"
#include "IntersectionComputations.h"

uint32_t World::getObjectCount() const {
    return _objects.size();
}

uint32_t World::getLightCount() const {
    return _lights.size();
}

PointLight World::getLight(uint32_t index) const {
    return _lights[index];
}

Sphere World::getObject(uint32_t index) const {
    return _objects[index];
}

void World::setLight(uint32_t index, const PointLight &light) {
    _lights[index] = light;
}

World World::createDefaultWorld() {
    World w;

    w.addLight(PointLight(
            Tuple::point(-10.0f, 10.0f, -10.0f),
            Color(1.0f, 1.0f, 1.0f)));

    w.addObject(Sphere(Material(
            Color(0.8f, 1.0f, 0.6f),
            0.1f, 0.7f, 0.2f, 200.0f)));

    w.addObject(Sphere(Mat4::scaling(0.5f, 0.5f, 0.5f)));

    return w;
}

void World::addLight(const PointLight &light) {
    _lights.emplace_back(light);
}

void World::addObject(const Sphere &object) {
    _objects.emplace_back(object);
}

bool World::containsLight(const PointLight &light) const {
    return std::find(_lights.begin(), _lights.end(), light) != _lights.end();
}

bool World::containsObject(const Sphere &object) const {
    return std::find(_objects.begin(), _objects.end(), object) != _objects.end();
}

IntersectionResult World::getIntersectionResult(const Ray &ray) const {
    IntersectionResult results;

    for (const auto &object : _objects) {
        auto ir = object.getIntersectionResult(ray);
        results.add(std::move(ir));
    }

    return results;
}

Color World::getShadeHit(const IntersectionComputations &comps) const {
    Color color;

    for (const auto light : _lights) {
        color = color + comps.getObject().getMaterial().lightning(
                light, comps.getPoint(), comps.getEye(), comps.getNormal());
    }

//    color = comps.getObject().getMaterial().lightning(
//            getLight(0), comps.getPoint(), comps.getEye(), comps.getNormal());

    return color;
}

Color World::getColor(const Ray &ray) const {
    const auto ir = getIntersectionResult(ray);
    const auto hit = ir.getHit();

    if (hit.has_value()) {
        const auto comps = hit.value().getComputations(ray);
        return getShadeHit(comps);
    } else {
        return Color();
    }
}

void World::setObjectMaterialAmbient(uint32_t index, float value) {
    _objects[index].setMaterialAmbient(value);
}
