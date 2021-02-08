//
// Created by SILENT on 29/01/2021.
//

#include <Tuple.h>
#include <Color.h>
#include <PointLight.h>
#include <Material.h>
#include <Sphere.h>
#include <Shape.h>
#include <Plane.h>
#include <Intersection.h>
#include <IntersectionComputations.h>
#include <World.h>
#include <IntersectionResult.h>
#include "catch.hpp"
#include "TestShape.h"
#include "FMath.h"

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
    auto s = std::make_shared<Sphere>();
    const Material m;
    const auto position = Tuple::point(0.0f, 0.0f, 0.0f);
    const auto eyeVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const auto normalVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const PointLight light(
            Tuple::point(0.0f, 0.0f, -10.0f),
            Color(1.0f, 1.0f, 1.0f));
    const auto result = m.lightning(light, s, position, eyeVector, normalVector, false);

    REQUIRE(result == Color(1.9f, 1.9f, 1.9f));
}

TEST_CASE("Lighting with the eye between light and surface, eye offset 45°") {
    auto s = std::make_shared<Sphere>();
    float angle = FMath::sqrt(2.0f) / 2.0f;
    const Material m;
    const auto position = Tuple::point(0.0f, 0.0f, 0.0f);
    const auto eyeVector = Tuple::vector(0.0f, angle, -angle);
    const auto normalVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const PointLight light(
            Tuple::point(0.0f, 0.0f, -10.0f),
            Color(1.0f, 1.0f, 1.0f));
    const auto result = m.lightning(light, s, position, eyeVector, normalVector, false);

    REQUIRE(result == Color(1.0f, 1.0f, 1.0f));
}

TEST_CASE("Lighting with eye opposite surface, light offset 45°") {
    auto s = std::make_shared<Sphere>();
    const Material m;
    const auto position = Tuple::point(0.0f, 0.0f, 0.0f);
    const auto eyeVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const auto normalVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const PointLight light(
            Tuple::point(0.0f, 10.0f, -10.0f),
            Color(1.0f, 1.0f, 1.0f));
    const auto result = m.lightning(light, s, position, eyeVector, normalVector, false);

    REQUIRE(result == Color(0.7364f, 0.7364f, 0.7364f));
}

TEST_CASE("Lighting with eye in the path of the reflection vector") {
    auto s = std::make_shared<Sphere>();
    float angle = FMath::sqrt(2.0f) / 2.0f;
    const Material m;
    const auto position = Tuple::point(0.0f, 0.0f, 0.0f);
    const auto eyeVector = Tuple::vector(0.0f, -angle, -angle);
    const auto normalVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const PointLight light(
            Tuple::point(0.0f, 10.0f, -10.0f),
            Color(1.0f, 1.0f, 1.0f));
    const auto result = m.lightning(light, s, position, eyeVector, normalVector, false);

    REQUIRE(result == Color(1.6364f, 1.6364f, 1.6364f));
}

TEST_CASE("Lighting with the light behind the surface") {
    auto s = std::make_shared<Sphere>();
    const Material m;
    const auto position = Tuple::point(0.0f, 0.0f, 0.0f);
    const auto eyeVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const auto normalVector = Tuple::vector(0.0f, 0.0f, -1.0f);
    const PointLight light(
            Tuple::point(0.0f, 10.0f, 10.0f),
            Color(1.0f, 1.0f, 1.0f));
    const auto result = m.lightning(light, s, position, eyeVector, normalVector, false);

    REQUIRE(result == Color(0.1f, 0.1f, 0.1f));
}

TEST_CASE("Reflectivity for the default material") {
    Material m;

    REQUIRE(m.getReflectivity() == 0.0f);
}

TEST_CASE("Precomputing the reflection vector") {
    const auto shape = std::make_shared<Plane>();
    float angle = FMath::sqrt(2.0f) / 2.0f;
    const Ray r(Tuple::point(0.0f, 1.0f, -1.0f),
                Tuple::vector(0.0f, -angle, angle));
    const Intersection i(FMath::sqrt(2.0f), shape);
    const auto comps = i.getComputations(r);

    REQUIRE(comps.getReflection() == Tuple::vector(0.0f, angle, angle));
}

