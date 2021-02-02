//
// Created by SILENT on 02/02/2021.
//

#ifndef RAYTRACER_TESTSHAPE_H
#define RAYTRACER_TESTSHAPE_H

#include "Shape.h"

class TestShape : public Shape {
public:
    TestShape();

    explicit TestShape(const Mat4 &transform);

    explicit TestShape(const Material &other);

private:
    [[nodiscard]] virtual Tuple
    getNormalImplementation(const Tuple &localPoint) override;

    [[nodiscard]] virtual IntersectionResult
    getIntersectionResultImplementation(const Ray &localRay) override;
};


#endif //RAYTRACER_TESTSHAPE_H
