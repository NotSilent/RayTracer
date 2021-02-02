//
// Created by SILENT on 29/01/2021.
//

#include <Tuple.h>
#include <Color.h>
#include <PointLight.h>
#include <Material.h>
#include <Sphere.h>
#include <Shape.h>
#include "catch.hpp"
#include "TestShape.h"

TEST_CASE("A point light has a position and intensity") {
    const Color intensity(1.0f, 1.0f, 1.0f);
    const auto position = Tuple::point(0.0f, 0.0f, 0.0f);
    const PointLight light(position, intensity);

    REQUIRE(light.getPosition() == position);
    REQUIRE(light.getIntensity() == intensity);
}

TEST_CASE("The default material") {
    const Material m;

    REQUIRE(m.getColor() == Color(1.0f, 1.0f, 1.0f));
    REQUIRE(m.getAmbient() == 0.1f);
    REQUIRE(m.getDiffuse() == 0.9f);
    REQUIRE(m.getSpecular() == 0.9f);
    REQUIRE(m.getShininess() == 200.0f);
}

TEST_CASE("A sphere has a default material") {
    const auto s = std::make_shared<TestShape>();
    const auto m = s->getMaterial();

    REQUIRE(m == Material());
}

TEST_CASE("Assigning a material") {
    auto s = std::make_shared<TestShape>();
    Material m;
    m.setAmbient(1.0f);
    s->setMaterial(m);

    REQUIRE(m == s->getMaterial());
}

TEST_CASE("Lighting with the eye between the light and the surface") {
    const Material m;
    const auto position = Tuple::point(0.0f, 0.0f, 0.0f);
    const auto eyeVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const auto normalVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const PointLight light(
            Tuple::point(0.0f, 0.0f, -10.0f),
            Color(1.0f, 1.0f, 1.0f));
    const auto result = m.lightning(light, position, eyeVector, normalVector, false);

    REQUIRE(result == Color(1.9f, 1.9f, 1.9f));
}

TEST_CASE("Lighting with the eye between light and surface, eye offset 45°") {
    float angle = FMath::sqrt(2.0f) / 2.0f;
    const Material m;
    const auto position = Tuple::point(0.0f, 0.0f, 0.0f);
    const auto eyeVector = Tuple::vector(0.0f, angle, -angle);
    const auto normalVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const PointLight light(
            Tuple::point(0.0f, 0.0f, -10.0f),
            Color(1.0f, 1.0f, 1.0f));
    const auto result = m.lightning(light, position, eyeVector, normalVector, false);

    REQUIRE(result == Color(1.0f, 1.0f, 1.0f));
}

TEST_CASE("Lighting with eye opposite surface, light offset 45°") {
    const Material m;
    const auto position = Tuple::point(0.0f, 0.0f, 0.0f);
    const auto eyeVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const auto normalVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const PointLight light(
            Tuple::point(0.0f, 10.0f, -10.0f),
            Color(1.0f, 1.0f, 1.0f));
    const auto result = m.lightning(light, position, eyeVector, normalVector, false);

    REQUIRE(result == Color(0.7364f, 0.7364f, 0.7364f));
}

TEST_CASE("Lighting with eye in the path of the reflection vector") {
    float angle = FMath::sqrt(2.0f) / 2.0f;
    const Material m;
    const auto position = Tuple::point(0.0f, 0.0f, 0.0f);
    const auto eyeVector = Tuple::vector(0.0f, -angle, -angle);
    const auto normalVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const PointLight light(
            Tuple::point(0.0f, 10.0f, -10.0f),
            Color(1.0f, 1.0f, 1.0f));
    const auto result = m.lightning(light, position, eyeVector, normalVector, false);

    REQUIRE(result == Color(1.6364f, 1.6364f, 1.6364f));
}

TEST_CASE("Lighting with the light behind the surface") {
    const Material m;
    const auto position = Tuple::point(0.0f, 0.0f, 0.0f);
    const auto eyeVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const auto normalVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const PointLight light(
            Tuple::point(0.0f, 10.0f, 10.0f),
            Color(1.0f, 1.0f, 1.0f));
    const auto result = m.lightning(light, position, eyeVector, normalVector, false);

    REQUIRE(result == Color(0.1f, 0.1f, 0.1f));
}

TEST_CASE("") {
    const Material m;
    const auto position = Tuple::point(0.0f, 0.0f, 0.0f);
    const auto eye = Tuple::vector(0.0f, 0.0f, -1.0f);
    const auto normal = Tuple::vector(0.0f, 0.0f, -1.0f);
    const PointLight light(Tuple::point(0.0f, 0.0f, -10.0f),
                           Color(1.0f, 1.0f, 1.0f));
    const bool isInShadow = true;
    const auto result = m.lightning(light, position, eye, normal, isInShadow);

    REQUIRE(result == Color(0.1f, 0.1f, 0.1f));
}