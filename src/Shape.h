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

    explicit Shape(Material other);

    Shape(const Mat4 &transform, const Material &material);

    virtual ~Shape() = default;

    bool operator==(const Shape &other) const;

    [[nodiscard]] Mat4 getTransform() const;

    void setTransform(const Mat4 &transform);

    [[nodiscard]] Tuple getNormal(const Tuple &point);

    [[nodiscard]] IntersectionResult getIntersectionResult(const Ray &ray);

    [[nodiscard]] Material getMaterial() const;

    void setMaterial(const Material &material);

    void setMaterialColor(const Color &color);

    void setMaterialAmbient(float value);

    void setMaterialReflectivity(float value);

    void setMaterialRefractiveIndex(float value);

    void setMaterialTransparency(float value);

    [[nodiscard]] Ray getSavedRay() const;

private:
    Mat4 _transform;
    Material _material;
    std::optional<Ray> _savedRay; //TODO: remove and make everything const correct again

    [[nodiscard]] virtual Tuple
    getNormalImplementation(const Tuple &localPoint) = 0;

    [[nodiscard]] virtual IntersectionResult
    getIntersectionResultImplementation(const Ray &localRay) = 0;
};


#endif //RAYTRACER_SHAPE_H
