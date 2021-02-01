//
// Created by SILENT on 26/01/2021.
//

#include "Sphere.h"

#include <utility>
#include "Ray.h"
#include "IntersectionResult.h"

Sphere::Sphere() :
        _transform(Mat4::identity()),
        _material() {
}

Sphere::Sphere(const Mat4 &transform) : _transform(transform), _material() {
}

Sphere::Sphere(const Material &material) : _transform(Mat4::identity()), _material(material) {
}

Sphere::Sphere(const Mat4 &transform, const Material &material) :
        _transform(transform), _material(material) {
}

bool Sphere::operator==(const Sphere &other) const {
    return _transform == other._transform;
}

Mat4 Sphere::getTransform() const {
    return _transform;
}

IntersectionResult Sphere::getIntersectionResult(const Ray &ray) const {
    const auto transformedRay = getTransform().inversed() * ray;

    const auto sphereToRay = transformedRay.getOrigin() - Tuple::point(0.0f, 0.0f, 0.0f);

    const auto a = Tuple::dot(transformedRay.getDirection(), transformedRay.getDirection());
    const auto b = 2.0f * Tuple::dot(transformedRay.getDirection(), sphereToRay);
    const auto c = Tuple::dot(sphereToRay, sphereToRay) - 1.0f;

    const float discriminant = (b * b) - (4 * a * c);

    if (discriminant < 0.0f) {
        return IntersectionResult();
    }

    float d1 = (-b - FMath::sqrt(discriminant)) / (2.0f * a);
    float d2 = (-b + FMath::sqrt(discriminant)) / (2.0f * a);

    const Intersection i1(d1, *this);
    const Intersection i2(d2, *this);

    if (d2 < d1) {
        return {i2, i1};
    }

    return {i1, i2};
}

void Sphere::setTransform(const Mat4 &transform) {
    _transform = transform;
}

Tuple Sphere::getNormalAt(const Tuple &point) const {
    const auto objectPoint = _transform.inversed() * point;
    const auto objectNormal = objectPoint - Tuple::point(0.0f, 0.0f, 0.0f);
    auto worldNormal = _transform.inversed().transposed() * objectNormal;
    worldNormal.set<3>(0.0f);
    return worldNormal.getNormalized();
}

Material Sphere::getMaterial() const {
    return _material;
}

void Sphere::setMaterialAmbient(float value) {
    _material.setAmbient(value);
}
