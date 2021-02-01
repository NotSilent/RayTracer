#include <iostream>
#include <chrono>
#include <Sphere.h>
#include <World.h>
#include <Camera.h>
#include <Canvas.h>
#include <fstream>

int main() {
    auto t1 = std::chrono::high_resolution_clock::now();

    const Material red(Color(1.0f, 0.0f, 0.0f),
                       0.1f, 0.9f, 0.0f, 0.0f);
    const Material blue(Color(0.0f, 0.0f, 1.0f),
                        0.1f, 0.9f, 0.0f, 0.0f);
    const Material green(Color(0.0f, 1.0f, 0.0f),
                         0.1f, 0.5f, 5.0f, 200.0f);

    const Sphere floor(Mat4::scaling(10.0f, 0.01f, 10.0f), red);
    const Sphere leftWall(Mat4::translation(0.0f, 0.0f, 5.0f) *
                          Mat4::rotation<Axis::Y>(-FMath::PI / 4.0f) *
                          Mat4::rotation<Axis::X>(FMath::PI / 2.0f) *
                          Mat4::scaling(10.0f, 0.01f, 10.0f),
                          blue);
    const Sphere rightWall(Mat4::translation(0.0f, 0.0f, 5.0f) *
                           Mat4::rotation<Axis::Y>(FMath::PI / 4.0f) *
                           Mat4::rotation<Axis::X>(FMath::PI / 2.0f) *
                           Mat4::scaling(10.0f, 0.01f, 10.0f),
                           blue);
    const Sphere middle(Mat4::translation(-0.5f, 1.0f, 0.5f), green);
    const Sphere right(Mat4::translation(1.5f, 0.5f, -0.5f) *
                       Mat4::scaling(0.5f, 0.5f, 0.5f), green);
    const Sphere left(Mat4::translation(-1.5f, 0.33f, -0.75f) *
                      Mat4::scaling(0.33f, 0.33f, 0.33f), green);
    World w;
    w.addLight(PointLight(Tuple::point(-10.0f, 10.0f, -10.0f),
                          Color(0.0f, 1.0f, 1.0f)));
    w.addLight(PointLight(Tuple::point(10.0f, 10.0f, -10.0f),
                          Color(1.0f, 1.0f, 0.0f)));
    w.addObject(floor);
    w.addObject(leftWall);
    w.addObject(rightWall);
    w.addObject(middle);
    w.addObject(right);
    w.addObject(left);
    Camera c(640, 480, FMath::PI / 3.0f,
             Mat4::getViewTransform(
                     Tuple::point(0.0f, 1.5f, -5.0f),
                     Tuple::point(0.1f, 1.0f, 0.0f),
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