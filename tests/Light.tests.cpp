//
// Created by SILENT on 29/01/2021.
//

#include <Tuple.h>
#include <Color.h>
#include <PointLight.h>
#include <Material.h>
#include <Sphere.h>
#include "catch.hpp"

TEST_CASE("A point light has a position and intensity") {
    const Color intensity(1.0f, 1.0f, 1.0f);
    const auto position = Tuple::point(0.0f, 0.0f, 0.0f);
    const PointLight light(position, intensity);

    REQUIRE(light.getPosition() == position);
    REQUIRE(light.getIntensity() == intensity);
}

TEST_CASE("The default material") {
    const auto m = Material::getDefaultMaterial();

    REQUIRE(m->getColor() == Color(1.0f, 1.0f, 1.0f));
    REQUIRE(m->getAmbient() == 0.1f);
    REQUIRE(m->getDiffuse() == 0.9f);
    REQUIRE(m->getSpecular() == 0.9f);
    REQUIRE(m->getShininess() == 200.0f);
}

TEST_CASE("A sphere has a default material") {
    const Sphere s;
    const auto m = s.getMaterial();

    REQUIRE(m == Material::getDefaultMaterial());
}

TEST_CASE("Lighting with the eye between the light and the surface") {
    const auto m = Material::getDefaultMaterial();
    const auto position = Tuple::point(0.0f, 0.0f, 0.0f);
    const auto eyeVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const auto normalVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const PointLight light(
            Tuple::point(0.0f, 0.0f, -10.0f),
            Color(1.0f, 1.0f, 1.0f));
    const auto result = m->lightning(light, position, eyeVector, normalVector);

    REQUIRE(result == Color(1.9f, 1.9f, 1.9f));
}

TEST_CASE("Lighting with the eye between light and surface, eye offset 45°") {
    float angle = FMath::sqrt(2.0f) / 2.0f;
    const auto m = Material::getDefaultMaterial();
    const auto position = Tuple::point(0.0f, 0.0f, 0.0f);
    const auto eyeVector = Tuple::vector(0.0f, angle, -angle);
    const auto normalVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const PointLight light(
            Tuple::point(0.0f, 0.0f, -10.0f),
            Color(1.0f, 1.0f, 1.0f));
    const auto result = m->lightning(light, position, eyeVector, normalVector);

    REQUIRE(result == Color(1.0f, 1.0f, 1.0f));
}

TEST_CASE("Lighting with eye opposite surface, light offset 45°") {
    const auto m = Material::getDefaultMaterial();
    const auto position = Tuple::point(0.0f, 0.0f, 0.0f);
    const auto eyeVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const auto normalVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const PointLight light(
            Tuple::point(0.0f, 10.0f, -10.0f),
            Color(1.0f, 1.0f, 1.0f));
    const auto result = m->lightning(light, position, eyeVector, normalVector);

    REQUIRE(result == Color(0.7364f, 0.7364f, 0.7364f));
}

TEST_CASE("Lighting with eye in the path of the reflection vector") {
    float angle = FMath::sqrt(2.0f) / 2.0f;
    const auto m = Material::getDefaultMaterial();
    const auto position = Tuple::point(0.0f, 0.0f, 0.0f);
    const auto eyeVector = Tuple::vector(0.0f, -angle, -angle);
    const auto normalVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const PointLight light(
            Tuple::point(0.0f, 10.0f, -10.0f),
            Color(1.0f, 1.0f, 1.0f));
    const auto result = m->lightning(light, position, eyeVector, normalVector);

    REQUIRE(result == Color(1.6364f, 1.6364f, 1.6364f));
}

TEST_CASE("Lighting with the light behind the surface") {
    const auto m = Material::getDefaultMaterial();
    const auto position = Tuple::point(0.0f, 0.0f, 0.0f);
    const auto eyeVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const auto normalVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const PointLight light(
            Tuple::point(0.0f, 10.0f, 10.0f),
            Color(1.0f, 1.0f, 1.0f));
    const auto result = m->lightning(light, position, eyeVector, normalVector);

    REQUIRE(result == Color(0.1f, 0.1f, 0.1f));
}
