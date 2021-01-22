//
// Created by SILENT on 22/01/2021.
//

#include <Color.h>
#include <Canvas.h>
#include "catch.hpp"

TEST_CASE("Creating a canvas") {
    const Canvas c(10, 20);
    REQUIRE(c.getWidth() == 10);
    REQUIRE(c.getHeight() == 20);

    const Color white(0.0f, 0.0f, 0.0f);
    for (int y = 0; y < c.getHeight(); ++y) {
        for (int x = 0; x < c.getWidth(); ++x) {
            REQUIRE(c.getColor(x, y) == white);
        }
    }
}

TEST_CASE("Writing pixels to a canvas") {
    Canvas c(10, 20);
    const Color red(1.0f, 0.0f, 0.0f);
    c.setColor(2, 3, red);
    REQUIRE(c.getColor(2, 3) == red);
}

TEST_CASE("Constructing the PPM header") {
    const Canvas c(5, 3);
    auto ppm = c.getAsString();

    std::string_view stringView(ppm);
    REQUIRE(stringView.substr(0, 11) == "P3\n5 3\n255\n");
}

TEST_CASE("Constructing the PPM pixel data") {
    Canvas c(5, 3);
    c.setColor(0, 0, Color(1.5f, 0.0f, 0.0f));
    c.setColor(2, 1, Color(0.0f, 0.5f, 0.0f));
    c.setColor(4, 2, Color(-0.5f, 0.0f, 1.0f));
    auto ppm = c.getAsString();
    REQUIRE(ppm == "P3\n5 3\n255\n"
                   "255 0 0\n0 0 0\n0 0 0\n0 0 0\n0 0 0\n"
                   "0 0 0\n0 0 0\n0 128 0\n0 0 0\n0 0 0\n"
                   "0 0 0\n0 0 0\n0 0 0\n0 0 0\n0 0 255\n");
}