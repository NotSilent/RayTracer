//
// Created by SILENT on 02/02/2021.
//

#include <Color.h>
#include <StripePattern.h>
#include <Material.h>
#include <PointLight.h>
#include <Sphere.h>
#include <GradientPattern.h>
#include <RingPattern.h>
#include <CheckersPattern.h>
#include "catch.hpp"

static const Color BLACK = Color(0.0f, 0.0f, 0.0f);
static const Color WHITE = Color(1.0f, 1.0f, 1.0f);

static const auto sab = std::make_shared<StripePattern>(WHITE, BLACK);
static const auto gab = std::make_shared<GradientPattern>(WHITE, BLACK);
static const auto rab = std::make_shared<RingPattern>(WHITE, BLACK);
static const auto cab = std::make_shared<CheckersPattern>(WHITE, BLACK);

TEST_CASE("Creating a stripe pattern") {
    const StripePattern pattern(WHITE, BLACK);

    REQUIRE(pattern.getA() == WHITE);
    REQUIRE(pattern.getB() == BLACK);
}

TEST_CASE("A stripe pattern is constant in y") {
    const StripePattern pattern(WHITE, BLACK);

    REQUIRE(pattern.getPoint(Tuple::point(0.0f, 0.0f, 0.0f)) == WHITE);
    REQUIRE(pattern.getPoint(Tuple::point(0.0f, 1.0f, 0.0f)) == WHITE);
    REQUIRE(pattern.getPoint(Tuple::point(0.0f, 2.0f, 0.0f)) == WHITE);
}

TEST_CASE("A stripe pattern is constant in z") {
    const StripePattern pattern(WHITE, BLACK);

    REQUIRE(pattern.getPoint(Tuple::point(0.0f, 0.0f, 0.0f)) == WHITE);
    REQUIRE(pattern.getPoint(Tuple::point(0.0f, 0.0f, 1.0f)) == WHITE);
    REQUIRE(pattern.getPoint(Tuple::point(0.0f, 0.0f, 2.0f)) == WHITE);
}

TEST_CASE("A stripe pattern alternates in x") {
    const StripePattern pattern(WHITE, BLACK);

    REQUIRE(pattern.getPoint(Tuple::point(0.0f, 0.0f, 0.0f)) == WHITE);
    REQUIRE(pattern.getPoint(Tuple::point(0.9f, 0.0f, 0.0f)) == WHITE);
    REQUIRE(pattern.getPoint(Tuple::point(1.0f, 0.0f, 0.0f)) == BLACK);
    REQUIRE(pattern.getPoint(Tuple::point(-0.1f, 0.0f, 0.0f)) == BLACK);
    REQUIRE(pattern.getPoint(Tuple::point(-1.0f, 0.0f, 0.0f)) == BLACK);
    REQUIRE(pattern.getPoint(Tuple::point(-1.1f, 0.0f, 0.0f)) == WHITE);
}

