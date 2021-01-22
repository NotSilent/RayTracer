#include <iostream>
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

int main() {
    Projectile proj{
            .position = Tuple::point(0.0f, 1.0f, 0.0f),
            .velocity = Tuple::vector(1.0f, 1.0f, 0.0f).normalized(),
    };

    const Environment env{
            .gravity = Tuple::vector(0.0f, -0.1f, 0.0f),
            .wind = Tuple::vector(-0.01f, 0.0f, 0.0f),
    };

    while (proj.position.getY() >= 0.0f) {
        proj = tick(env, proj);

        std::cout << "Projectile position: " << proj.position << "\n";
    }

    return 0;
}