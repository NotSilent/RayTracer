//
// Created by SILENT on 26/01/2021.
//

#include <Tuple.h>
#include <Ray.h>
#include <Sphere.h>
#include <Matrix.h>
#include <Shape.h>
#include "catch.hpp"
#include "Intersection.h"
#include "IntersectionResult.h"
#include "TestShape.h"

TEST_CASE("Creating and querying a ray") {
    const auto origin = Tuple::point(1.0f, 2.0f, 3.0f);
    const auto direction = Tuple::vector(4.0f, 5.0f, 6.0f);
    const Ray ray(origin, direction);

    REQUIRE(origin == ray.getOrigin());
    REQUIRE(direction == ray.getDirection());
}

TEST_CASE("Computing a point from a distance") {
    const Ray ray(Tuple::point(2.0f, 3.0f, 4.0f),
                  Tuple::vector(1.0f, 0.0f, 0.0f));

    REQUIRE(Tuple::point(2.0f, 3.0f, 4.0f) == ray.getPosition(0.0f));
    REQUIRE(Tuple::point(3.0f, 3.0f, 4.0f) == ray.getPosition(1.0f));
    REQUIRE(Tuple::point(1.0f, 3.0f, 4.0f) == ray.getPosition(-1.0f));
    REQUIRE(Tuple::point(4.5f, 3.0f, 4.0f) == ray.getPosition(2.5f));
}

TEST_CASE("A ray intersects a sphere at two points") {
    const Ray ray(Tuple::point(0.0f, 0.0f, -5.0f),
                  Tuple::vector(0.0f, 0.0f, 1.0f));
    auto sphere = std::make_shared<Sphere>();
    const auto intersects = sphere->getIntersectionResult(ray);

    REQUIRE(intersects.getCount() == 2);
    REQUIRE(intersects.get(0).getDistance() == 4.0f);
    REQUIRE(intersects.get(1).getDistance() == 6.0f);
}

TEST_CASE("A ray intersects a sphere at a tangent") {
    const Ray ray(Tuple::point(0.0f, 1.0f, -5.0f),
                  Tuple::vector(0.0f, 0.0f, 1.0f));
    auto sphere = std::make_shared<Sphere>();
    const auto intersects = sphere->getIntersectionResult(ray);

    REQUIRE(intersects.getCount() == 2);
    REQUIRE(intersects.get(0).getDistance() == 5.0f);
    REQUIRE(intersects.get(1).getDistance() == 5.0f);
}

TEST_CASE("A ray misses a sphere") {
    const Ray ray(Tuple::point(0.0f, 2.0f, -5.0f),
                  Tuple::vector(0.0f, 0.0f, 1.0f));
    auto sphere = std::make_shared<Sphere>();
    const auto intersects = sphere->getIntersectionResult(ray);

    REQUIRE(intersects.getCount() == 0);
}

TEST_CASE("A ray originates inside a sphere") {
    const Ray ray(Tuple::point(0.0f, 0.0f, 0.0f),
                  Tuple::vector(0.0f, 0.0f, 1.0f));
    auto sphere = std::make_shared<Sphere>();
    const auto intersects = sphere->getIntersectionResult(ray);

    REQUIRE(intersects.getCount() == 2);
    REQUIRE(intersects.get(0).getDistance() == -1.0f);
    REQUIRE(intersects.get(1).getDistance() == 1.0f);
}

TEST_CASE("A sphere is behind a ray") {
    const Ray ray(Tuple::point(0.0f, 0.0f, 5.0f),
                  Tuple::vector(0.0f, 0.0f, 1.0f));
    auto sphere = std::make_shared<Sphere>();
    const auto intersects = sphere->getIntersectionResult(ray);

    REQUIRE(intersects.getCount() == 2);
    REQUIRE(intersects.get(0).getDistance() == -6.0f);
    REQUIRE(intersects.get(1).getDistance() == -4.00f);
}

TEST_CASE("An intersection encapsulates t and object") {
    const auto s = std::make_shared<Sphere>();
    const Intersection i(3.5f, s);

    REQUIRE(i.getDistance() == 3.5f);
    REQUIRE(i.getObject() == s);
}

TEST_CASE("Aggregating intersections") {
    const auto s = std::make_shared<Sphere>();
    const Intersection i1(1.0f, s);
    const Intersection i2(2.0f, s);

    const IntersectionResult ir{i1, i2};

    REQUIRE(ir.getCount() == 2);
    REQUIRE(ir.get(0).getDistance() == 1.0f);
    REQUIRE(ir.get(1).getDistance() == 2.0f);
}

