#include <iostream>
#include <chrono>
#include <Sphere.h>
#include <World.h>
#include <Camera.h>
#include <Canvas.h>
#include <fstream>
#include <Plane.h>
#include <GradientPattern.h>
#include <RingPattern.h>

int main() {
    auto t1 = std::chrono::high_resolution_clock::now();

    Material red(Color(1.0f, 0.0f, 0.0f),
                 0.1f, 0.9f, 0.0f, 200.0f,
                 0.0f, 0.0f, 1.0f);
    red.setPattern(std::make_shared<RingPattern>(
            Color(1.0f, 0.0f, 1.0f),
            Color(0.0f, 1.0f, 0.0f)));
    const Material blue(Color(0.0f, 0.0f, 1.0f),
                        0.1f, 0.9f, 0.0f, 200.0f,
                        0.0f, 0.0f, 1.0f);
    Material mirror(Color(0.5f, 0.5f, 0.5f),
                    0.1f, 0.5f, 5.0f, 200.0f,
                    1.0f, 0.0f, 1.5f);
    Material glass(Color(0.5f, 0.5f, 0.5f),
                   0.1f, 0.5f, 5.0f, 200.0f,
                   0.0f, 1.0f, 1.5f);
//    white.setPattern(std::make_shared<GradientPattern>(
//            Color(1.0f, 0.0f, 1.0f),
//            Color(0.0f, 1.0f, 0.0f)));

    const auto floor = std::make_shared<Plane>(red);
    const auto ceiling = std::make_shared<Plane>(
            Mat4::translation(0.0f, 50.0f, 0.0f), blue);
    const auto wall = std::make_shared<Plane>(
            Mat4::translation(0.0f, 0.0f, 50.0f) *
            Mat4::rotation<Axis::X>(FMath::PI / 2.0f),
            blue);
    const auto oppositeWall = std::make_shared<Plane>(
            Mat4::translation(0.0f, 0.0f, -50.0f) *
            Mat4::rotation<Axis::X>(FMath::PI / 2.0f),
            blue);
    const auto middle = std::make_shared<Sphere>(
            Mat4::translation(-0.5f, 1.0f, 0.5f), mirror);
    const auto right = std::make_shared<Sphere>(
            Mat4::translation(1.5f, 0.5f, -0.5f) *
            Mat4::scaling(0.5f, 0.5f, 0.5f), mirror);
    const auto left = std::make_shared<Sphere>(
            Mat4::translation(-1.5f, 0.33f, -0.75f) *
            Mat4::scaling(0.33f, 0.33f, 0.33f), mirror);
    World w;
    w.setLight(PointLight(Tuple::point(-10.0f, 10.0f, -10.0f),
                          Color(1.0f, 1.0f, 1.0f)));
    w.addObject(floor);
    w.addObject(ceiling);
    w.addObject(wall);
    w.addObject(oppositeWall);
    w.addObject(middle);
    w.addObject(right);
    w.addObject(left);
    Camera c(640, 480, FMath::PI / 3.0f,
             Mat4::getViewTransform(
                     Tuple::point(0.0f, 0.5f, -5.0f),
                     Tuple::point(0.0f, 1.0f, 0.0f),
                     Tuple::vector(0.0f, 1.0f, 0.0f)));

    const auto canvas = c.getRender(w);

    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << "Duration: " << duration << "\n";

    std::ofstream file("image.ppm", std::ios::trunc);
    file << canvas.getAsString();
    file.close();

    return 0;
}