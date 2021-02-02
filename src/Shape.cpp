//
// Created by SILENT on 02/02/2021.
//

#include "Shape.h"

#include "Ray.h"
#include "IntersectionResult.h"

Shape::Shape() :
        _transform(Mat4::identity()),
        _material() {
}

Shape::Shape(const Mat4 &transform) : _transform(transform), _material() {
}

Shape::Shape(const Material &material) : _transform(Mat4::identity()), _material(material) {
}

Shape::Shape(const Mat4 &transform, const Material &material) :
        _transform(transform), _material(material) {
}

bool Shape::operator==(const Shape &other) const {
    return _transform == other._transform && _material == other._material;
}

Mat4 Shape::getTransform() const {
    return _transform;
}

IntersectionResult Shape::getIntersectionResult(const Ray &ray) {
    _savedRay = getTransform().inversed() * ray;

    return getIntersectionResultImplementation(_savedRay.value());
}

void Shape::setTransform(const Mat4 &transform) {
    _transform = transform;
}

Tuple Shape::getNormal(const Tuple &point) {
    const auto objectPoint = _transform.inversed() * point;
    const auto objectNormal = getNormalImplementation(objectPoint);
    auto worldNormal = _transform.inversed().transposed() * objectNormal;
    worldNormal.set<3>(0.0f);
    return worldNormal.getNormalized();
}

Material Shape::getMaterial() const {
    return _material;
}

void Shape::setMaterialAmbient(float value) {
    _material.setAmbient(value);
}

Ray Shape::getSavedRay() const {
    return _savedRay.value();
}

void Shape::setMaterial(const Material &material) {
    _material = material;
}
