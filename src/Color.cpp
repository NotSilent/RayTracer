//
// Created by SILENT on 22/01/2021.
//

#include <algorithm>
#include "Color.h"
#include "FMath.h"


Color::Color(float r, float g, float b) : _buffer{r, g, b} {

}

float Color::getRed() const {
    return _buffer[0];
}

float Color::getGreen() const {
    return _buffer[1];
}

float Color::getBlue() const {
    return _buffer[2];
}

bool Color::operator==(const Color &other) const {
    return FMath::approximately(getRed(), other.getRed()) && FMath::approximately(getGreen(), other.getGreen()) &&
           FMath::approximately(getBlue(), other.getBlue());
}

Color Color::operator+(const Color &other) const {
    return Color(getRed() + other.getRed(), getGreen() + other.getGreen(), getBlue() + other.getBlue());
}

Color Color::operator-(const Color &other) const {
    return Color(getRed() - other.getRed(), getGreen() - other.getGreen(), getBlue() - other.getBlue());
}

Color Color::operator-() const {
    return Color(-this->getRed(), -this->getGreen(), -this->getBlue());
}

std::ostream &operator<<(std::ostream &os, const Color &value) {
    os << "{" << value.getRed() << ", " << value.getGreen() << ", " << value.getBlue() << "}";
    return os;
}

Color Color::operator*(const float other) const {
    return Color(getRed() * other, getGreen() * other, getBlue() * other);
}

Color Color::operator*(const Color &other) const {
    return Color(getRed() * other.getRed(), getGreen() * other.getGreen(), getBlue() * other.getBlue());
}

Color::Color() : Color(0.0f, 0.0f, 0.0f) {

}


int Color::getRedInt() const {
    return floatToInt(getRed());
}

int Color::getGreenInt() const {
    return floatToInt(getGreen());
}

int Color::getBlueInt() const {
    return floatToInt(getBlue());
}

uint32_t Color::floatToInt(float value) {
    return std::clamp<uint32_t>(
            static_cast<uint32_t >(std::max(0.0f, value) * 256.0f),
            0,
            255);
}