TEST_CASE("Intersect sets the object on the intersection") {
    const Ray r(Tuple::point(0.0f, 0.0f, 5.0f),
                Tuple::vector(0.0f, 0.0f, 1.0f));
    const auto s = std::make_shared<Sphere>();
    const auto ir = s->getIntersectionResult(r);

    REQUIRE(ir.getCount() == 2);
    REQUIRE(ir.get(0).getObject() == s);
    REQUIRE(ir.get(1).getObject() == s);
}

TEST_CASE("The hit, when all intersections have positive t") {
    const auto s = std::make_shared<Sphere>();
    const Intersection i1(1.0f, s);
    const Intersection i2(2.0f, s);
    const IntersectionResult ir{i2, i1};
    const auto hit = ir.getHit();

    REQUIRE(hit.value() == i1);
}

TEST_CASE("The hit, when some intersections have negative t") {
    const auto s = std::make_shared<Sphere>();
    const Intersection i1(-1.0f, s);
    const Intersection i2(1.0f, s);
    const IntersectionResult ir{i2, i1};
    const auto hit = ir.getHit();

    REQUIRE(hit.value() == i2);
}

TEST_CASE("The hit, when all intersections have negative t") {
    const auto s = std::make_shared<Sphere>();
    const Intersection i1(-2.0f, s);
    const Intersection i2(-1.0f, s);
    const IntersectionResult ir{i2, i1};
    const auto hit = ir.getHit();

    REQUIRE(hit.has_value() == false);
}

TEST_CASE("The hit is always the lowest non-negative intersection") {
    const auto s = std::make_shared<Sphere>();
    const Intersection i1(5.0f, s);
    const Intersection i2(7.0f, s);
    const Intersection i3(-3.0f, s);
    const Intersection i4(2.0f, s);
    const IntersectionResult ir{i1, i2, i3, i4};
    const auto hit = ir.getHit();

    REQUIRE(hit.value() == i4);
}

TEST_CASE("Translating a ray") {
    const Ray r(Tuple::point(1.0f, 2.0f, 3.0f),
                Tuple::vector(0.0f, 1.0f, 0.0f));
    const auto m = Mat4::translation(3.0f, 4.0f, 5.0f);
    const auto r2 = m * r;

    REQUIRE(r2.getOrigin() == Tuple::point(4.0f, 6.0f, 8.0f));
    REQUIRE(r2.getDirection() == Tuple::vector(0.0f, 1.0f, 0.0f));
}

TEST_CASE("Scaling a ray") {
    const Ray r(Tuple::point(1.0f, 2.0f, 3.0f),
                Tuple::vector(0.0f, 1.0f, 0.0f));
    const auto m = Mat4::scaling(2.0f, 3.0f, 4.0f);
    const auto r2 = m * r;

    REQUIRE(r2.getOrigin() == Tuple::point(2.0f, 6.0f, 12.0f));
    REQUIRE(r2.getDirection() == Tuple::vector(0.0f, 3.0f, 0.0f));
}

TEST_CASE("The default transformation") {
    const TestShape s;

    REQUIRE(s.getTransform() == Mat4::identity());
}

TEST_CASE("Assigning a transformation") {
    TestShape s;
    const auto transform = Mat4::translation(2.0f, 3.0f, 4.0f);
    s.setTransform(transform);

    REQUIRE(s.getTransform() == transform);
}

TEST_CASE("Intersecting a scaled shape with a ray") {
    const Ray r(Tuple::point(0.0f, 0.0f, -5.0f),
                Tuple::vector(0.0f, 0.0f, 1.0f));
    const auto s = std::make_shared<TestShape>(
            Mat4::scaling(2.0f, 2.0f, 2.0f));
    const auto ir = s->getIntersectionResult(r);

    REQUIRE(s->getSavedRay().getOrigin() == Tuple::point(0.0f, 0.0f, -2.5f));
    REQUIRE(s->getSavedRay().getDirection() == Tuple::vector(0.0f, 0.0f, 0.5f));
}

TEST_CASE("Intersecting a translated shape with a ray") {
    const Ray r(Tuple::point(0.0f, 0.0f, -5.0f),
                Tuple::vector(0.0f, 0.0f, 1.0f));
    const auto s = std::make_shared<TestShape>(
            Mat4::translation(5.0f, 0.0f, 0.0f));
    const auto ir = s->getIntersectionResult(r);

    REQUIRE(s->getSavedRay().getOrigin() == Tuple::point(-5.0f, 0.0f, -5.0f));
    REQUIRE(s->getSavedRay().getDirection() == Tuple::vector(0.0f, 0.0f, 1.0f));
}