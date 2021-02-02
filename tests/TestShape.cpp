//
// Created by SILENT on 02/02/2021.
//

#include "TestShape.h"
#include "IntersectionResult.h"
#include "Ray.h"

TestShape::TestShape() : Shape() {}

TestShape::TestShape(const Mat4 &transform) : Shape(transform) {
}

TestShape::TestShape(const Material &other) : Shape(other) {
}


Tuple TestShape::getNormalImplementation([[maybe_unused]] const Tuple &localPoint) {
    return {};
}

IntersectionResult TestShape::getIntersectionResultImplementation(
        [[maybe_unused]] const Ray &localRay) {
    return {};
}