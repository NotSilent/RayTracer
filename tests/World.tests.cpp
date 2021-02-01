//
// Created by SILENT on 29/01/2021.
//

#include <World.h>
#include <PointLight.h>
#include <Sphere.h>
#include <Ray.h>
#include <IntersectionComputations.h>
#include "catch.hpp"
#include "Material.h"
#include "IntersectionResult.h"

TEST_CASE("Creating a world") {
    const World w;

    REQUIRE(w.getObjectCount() == 0);
    REQUIRE(w.getLightCount() == 0);
}

TEST_CASE("The default world") {
    const Material material(
            Color(0.8f, 1.0f, 0.6f),
            0.1f, 0.7f, 0.2f, 200.0f);
    const PointLight p(
            Tuple::point(-10.0f, 10.0f, -10.0f),
            Color(1.0f, 1.0f, 1.0f));
    const Sphere s1(material);
    const Sphere s2(Mat4::scaling(0.5f, 0.5f, 0.5f));
    const auto w = World::createDefaultWorld();

    REQUIRE(w.containsLight(p) == true);
    REQUIRE(w.containsObject(s1) == true);
    REQUIRE(w.containsObject(s2) == true);
}

TEST_CASE("Intersect a world with a ray") {
    const auto w = World::createDefaultWorld();
    const Ray r(
            Tuple::point(0.0f, 0.0f, -5.0f),
            Tuple::vector(0.0f, 0.0f, 1.0f));
    const auto ir = w.getIntersectionResult(r);

    REQUIRE(ir.getCount() == 4);
    REQUIRE(ir.get(0).getDistance() == 4.0f);
    REQUIRE(ir.get(1).getDistance() == 4.5f);
    REQUIRE(ir.get(2).getDistance() == 5.5f);
    REQUIRE(ir.get(3).getDistance() == 6.0f);
}

TEST_CASE("Precomputing the state of an intersection") {
    const Ray r(Tuple::point(0.0f, 0.0f, -5.0f),
                Tuple::vector(0.0f, 0.0f, 1.0f));
    Sphere shape;
    const Intersection i(4.0f, shape);
    const auto comps = i.getComputations(r);

    REQUIRE(comps.getDistance() == i.getDistance());
    REQUIRE(comps.getPoint() == Tuple::point(0.0f, 0.0f, -1.0f));
    REQUIRE(comps.getEye() == Tuple::vector(0.0f, 0.0f, -1.0f));
    REQUIRE(comps.getNormal() == Tuple::vector(0.0f, 0.0f, -1.0f));
}

TEST_CASE("The hit, when an intersection occurs on the outside") {
    const Ray r(Tuple::point(0.0f, 0.0f, -5.0f),
                Tuple::vector(0.0f, 0.0f, 1.0f));
    const Sphere sphere;
    const Intersection i(4.0f, sphere);
    const auto comps = i.getComputations(r);

    REQUIRE(comps.isInside() == false);
}

TEST_CASE("The hit, when an intersection occurs on the inside") {
    const Ray r(Tuple::point(0.0f, 0.0f, 0.0f),
                Tuple::vector(0.0f, 0.0f, 1.0f));
    const Sphere sphere;
    const Intersection i(1.0f, sphere);
    const auto comps = i.getComputations(r);

    REQUIRE(comps.getPoint() == Tuple::point(0.0f, 0.0f, 1.0f));
    REQUIRE(comps.getEye() == Tuple::vector(0.0f, 0.0f, -1.0f));
    REQUIRE(comps.isInside() == true);
    REQUIRE(comps.getNormal() == Tuple::vector(0.0f, 0.0f, -1.0f));
}

TEST_CASE("Shading an intersection") {
    const auto w = World::createDefaultWorld();
    const Ray r(Tuple::point(0.0f, 0.0f, -5.0f),
                Tuple::vector(0.0f, 0.0f, 1.0f));
    const auto shape = w.getObject(0);
    const Intersection i(4.0f, shape);
    const auto comps = i.getComputations(r);
    const auto c = w.getShadeHit(comps);

    REQUIRE(c == Color(0.38066f, 0.47583f, 0.2855f));
}

TEST_CASE("Shading an intersection from the inside") {
    auto w = World::createDefaultWorld();
    w.setLight(0, PointLight(
            Tuple::point(0.0f, 0.25f, 0.0f),
            Color(1.0f, 1.0f, 1.0f)));
    const Ray r(Tuple::point(0.0f, 0.f, 0.0f),
                Tuple::vector(0.0f, 0.0f, 1.0f));
    const auto shape = w.getObject(1);
    const Intersection i(0.5f, shape);
    const auto comps = i.getComputations(r);
    const auto c = w.getShadeHit(comps);

    REQUIRE(c == Color(0.90498f, 0.90498f, 0.90498f));
}

TEST_CASE("The color when a ray misses") {
    const auto w = World::createDefaultWorld();
    const Ray r(Tuple::point(0.0f, 0.f, -5.0f),
                Tuple::vector(0.0f, 1.0f, 0.0f));
    const auto c = w.getColor(r);

    REQUIRE(c == Color(0.0f, 0.0f, 0.0f));
}

