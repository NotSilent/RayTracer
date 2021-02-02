//
// Created by SILENT on 29/01/2021.
//

#include "World.h"

#include <memory>
#include "IntersectionResult.h"
#include "Ray.h"
#include "IntersectionComputations.h"

uint32_t World::getObjectCount() const {
    return _objects.size();
}

PointLight World::getLight() const {
    return _light;
}

std::shared_ptr<Shape> World::getObject(uint32_t index) const {
    return _objects[index];
}

void World::setLight(const PointLight &light) {
    _light = light;
}

World World::createDefaultWorld() {
    World w;

    w.setLight(PointLight(
            Tuple::point(-10.0f, 10.0f, -10.0f),
            Color(1.0f, 1.0f, 1.0f)));

    w.addObject(std::make_shared<Sphere>(Material(
            Color(0.8f, 1.0f, 0.6f),
            0.1f, 0.7f, 0.2f, 200.0f)));

    w.addObject(std::make_shared<Sphere>(
            Mat4::scaling(0.5f, 0.5f, 0.5f)));

    return w;
}

void World::addObject(std::shared_ptr<Shape> object) {
    _objects.emplace_back(object);
}

bool World::containsObject(const Shape &object) const {
    auto it = std::find_if(_objects.begin(), _objects.end(),
                           [&](std::shared_ptr<Shape> const &current) {
                               return *current == object;
                           });

    return it != _objects.end();
}

IntersectionResult World::getIntersectionResult(const Ray &ray) {
    IntersectionResult results;

    for (auto &object : _objects) {
        auto ir = object->getIntersectionResult(ray);
        results.add(std::move(ir));
    }

    return results;
}

Color World::getShadeHit(const IntersectionComputations &comps) {
    Color color;

//    for (const auto light : _lights) {
    const auto inShadow = isInShadow(comps.getOverPoint());
    color = color + comps.getObject()->getMaterial().lightning(
            getLight(), comps.getPoint(), comps.getEye(), comps.getNormal(), inShadow);
//    }

//    color = comps.getObject().getMaterial().lightning(
//            getLight(0), comps.getPoint(), comps.getEye(), comps.getNormal());

    return color;
}

Color World::getColor(const Ray &ray) {
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
    _objects[index]->setMaterialAmbient(value);
}

bool World::isInShadow(const Tuple &point) {
    const auto direction = getLight().getPosition() - point;
    const auto distance = direction.getMagnitude();
    const Ray ray(point, direction.getNormalized());
    const auto ir = getIntersectionResult(ray);
    if (ir.getHit().has_value() && ir.getHit().value().getDistance() < distance) {
        return true;
    }

    return false;
}
