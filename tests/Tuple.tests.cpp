//
// Created by SILENT on 21/01/2021.
//
#include "catch.hpp"
#include "FMath.h"
#include "Tuple.h"

TEST_CASE("A tuple with w == 1.0f is a point") {
    const auto point = Tuple(0.0f, 0.0f, 0.0f, 1.0f);
    REQUIRE(point.isPoint());
    REQUIRE(!point.isVector());
}

TEST_CASE("A tuple with w == 0.0f is a vector") {
    const auto point = Tuple(0.0f, 0.0f, 0.0f, 0.0f);
    REQUIRE(point.isVector());
    REQUIRE(!point.isPoint());
}

TEST_CASE("Tuple::point() creates tuple with w == 1.0f") {
    const auto point = Tuple::point(0.0f, 0.0f, 0.0f);
    const auto w = point.getW();
    REQUIRE(FMath::approximately(w, 1.0f));
}

TEST_CASE("Tuple::vector() creates tuple with w == 0.0f") {
    const auto point = Tuple::vector(0.0f, 0.0f, 0.0f);
    const auto w = point.getW();
    REQUIRE(FMath::approximately(w, 0.0f));
}

TEST_CASE("Adding two tuples") {
    const Tuple t1(3.0f, -2.0f, 5.0f, 1.0f);
    const Tuple t2(-2.0f, 3.0f, 1.0f, 0.0f);
    const Tuple sum(1.0f, 1.0f, 6.0, 1.0f);
    REQUIRE(sum == (t1 + t2));
}

TEST_CASE("Subtracting two points") {
    const auto t1 = Tuple::point(3.0, 2.0, 1.0); // w == 1.0
    const auto t2 = Tuple::point(5.0, 6.0, 7.0); // w == 1.0
    const Tuple sub(-2.0, -4.0, -6.0, 0.0f);        // w == 0.0
    REQUIRE(sub == (t1 - t2));
}

TEST_CASE("Subtracting a vector from a point") {
    const auto p = Tuple::point(3.0, 2.0, 1.0);  // w == 1.0
    const auto v = Tuple::vector(5.0, 6.0, 7.0); // w == 0.0
    const Tuple sub(-2.0, -4.0, -6.0, 1.0f);        // w == 1.0
    REQUIRE(sub == (p - v));
}

TEST_CASE("Subtracting two vectors") {
    const auto t1 = Tuple::vector(3.0, 2.0, 1.0); // w == 0.0
    const auto t2 = Tuple::vector(5.0, 6.0, 7.0); // w == 0.0
    const Tuple sub(-2.0, -4.0, -6.0, 0.0f);         // w == 0.0
    REQUIRE(sub == (t1 - t2));
}

TEST_CASE("Subtracting a vector from the zero vector") {
    const auto t1 = Tuple::vector(0.0, 0.0, 0.0);  // w == 0.0
    const auto t2 = Tuple::vector(1.0, -2.0, 3.0); // w == 0.0
    const Tuple sub(-1.0, 2.0, -3.0, 0.0f);          // w == 0.0
    REQUIRE(sub == (t1 - t2));
}

TEST_CASE("Negating a tuple") {
    const Tuple t(1.0f, -2.0f, 3.0f, -4.0f);
    const Tuple neg(-1.0f, 2.0f, -3.0f, 4.0f);
    REQUIRE(neg == -t);
}

TEST_CASE("Multiplying a tuple by a scalar") {
    const Tuple t(1.0f, -2.0f, 3.0f, -4.0f);
    const Tuple mul(3.5f, -7.0f, 10.5f, -14.0f);
    REQUIRE(mul == (t * 3.5f));
}

TEST_CASE("Multiplying a tuple by a fraction") {
    const Tuple t(1.0f, -2.0f, 3.0f, -4.0f);
    const Tuple mul(0.5f, -1.0f, 1.5f, -2.0f);
    REQUIRE(mul == (t * 0.5f));
}

TEST_CASE("Dividing a tuple by a scalar") {
    const Tuple t(1.0f, -2.0f, 3.0f, -4.0f);
    const Tuple div(0.5f, -1.0f, 1.5f, -2.0f);
    REQUIRE(div == (t / 2));
}

TEST_CASE("Computing the magnitude of vector(1, 0, 0)") {
    const auto v = Tuple::vector(1.0f, 0.0f, 0.0f);
    const float magnitude = 1.0f;
    REQUIRE(magnitude == v.magnitude());
}

TEST_CASE("Computing the magnitude of vector(0, 1, 0)") {
    const auto v = Tuple::vector(0.0f, 1.0f, 0.0f);
    const float magnitude = 1.0f;
    REQUIRE(magnitude == v.magnitude());
}

TEST_CASE("Computing the magnitude of vector(0, 0, 1)") {
    const auto v = Tuple::vector(0.0f, 0.0f, 1.0f);
    const float magnitude = 1.0f;
    REQUIRE(magnitude == v.magnitude());
}

TEST_CASE("Computing the magnitude of vector(1, 2, 3)") {
    const auto v = Tuple::vector(1.0f, 2.0f, 3.0f);
    const float magnitude = sqrt(14.0f);
    REQUIRE(magnitude == v.magnitude());
}

TEST_CASE("Computing the magnitude of vector(-1, -2, -3)") {
    const auto v = Tuple::vector(-1.0f, -2.0f, -3.0f);
    const float magnitude = sqrt(14.0f);
    REQUIRE(magnitude == v.magnitude());
}

TEST_CASE("Normalizing vector(4, 0, 0) gives (1, 0, 0)") {
    auto v = Tuple::vector(4.0f, 0.0f, 0.0f);
    v.normalize();
    const auto normalized = Tuple::vector(1.0f, 0.0f, 0.0f);
    REQUIRE(v == normalized);
}

TEST_CASE("Normalizing vector(1, 2, 3)") {
    auto v = Tuple::vector(1.0f, 2.0f, 3.0f);
    v.normalize();
    float dividend = sqrt(14.0f);
    const auto normalized = Tuple::vector(1.0f / dividend, 2.0f / dividend, 3.0f / dividend);
    REQUIRE(v == normalized);
}

TEST_CASE("The magnitude of a normalized vector") {
    auto v = Tuple::vector(1.0f, 2.0f, 3.0f);
    v.normalize();
    const float magnitude = 1.0f;
    REQUIRE(FMath::approximately(v.magnitude(), magnitude));
}

TEST_CASE("The dot product of two tuples") {
    const auto v1 = Tuple::vector(1.0f, 2.0f, 3.0f);
    const auto v2 = Tuple::vector(2.0f, 3.0f, 4.0f);
    const float dot = 20.0f;
    REQUIRE(Tuple::dot(v1, v2) == dot);
}

TEST_CASE("The cross product of two vectors") {
    const auto v1 = Tuple::vector(1.0f, 2.0f, 3.0f);
    const auto v2 = Tuple::vector(2.0f, 3.0f, 4.0f);
    const auto cross = Tuple::vector(-1.0f, 2.0f, -1.0f);
    REQUIRE(cross == Tuple::cross(v1, v2));
}