TEST_CASE("The color when a ray hits") {
    const auto w = World::createDefaultWorld();
    const Ray r(Tuple::point(0.0f, 0.f, -5.0f),
                Tuple::vector(0.0f, 0.0f, 1.0f));
    const auto c = w.getColor(r);

    REQUIRE(c == Color(0.38066f, 0.47583f, 0.2855f));
}

TEST_CASE("The color with an intersection behind the ray") {
    auto w = World::createDefaultWorld();
    w.setObjectMaterialAmbient(0, 1.0f);
    w.setObjectMaterialAmbient(1, 1.0f);
    const auto inner = w.getObject(1);
    const Ray r(Tuple::point(0.0f, 0.f, 0.75f),
                Tuple::vector(0.0f, 0.0f, -1.0f));
    const auto c = w.getColor(r);

    REQUIRE(c == inner.getMaterial().getColor());
}

TEST_CASE("The transformation matrix for the default orientation") {
    const auto from = Tuple::point(0.0f, 0.0f, 0.0f);
    const auto to = Tuple::point(0.0f, 0.0f, -1.0f);
    const auto up = Tuple::vector(0.0f, 1.0f, 0.0f);
    const auto t = Mat4::getViewTransform(from, to, up);

    REQUIRE(t == Mat4::identity());
}

TEST_CASE("A view transformation matrix looking in positive z direction") {
    const auto from = Tuple::point(0.0f, 0.0f, 0.0f);
    const auto to = Tuple::point(0.0f, 0.0f, 1.0f);
    const auto up = Tuple::vector(0.0f, 1.0f, 0.0f);
    const auto t = Mat4::getViewTransform(from, to, up);

    REQUIRE(t == Mat4::scaling(-1.0f, 1.0f, -1.0f));
}

TEST_CASE("The view transformation moves the world") {
    const auto from = Tuple::point(0.0f, 0.0f, 8.0f);
    const auto to = Tuple::point(0.0f, 0.0f, 0.0f);
    const auto up = Tuple::vector(0.0f, 1.0f, 0.0f);
    const auto t = Mat4::getViewTransform(from, to, up);

    REQUIRE(t == Mat4::translation(0.0f, 0.0f, -8.0f));
}

TEST_CASE("An arbitrary view transformation") {
    const auto from = Tuple::point(1.0f, 3.0f, 2.0f);
    const auto to = Tuple::point(4.0f, -2.0f, 8.0f);
    const auto up = Tuple::vector(1.0f, 1.0f, 0.0f);
    const auto t = Mat4::getViewTransform(from, to, up);

    const Mat4 mat(-0.50709f, 0.50709f, 0.67612f, -2.36643f,
                   0.76772f, 0.60609f, 0.12122f, -2.82843f,
                   -0.35857f, 0.59761f, -0.71714f, 0.00000f,
                   0.00000f, 0.00000f, 0.00000f, 1.00000);

    REQUIRE(t == mat);
}

TEST_CASE("There is no shadow when nothing is collinear with point and light") {
    const auto w = World::createDefaultWorld();
    const auto p = Tuple::point(0.0f, 10.0f, 0.0f);

    REQUIRE(w.isInShadow(p) == false);
}

TEST_CASE("The shadow when an object is between the point and the light") {
    const auto w = World::createDefaultWorld();
    const auto p = Tuple::point(10.0f, -10.0f, 10.0f);

    REQUIRE(w.isInShadow(p) == true);
}

TEST_CASE("There is no shadow when an object is behind the light") {
    const auto w = World::createDefaultWorld();
    const auto p = Tuple::point(-20.0f, 20.0f, -20.0f);

    REQUIRE(w.isInShadow(p) == false);
}

TEST_CASE("There is no shadow when an object is behind the point") {
    const auto w = World::createDefaultWorld();
    const auto p = Tuple::point(-2.0f, 2.0f, -2.0f);

    REQUIRE(w.isInShadow(p) == false);
}

TEST_CASE("shade_hit() is given an intersection in shadow") {
    World w;
    w.addLight(PointLight(Tuple::point(0.0f, 0.0f, -10.f),
                          Color(1.0f, 1.0f, 1.0f)));
    const Sphere s1;
    const Sphere s2(Mat4::translation(0.0f, 0.0f, 10.0f));
    w.addObject(s1);
    w.addObject(s2);
    const Ray r(Tuple::point(0.0f, 0.0f, 5.0f),
                Tuple::vector(0.0f, 0.0f, 1.0f));
    const Intersection i(4.0f, s2);
    const IntersectionComputations comps = i.getComputations(r);
    const auto c = w.getShadeHit(comps);

    REQUIRE(c == Color(0.1f, 0.1f, 0.1f));
}

TEST_CASE("The hit should offset the point") {
    const Ray r(Tuple::point(0.0f, 0.0f, -5.0f),
                Tuple::vector(0.0f, 0.0f, 1.0f));
    const Sphere shape(Mat4::translation(0.0f, 0.0f, 1.0f));
    const Intersection i(5.0f, shape);
    const auto comps = i.getComputations(r);

    REQUIRE(comps.getOverPoint().getZ() < -std::numeric_limits<float>::epsilon() / 2);
    REQUIRE(comps.getPoint().getZ() > comps.getOverPoint().getZ());
}