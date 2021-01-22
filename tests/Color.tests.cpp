//
// Created by SILENT on 22/01/2021.
//

#include "catch.hpp"
#include "Color.h"

TEST_CASE("Colors are (red, green, blue) tuples") {
    const Color c(-0.5f, 0.4f, 1.7f);
    REQUIRE(c.getRed() == -0.5f);
    REQUIRE(c.getGreen() == 0.4f);
    REQUIRE(c.getBlue() == 1.7f);
}

TEST_CASE("Adding colors") {
    const Color c1(0.9f, 0.6f, 0.75f);
    const Color c2(0.7f, 0.1f, 0.25f);
    const Color sum(1.6f, 0.7f, 1.0f);
    REQUIRE(sum == (c1 + c2));
}

TEST_CASE("Subtracting colors") {
    const Color c1(0.9f, 0.6f, 0.75f);
    const Color c2(0.7f, 0.1f, 0.25f);
    const Color sub(0.2f, 0.5f, 0.5f);
    REQUIRE(sub == (c1 - c2));
}

TEST_CASE("Multiplying a color by a scalar") {
    const Color c(0.2f, 0.3f, 0.4f);
    const Color mul(0.4f, 0.6f, 0.8f);
    REQUIRE(mul == (c * 2.0f));
}

TEST_CASE("Multiplying colors") {
    const Color c1(1.0f, 0.2f, 0.4f);
    const Color c2(0.9f, 1.0f, 0.1f);
    const Color mul(0.9f, 0.2f, 0.04f);
    REQUIRE(mul == (c1 * c2));
}