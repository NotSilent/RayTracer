//
// Created by SILENT on 01/02/2021.
//

#include "catch.hpp"
#include "FMath.h"
#include "Matrix.h"
#include "Camera.h"
#include "Ray.h"
#include "World.h"
#include "Canvas.h"

TEST_CASE("Constructing a camera") {
    uint32_t hSize = 160;
    uint32_t vSize = 120;
    float fov = FMath::PI / 2.0f;
    const Camera c(hSize, vSize, fov);

    REQUIRE(c.getWidth() == 160);
    REQUIRE(c.getHeight() == 120);
    REQUIRE(c.getFOV() == FMath::PI / 2.0f);
    REQUIRE(c.getTransform() == Mat4::identity());
}

TEST_CASE("The pixel size for a horizontal canvas") {
    const Camera c(200, 125, FMath::PI / 2.0f);

    REQUIRE(c.getPixelSize() == 0.01f);
}

TEST_CASE("The pixel size for a vertical canvas") {
    const Camera c(125, 200, FMath::PI / 2.0f);

    REQUIRE(c.getPixelSize() == 0.01f);
}

TEST_CASE("Constructing a ray through the center of the canvas") {
    const Camera c(201, 101, FMath::PI / 2.0f);
    const auto r = c.getRay(100, 50);

    REQUIRE(r.getOrigin() == Tuple::point(0.0f, 0.0f, 0.0f));
    REQUIRE(r.getDirection() == Tuple::vector(0.0f, 0.0f, -1.0f));
}

TEST_CASE("Constructing a ray through a corner of the canvas") {
    const Camera c(201, 101, FMath::PI / 2.0f);
    const auto r = c.getRay(0, 0);

    REQUIRE(r.getOrigin() == Tuple::point(0.0f, 0.0f, 0.0f));
    REQUIRE(r.getDirection() == Tuple::vector(0.66519f, 0.33259f, -0.66851f));
}

TEST_CASE("Constructing a ray when the camera is transformed") {
    const auto transform = Mat4::rotation<Axis::Y>(FMath::PI / 4.0f) *
                           Mat4::translation(0.0f, -2.0f, 5.0f);
    const Camera c(201, 101, FMath::PI / 2.0f, transform);
    const auto r = c.getRay(100, 50);
    const auto result = FMath::sqrt(2.0f) / 2.0f;

    REQUIRE(r.getOrigin() == Tuple::point(0.0f, 2.0f, -5.0f));
    REQUIRE(r.getDirection() == Tuple::vector(result, 0.0f, -result));
}

TEST_CASE("Rendering a world with a camera") {
    auto w = World::createDefaultWorld();
    const auto m = Mat4::getViewTransform(
            Tuple::point(0.0f, 0.0f, -5.0f),
            Tuple::point(0.0f, 0.0f, 0.0f),
            Tuple::point(0.0f, 1.0f, 0.0f));
    const Camera c(11, 11, FMath::PI / 2.0f, m);
    const auto image = c.getRender(w);

    REQUIRE(image.getColor(5, 5) == Color(0.38066f, 0.47583f, 0.2855f));
}