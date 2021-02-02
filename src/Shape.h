//
// Created by SILENT on 02/02/2021.
//

#ifndef RAYTRACER_SHAPE_H
#define RAYTRACER_SHAPE_H

#include "Matrix.h"
#include "Material.h"
#include "Ray.h"

class IntersectionResult;

class Shape : public std::enable_shared_from_this<Shape> {
public:
    Shape();

    explicit Shape(const Mat4 &transform);

    explicit Shape(const Material &other);

    Shape(const Mat4 &transform, const Material &material);

    virtual ~Shape() = default;

    bool operator==(const Shape &other) const;

    [[nodiscard]] Mat4 getTransform() const;

    void setTransform(const Mat4 &transform);

    [[nodiscard]] Tuple getNormal(const Tuple &point);

    [[nodiscard]] IntersectionResult getIntersectionResult(const Ray &ray);

    [[nodiscard]] Material getMaterial() const;

    void setMaterial(const Material &material);

    void setMaterialAmbient(float value);

    [[nodiscard]] Ray getSavedRay() const;

private:
    Mat4 _transform;
    Material _material;
    std::optional<Ray> _savedRay;

    [[nodiscard]] virtual Tuple
    getNormalImplementation(const Tuple &localPoint) = 0;

    [[nodiscard]] virtual IntersectionResult
    getIntersectionResultImplementation(const Ray &localRay) = 0;
};


#endif //RAYTRACER_SHAPE_H