TEST_CASE("The reflected color for a nonreflective material") {
    auto w = World::createDefaultWorld();
    const Ray r(Tuple::point(0.0f, 0.0f, 0.0f),
                Tuple::vector(0.0f, 0.0f, 1.0f));
    auto shape = w.getObject(1);
    shape->setMaterialAmbient(1.0f);
    const Intersection i(1.0f, shape);
    const auto comps = i.getComputations(r);
    const auto color = w.getReflectedColor(comps);

    REQUIRE(color == Color(0.0f, 0.0f, 0.0f));
}

TEST_CASE("The reflected color for a reflective material") {
    auto w = World::createDefaultWorld();
    auto shape = std::make_shared<Plane>(
            Mat4::translation(0.0f, -1.0f, 0.0f));
    shape->setMaterialReflectivity(0.5f);
    w.addObject(shape);
    float angle = FMath::sqrt(2.0f) / 2.0f;
    const Ray r(Tuple::point(0.0f, 0.0f, -3.0f),
                Tuple::vector(0.0f, -angle, angle));
    const Intersection i(FMath::sqrt(2.0f), shape);
    const auto comps = i.getComputations(r);
    const auto color = w.getReflectedColor(comps);

    REQUIRE(color == Color(0.19032f, 0.2379f, 0.14274f));
}

TEST_CASE("shade_hit() with a reflective material") {
    auto w = World::createDefaultWorld();
    auto shape = std::make_shared<Plane>(
            Mat4::translation(0.0f, -1.0f, 0.0f));
    shape->setMaterialReflectivity(0.5f);
    w.addObject(shape);
    float angle = FMath::sqrt(2.0f) / 2.0f;
    const Ray r(Tuple::point(0.0f, 0.0f, -3.0f),
                Tuple::vector(0.0f, -angle, angle));
    const Intersection i(FMath::sqrt(2.0f), shape);
    const auto comps = i.getComputations(r);
    const auto color = w.getShadeHit(comps);

    REQUIRE(color == Color(0.87677f, 0.92436f, 0.82918f));
}

TEST_CASE("color_at() with mutually reflective surfaces") {
    World w;
    w.setLight(PointLight(Tuple::point(0.0f, 0.0f, 0.0f),
                          Color(1.0f, 1.0f, 1.0f)));
    auto lower = std::make_shared<Plane>(
            Mat4::translation(0.0f, -1.0f, 0.0f));
    lower->setMaterialReflectivity(1.0f);
    w.addObject(lower);
    auto upper = std::make_shared<Plane>(
            Mat4::translation(0.0f, 1.0f, 0.0f));
    upper->setMaterialReflectivity(1.0f);
    w.addObject(upper);
    const Ray r(Tuple::point(0.0f, 0.0f, 0.0f),
                Tuple::vector(0.0f, 1.0f, 0.0f));

    REQUIRE_NOTHROW(w.getColor(r));
}

TEST_CASE("The reflected color at the maximum recursive depth") {
    auto w = World::createDefaultWorld();
    auto shape = std::make_shared<Plane>(
            Mat4::translation(0.0f, -1.0f, 0.0f));
    shape->setMaterialReflectivity(0.5f);
    w.addObject(shape);
    float angle = FMath::sqrt(2.0f) / 2.0f;
    const Ray r(Tuple::point(0.0f, 0.0f, -3.0f),
                Tuple::vector(0.0f, -angle, angle));
    const Intersection i(FMath::sqrt(2.0f), shape);
    const auto comps = i.getComputations(r);
    const auto color = w.getReflectedColor(comps, 0);

    REQUIRE(color == Color(0.0f, 0.0f, 0.0f));
}

TEST_CASE("Transparency and Refractive Index for the default material") {
    Material m;

    REQUIRE(m.getTransparency() == 0.0f);
    REQUIRE(m.getRefractiveIndex() == 1.0f);
}

TEST_CASE("A helper for producing a sphere with a glassy material") {
    const auto s = Sphere::createGlass();

    REQUIRE(s.getTransform() == Mat4::identity());
    REQUIRE(s.getMaterial().getTransparency() == 1.0f);
    REQUIRE(s.getMaterial().getRefractiveIndex() == 1.5f);
}

