#include <iostream>
#include <filesystem>
#include <fstream>
#include <Canvas.h>
#include <Sphere.h>
#include <Ray.h>
#include "Tuple.h"
#include "Matrix.h"
#include "IntersectionResult.h"

const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;

Color getColor(const Sphere &s, const Tuple &origin, uint32_t x, uint32_t y);

int main() {
    Canvas canvas(WIDTH, HEIGHT);

    const Sphere s;
    const auto origin = Tuple::point(0.0f, 0.0f, -10.0f);

    for (uint32_t x = 0; x < WIDTH; ++x) {
        for (uint32_t y = 0; y < HEIGHT; ++y) {
            const auto color = getColor(s, origin, x, y);
            canvas.setColor(x, y, color);
        }
    }

    //std::cout << std::filesystem::current_path() << "\n";

    std::ofstream file("image.ppm", std::ios::trunc);
    file << canvas.getAsString();
    file.close();

    return 0;
}

Color getColor(const Sphere &s, const Tuple &origin, uint32_t x, uint32_t y) {
    static const Color hitColor(0.5f, 1.0f, 0.5f);
    static const Color black(0.0f, 0.0f, 0.0f);
    static const float mul = 4.0f;
    static const float aspectRatio = static_cast<float>(WIDTH) / HEIGHT;

    float normalX = (static_cast<float>(x) / static_cast<float>(WIDTH)) * 2.0f - 1.0f;
    float normalY = ((static_cast<float>(y) / static_cast<float>(HEIGHT)) * 2.0f - 1.0f) / aspectRatio;

    const auto direction = (Tuple::point(normalX * mul, normalY * mul, 0.0f) - origin).getNormalized();

    const Ray ray(origin, direction);
    const auto ir = s.getIntersectionResult(ray);

    if (ir.getCount() == 0) {
        return black;
    }

    return hitColor;
}
