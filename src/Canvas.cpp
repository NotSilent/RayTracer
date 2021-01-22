//
// Created by SILENT on 22/01/2021.
//

#include "Canvas.h"
#include <sstream>

Canvas::Canvas(uint32_t width, uint32_t height) : _width(width), _height(height) {
    const Color white(0.0f, 0.0f, 0.0f);
    _buffer = std::vector<Color>(width * height, white);
}

uint32_t Canvas::getWidth() const {
    return _width;
}

uint32_t Canvas::getHeight() const {
    return _height;
}

Color Canvas::getColor(uint32_t x, uint32_t y) const {
    return _buffer[(_width * y) + x];
}

void Canvas::setColor(uint32_t x, uint32_t y, const Color &color) {
    if (x >= getWidth() || y >= getHeight()) {
        return;
    }

    _buffer[(_width * y) + x] = color;
}

std::string Canvas::getAsString() const {
    std::stringstream ss;
    ss << "P3\n" << getWidth() << " " << getHeight() << "\n" << "255\n";

    for (const auto &color : _buffer) {
        ss << color.getRedInt() << " "
           << color.getGreenInt() << " "
           << color.getBlueInt() << "\n";
    }

    return ss.str();
}