TEST_CASE("Finding n1 and n2 at various intersections") {
    auto a = std::make_shared<Sphere>(Sphere::createGlass());
    a->setTransform(Mat4::scaling(2.0f, 2.0f, 2.0f));
    a->setMaterialRefractiveIndex(1.5f);

    auto b = std::make_shared<Sphere>(Sphere::createGlass());
    b->setTransform(Mat4::translation(0.0f, 0.0f, -0.25f));
    b->setMaterialRefractiveIndex(2.0f);

    auto c = std::make_shared<Sphere>(Sphere::createGlass());
    c->setTransform(Mat4::translation(0.0f, 0.0f, 0.25f));
    c->setMaterialRefractiveIndex(2.5f);

    const Ray r(Tuple::point(0.0f, 0.0f, -4.0f),
                Tuple::vector(0.0f, 0.0f, 1.0f));

    std::vector<Intersection> intersections{
            {2.0f,  a},
            {2.75f, b},
            {3.25f, c},
            {4.75f, b},
            {5.25f, c},
            {6.0f,  a},
    };

    const auto c0 = intersections[0].getComputations(r, intersections);
    const auto c1 = intersections[1].getComputations(r, intersections);
    const auto c2 = intersections[2].getComputations(r, intersections);
    const auto c3 = intersections[3].getComputations(r, intersections);
    const auto c4 = intersections[4].getComputations(r, intersections);
    const auto c5 = intersections[5].getComputations(r, intersections);

    REQUIRE(c0.getRefractiveIndexExit() == 1.0f);
    REQUIRE(c0.getRefractiveIndexEnter() == 1.5f);
    REQUIRE(c1.getRefractiveIndexExit() == 1.5f);
    REQUIRE(c1.getRefractiveIndexEnter() == 2.0f);
    REQUIRE(c2.getRefractiveIndexExit() == 2.0f);
    REQUIRE(c2.getRefractiveIndexEnter() == 2.5f);
    REQUIRE(c3.getRefractiveIndexExit() == 2.5f);
    REQUIRE(c3.getRefractiveIndexEnter() == 2.5f);
    REQUIRE(c4.getRefractiveIndexExit() == 2.5f);
    REQUIRE(c4.getRefractiveIndexEnter() == 1.5f);
    REQUIRE(c5.getRefractiveIndexExit() == 1.5f);
    REQUIRE(c5.getRefractiveIndexEnter() == 1.0f);
}

TEST_CASE("The under point is offset below the surface") {
    const Ray r(0.0f, 0.0f, -5.0f,
                0.0f, 0.0f, 1.0f);
    auto shape = std::make_shared<Sphere>(Sphere::createGlass());
    shape->setTransform(Mat4::translation(0.0f, 0.0f, 1.0f));
    std::vector<Intersection> intersections{{5.0f, shape}};
    const auto comps = intersections[0].getComputations(r, intersections);

    REQUIRE(comps.getUnderPoint().getZ() > (FMath::EPSILON / 2.0f));
    REQUIRE(comps.getPoint().getZ() < comps.getUnderPoint().getZ());
}

TEST_CASE("The refracted color with an opaque surface") {
    auto w = World::createDefaultWorld();
    auto shape = w.getObject(0);
    Ray r(0.0f, 0.0f, -5.0f,
          0.0f, 0.0f, 1.0f);
    std::vector<Intersection> intersections{
            {4.0f, shape},
            {6.0f, shape},
    };
    auto comps = intersections[0].getComputations(r, intersections);
    auto color = w.getRefractedColor(comps, 5);

    REQUIRE(color == Color(0.0f, 0.0f, 0.0f));
}

TEST_CASE("The refracted color at the maximum recursive depth") {
    auto w = World::createDefaultWorld();
    auto shape = w.getObject(0);
    shape->setMaterialTransparency(1.0f);
    shape->setMaterialRefractiveIndex(1.5f);
    Ray r(0.0f, 0.0f, -5.0f,
          0.0f, 0.0f, 1.0f);
    std::vector<Intersection> intersections{
            {4.0f, shape},
            {6.0f, shape},
    };
    auto comps = intersections[0].getComputations(r, intersections);
    auto color = w.getRefractedColor(comps, 0);

    REQUIRE(color == Color(0.0f, 0.0f, 0.0f));
}

