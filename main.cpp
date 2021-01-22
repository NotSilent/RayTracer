#include <iostream>
#include <filesystem>
#include <fstream>
#include <Canvas.h>
#include "Tuple.h"

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
    Projectile proj{
            .position = Tuple::point(0.0f, 1.0f, 0.0f),
            .velocity = Tuple::vector(1.0f, 1.8f, 0.0f).normalized() * 12.5,
    };

    const Environment env{
            .gravity = Tuple::vector(0.0f, -0.1f, 0.0f),
            .wind = Tuple::vector(-0.01f, 0.0f, 0.0f),
    };

    Canvas canvas(WIDTH, HEIGHT);
    const Color white(1.0f, 1.0f, 1.0f);

    while (proj.position.getY() >= 0.0f) {
        canvas.setColor(proj.position.getX(), HEIGHT - proj.position.getY(), white);
        std::cout << "Projectile position: " << proj.position << "\n";

        proj = tick(env, proj);
    }

    //std::cout << std::filesystem::current_path() << "\n";

    std::ofstream file("image.ppm", std::ios::trunc);
    file << canvas.getAsString();
    file.close();

    return 0;
}