//
// Created by SILENT on 22/01/2021.
//

#ifndef RAYTRACERCHALLENGE_COLOR_H
#define RAYTRACERCHALLENGE_COLOR_H

#include "Tuple.h"

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
    float _r;
    float _g;
    float _b;

    static uint32_t clampInt(uint32_t);
    static uint32_t floatToInt(float value);
};


#endif //RAYTRACERCHALLENGE_COLOR_H
