#include <iostream>
#include <filesystem>
#include <fstream>
#include <Canvas.h>
#include "Tuple.h"
#include "Matrix.h"

struct Projectile {
    Tuple position;
    Tuple velocity;
};

struct Environment {
    Tuple gravity;
    Tuple wind;
};

Projectile tick(const Environment &env, const Projectile &proj) {
    const auto position = proj.position + proj.velocity;
    const auto velocity = proj.velocity + env.gravity + env.wind;
    return Projectile{
            .position = position,
            .velocity = velocity,
    };
}

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

int main() {
    Canvas canvas(WIDTH, HEIGHT);
    const Color white(1.0f, 1.0f, 1.0f);

    const auto point = Tuple::point(0.0f, 0.5f, 0.0f);
    float step = (2.0f * FMath::PI) / 12.0f;
    float aspectRatio = static_cast<float>(WIDTH) / HEIGHT;

    for (uint32_t i = 0; i < 12; ++i) {
        const auto rotation = Mat4::rotation<Axis::Z>(step * i);
        const auto hourPosition = rotation * point;

        float x = hourPosition.getX() / aspectRatio;
        x = (x + 1.0f) / 2.0f;

        float y = (hourPosition.getY() + 1.0f) / 2.0f;

        x *= WIDTH;
        y *= HEIGHT;

        canvas.setColor(x, y, Color(1.0f, 1.0f, 1.0f));
    }

    //std::cout << std::filesystem::current_path() << "\n";

    std::ofstream file("image.ppm", std::ios::trunc);
    file << canvas.getAsString();
    file.close();

    return 0;
}