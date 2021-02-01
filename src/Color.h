//
// Created by SILENT on 22/01/2021.
//

#ifndef RAYTRACERCHALLENGE_COLOR_H
#define RAYTRACERCHALLENGE_COLOR_H

#include "Tuple.h"
#include <array>

class Color {
public:
    Color();

    explicit Color(float r, float g, float b);

    [[nodiscard]] float getRed() const;

    [[nodiscard]] float getGreen() const;

    [[nodiscard]] float getBlue() const;

    [[nodiscard]] int getRedInt() const;

    [[nodiscard]] int getGreenInt() const;

    [[nodiscard]] int getBlueInt() const;

    bool operator==(const Color &other) const;

    Color operator+(const Color &other) const;

    Color operator-(const Color &other) const;

    Color operator-() const;

    Color operator*(float other) const;

    Color operator*(const Color &other) const;

    friend std::ostream &operator<<(std::ostream &os, Color const &value);

private:
    std::array<float, 3> _buffer;

    static uint32_t floatToInt(float value);
};

static_assert(std::is_trivially_copyable<Color>::value, "Color has to be trivially copyable!");

#endif //RAYTRACERCHALLENGE_COLOR_H
