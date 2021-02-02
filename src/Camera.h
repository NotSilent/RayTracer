//
// Created by SILENT on 01/02/2021.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H


#include <cstdint>
#include "Matrix.h"

class Canvas;

class Ray;

class World;

class Camera {
public:
    Camera(uint32_t width, uint32_t height, float fov);

    Camera(uint32_t width, uint32_t height, float fov, Mat4 transform);

    [[nodiscard]] uint32_t getWidth() const;

    [[nodiscard]] uint32_t getHeight() const;

    [[nodiscard]] float getFOV() const;

    [[nodiscard]] Mat4 getTransform() const;

    [[nodiscard]] float getPixelSize() const;

    [[nodiscard]] Ray getRay(uint32_t pixelX, uint32_t pixelY) const;

    [[nodiscard]] Canvas getRender(World &world) const;

private:
    uint32_t _width;
    uint32_t _height;
    float _fov;
    float _halfWidth;
    float _halfHeight;
    float _pixelSize;
    Mat4 _transform;
};

static_assert(std::is_trivially_copyable<Camera>::value,
              "Camera has to be trivially copyable");

#endif //RAYTRACER_CAMERA_H