TEST_CASE("The refracted color under total internal reflection") {
    auto w = World::createDefaultWorld();
    auto shape = w.getObject(0);
    shape->setMaterialTransparency(1.0f);
    shape->setMaterialRefractiveIndex(1.5f);
    float angle = FMath::sqrt(2.0f) / 2.0f;
    Ray r(0.0f, 0.0f, angle,
          0.0f, 1.0f, 0.0f);
    std::vector<Intersection> intersections{
            {-angle, shape},
            {angle,  shape},
    };
    auto comps = intersections[1].getComputations(r, intersections);
    auto color = w.getRefractedColor(comps, 5);

    REQUIRE(color == Color(0.0f, 0.0f, 0.0f));
}

TEST_CASE("shade_hit() with a transparent material") {
    auto w = World::createDefaultWorld();
    auto floor = std::make_shared<Plane>(
            Mat4::translation(0.0f, -1.0f, 0.0f));
    floor->setMaterialTransparency(0.5f);
    floor->setMaterialRefractiveIndex(1.5f);
    w.addObject(floor);
    auto ball = std::make_shared<Sphere>(
            Mat4::translation(0.0f, -3.5f, -0.5f));
    ball->setMaterialColor(Color(1.0f, 0.0f, 0.0f));
    ball->setMaterialAmbient(0.5f);
    w.addObject(ball);
    float angle = FMath::sqrt(2.0f) / 2.0f;
    Ray r(0.0f, 0.0f, -3.0f,
          0.0f, -angle, angle);
    std::vector<Intersection> intersections{{FMath::sqrt(2.0f), floor}};
    auto comps = intersections[0].getComputations(r, intersections);
    auto color = w.getShadeHit(comps, 5);

    REQUIRE(color == Color(0.93642f, 0.68642f, 0.68642f));
};

TEST_CASE("The Schlick approximation under total internal reflection") {
    auto shape = std::make_shared<Sphere>(Sphere::createGlass());
    float angle = FMath::sqrt(2.0f) / 2.0f;
    Ray r(0.0f, 0.0f, angle,
          0.0f, 1.0f, 0.0f);
    std::vector<Intersection> intersections{
            {-angle, shape},
            {angle,  shape},
    };
    auto comps = intersections[1].getComputations(r, intersections);
    float reflectance = comps.getReflectance();

    REQUIRE(FMath::isOne(reflectance) == true);
}

TEST_CASE("The Schlick approximation with a perpendicular viewing angle") {
    auto shape = std::make_shared<Sphere>(Sphere::createGlass());
    Ray r(0.0f, 0.0f, 0.0f,
          0.0f, 1.0f, 0.0f);
    std::vector<Intersection> intersections{
            {-1, shape},
            {1,  shape},
    };
    auto comps = intersections[1].getComputations(r, intersections);
    float reflectance = comps.getReflectance();

    REQUIRE(FMath::approximately(reflectance, 0.04f) == true);
}

TEST_CASE("The Schlick approximation with small angle and n2 > n1") {
    auto shape = std::make_shared<Sphere>(Sphere::createGlass());
    Ray r(0.0f, 0.99f, -2.0f,
          0.0f, 0.0f, 1.0f);
    std::vector<Intersection> intersections{{1.8589f, shape}};
    auto comps = intersections[0].getComputations(r, intersections);
    float reflectance = comps.getReflectance();

    REQUIRE(FMath::approximately(reflectance, 0.48873f) == true);
}

TEST_CASE("shade_hit() with a reflective, transparent material") {
    auto w = World::createDefaultWorld();
    float angle = FMath::sqrt(2.0f) / 2.0f;
    Ray r(0.0f, 0.0f, -3.0f,
          0.0f, -angle, angle);
    auto floor = std::make_shared<Plane>(
            Mat4::translation(0.0f, -1.0f, 0.0f));
    floor->setMaterialTransparency(0.5f);
    floor->setMaterialRefractiveIndex(1.5f);
    floor->setMaterialReflectivity(0.5f);
    w.addObject(floor);
    auto ball = std::make_shared<Sphere>(
            Mat4::translation(0.0f, -3.5f, -0.5f));
    ball->setMaterialColor(Color(1.0f, 0.0f, 0.0f));
    ball->setMaterialAmbient(0.5f);
    w.addObject(ball);
    std::vector<Intersection> intersections{
            {FMath::sqrt(2.0f), floor}
    };
    auto comps = intersections[0].getComputations(r, intersections);
    auto color = w.getShadeHit(comps, 5);

    REQUIRE(color == Color(0.93391f, 0.69643f, 0.69243f));
};