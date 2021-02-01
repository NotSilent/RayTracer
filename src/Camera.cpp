//
// Created by SILENT on 01/02/2021.
//

#include "Camera.h"
#include "Ray.h"
#include "Canvas.h"
#include "World.h"

Camera::Camera(uint32_t width, uint32_t height, float fov) :
        _width(width), _height(height), _fov(fov), _transform(Mat4::identity()) {
    float halfView = FMath::tan(_fov / 2.0f);
    auto aspectRatio = static_cast<float>(_width) / _height;

    if (aspectRatio >= 1.0f) {
        _halfWidth = halfView;
        _halfHeight = halfView / aspectRatio;
    } else {
        _halfWidth = halfView * aspectRatio;
        _halfHeight = halfView;
    }

    _pixelSize = (_halfWidth * 2.0f) / _width;
}

Camera::Camera(uint32_t width, uint32_t height, float fov, Mat4 transform) :
        Camera(width, height, fov) {
    _transform = transform;
}


uint32_t Camera::getWidth() const {
    return _width;
}

uint32_t Camera::getHeight() const {
    return _height;
}

float Camera::getFOV() const {
    return _fov;
}

Mat4 Camera::getTransform() const {
    return _transform;
}

float Camera::getPixelSize() const {
    return _pixelSize;
}

Ray Camera::getRay(uint32_t pixelX, uint32_t pixelY) const {
    float xOffset = (pixelX + 0.5f) * _pixelSize;
    float yOffset = (pixelY + 0.5f) * _pixelSize;

    float worldX = _halfWidth - xOffset;
    float worldY = _halfHeight - yOffset;

    const auto pixel = _transform.inversed() * Tuple::point(worldX, worldY, -1.0f);
    const auto origin = _transform.inversed() * Tuple::point(0.0f, 0.0f, 0.0f);
    const auto direction = (pixel - origin).getNormalized();

    return Ray(origin, direction);
}

Canvas Camera::getRender(const World &world) const {
    Canvas canvas(getWidth(), getHeight());

    for (uint32_t y = 0; y < getHeight(); ++y) {
        for (uint32_t x = 0; x < getHeight(); ++x) {
            const auto ray = getRay(x, y);
            const auto color = world.getColor(ray);
            canvas.setColor(x, y, color);
        }
    }

    return canvas;
}
