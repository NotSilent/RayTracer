#include <iostream>
#include <filesystem>
#include <fstream>
#include <Canvas.h>
#include <Sphere.h>
#include <Ray.h>
#include "Tuple.h"
#include "IntersectionResult.h"
#include "PointLight.h"
#include <chrono>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

Color getColor(const Sphere &s, const Tuple &origin, const PointLight &light,
               uint32_t x, uint32_t y);

int main() {
    auto t1 = std::chrono::high_resolution_clock::now();

    Canvas canvas(WIDTH, HEIGHT);

    const Sphere s;
    const PointLight light(
            Tuple::point(-10.0, 10.0f, -10.0f),
            Color(1.0f, 1.0f, 1.0f));
    const auto origin = Tuple::point(0.0f, 0.0f, -10.0f);

    for (uint32_t x = 0; x < WIDTH; ++x) {
        for (uint32_t y = 0; y < HEIGHT; ++y) {
            const auto color = getColor(s, origin, light, x, y);
            canvas.setColor(x, y, color);
        }
    }

    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << "Duration: " << duration << "\n";

    //std::cout << std::filesystem::current_path() << "\n";

    std::ofstream file("image.ppm", std::ios::trunc);
    file << canvas.getAsString();
    file.close();

    return 0;
}

Color getColor(const Sphere &s, const Tuple &origin, const PointLight &light,
               uint32_t x, uint32_t y) {
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

    const auto hit = ir.getHit();
    const auto point = ray.getPosition(hit->getDistance());
    const auto normal = hit->getObject().getNormalAt(point);
    const auto eye = -ray.getDirection();

    return hit->getObject().getMaterial().lightning(light, point, eye, normal);
}