TEST_CASE("Lighting with a pattern applied") {
    auto s = std::make_shared<Sphere>();
    Material m(WHITE, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    m.setPattern(sab);
    const auto eye = Tuple::vector(0.0f, 0.0f, -1.0f);
    const auto normal = Tuple::vector(0.0f, 0.0f, -1.0f);
    const PointLight light(
            Tuple::point(0.0f, 0.0f, -10.0f),
            WHITE);
    const auto c1 = m.lightning(
            light, s, Tuple::point(0.9f, 0.0f, 0.0f),
            eye, normal, false);
    const auto c2 = m.lightning(
            light, s, Tuple::point(1.1f, 0.0f, 0.0f),
            eye, normal, false);

    REQUIRE(c1 == WHITE);
    REQUIRE(c2 == BLACK);
}

TEST_CASE("Stripes with an object transformation") {
    auto s = std::make_shared<Sphere>(Mat4::scaling(2.0f, 2.0f, 2.0f));
    const StripePattern pattern(WHITE, BLACK);
    const auto c = pattern.getColor(s, Tuple::point(1.5f, 0.0f, 0.0f));

    REQUIRE(c == WHITE);
}

TEST_CASE("Stripes with a pattern transformation") {
    auto s = std::make_shared<Sphere>();
    const StripePattern pattern(
            Mat4::scaling(2.0f, 2.0f, 2.0f), WHITE, BLACK);
    const auto c = pattern.getColor(s, Tuple::point(1.5f, 0.0f, 0.0f));

    REQUIRE(c == WHITE);
}

TEST_CASE("Stripes with both an object and a pattern transformation") {
    auto s = std::make_shared<Sphere>(Mat4::scaling(2.0f, 2.0f, 2.0f));
    const StripePattern pattern(WHITE, BLACK);
    const auto c = pattern.getColor(s, Tuple::point(1.5f, 0.0f, 0.0f));

    REQUIRE(c == WHITE);
}

TEST_CASE("A gradient linearly interpolates between colors") {
    auto s = std::make_shared<Sphere>();
    const auto c1 = WHITE;
    const auto c2 = Color(0.75, 0.75, 0.75);
    const auto c3 = Color(0.5, 0.5, 0.5);
    const auto c4 = Color(0.25, 0.25, 0.25);

    REQUIRE(gab->getColor(s, Tuple::point(0.0f, 0.0f, 0.0f)) == c1);
    REQUIRE(gab->getColor(s, Tuple::point(0.25f, 0.0f, 0.0f)) == c2);
    REQUIRE(gab->getColor(s, Tuple::point(-0.25f, 0.0f, 0.0f)) == c2);
    REQUIRE(gab->getColor(s, Tuple::point(0.5f, 0.0f, 0.0f)) == c3);
    REQUIRE(gab->getColor(s, Tuple::point(-0.5f, 0.0f, 0.0f)) == c3);
    REQUIRE(gab->getColor(s, Tuple::point(0.75f, 0.0f, 0.0f)) == c4);
    REQUIRE(gab->getColor(s, Tuple::point(-0.75f, 0.0f, 0.0f)) == c4);
}

TEST_CASE("A ring should extend in both x and z") {
    auto s = std::make_shared<Sphere>();

    REQUIRE(rab->getColor(s, Tuple::point(0.0f, 0.0f, 0.0f)) == WHITE);
    REQUIRE(rab->getColor(s, Tuple::point(1.0f, 0.0f, 0.0f)) == BLACK);
    REQUIRE(rab->getColor(s, Tuple::point(0.0f, 0.0f, 1.0f)) == BLACK);
    REQUIRE(rab->getColor(s, Tuple::point(0.708f, 0.0f, 0.708f)) == BLACK);
}

TEST_CASE("Checkers should repeat in x") {
    auto s = std::make_shared<Sphere>();

    REQUIRE(cab->getColor(s, Tuple::point(0.0f, 0.0f, 0.0f)) == WHITE);
    REQUIRE(cab->getColor(s, Tuple::point(0.99f, 0.0f, 0.0f)) == WHITE);
    REQUIRE(cab->getColor(s, Tuple::point(1.01f, 0.0f, 0.0f)) == BLACK);
}

TEST_CASE("Checkers should repeat in y") {
    auto s = std::make_shared<Sphere>();

    REQUIRE(cab->getColor(s, Tuple::point(0.0f, 0.0f, 0.0f)) == WHITE);
    REQUIRE(cab->getColor(s, Tuple::point(0.0f, 0.99f, 0.0f)) == WHITE);
    REQUIRE(cab->getColor(s, Tuple::point(0.0f, 1.01f, 0.0f)) == BLACK);
}

TEST_CASE("Checkers should repeat in z") {
    auto s = std::make_shared<Sphere>();

    REQUIRE(cab->getColor(s, Tuple::point(0.0f, 0.0f, 0.0f)) == WHITE);
    REQUIRE(cab->getColor(s, Tuple::point(0.0f, 0.0f, 0.99f)) == WHITE);
    REQUIRE(cab->getColor(s, Tuple::point(0.0f, 0.0f, 1.01f)) == BLACK);
}