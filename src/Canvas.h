//
// Created by SILENT on 22/01/2021.
//

#ifndef RAYTRACERCHALLENGE_CANVAS_H
#define RAYTRACERCHALLENGE_CANVAS_H

#include <cstdint>
#include <vector>
#include "Color.h"

class Canvas {
public:
    Canvas(uint32_t width, uint32_t height);

    [[nodiscard]] uint32_t getWidth() const;

    [[nodiscard]] uint32_t getHeight() const;

    [[nodiscard]] Color getColor(uint32_t x, uint32_t y) const;

    [[nodiscard]] std::string getAsString() const;

    void setColor(uint32_t x, uint32_t y, const Color &color);

private:
    uint32_t _width;
    uint32_t _height;

    std::vector<Color> _buffer;
};


#endif //RAYTRACERCHALLENGE_CANVAS_H
