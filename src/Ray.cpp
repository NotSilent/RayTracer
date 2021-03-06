//
// Created by SILENT on 26/01/2021.
//

#include "Ray.h"

Ray::Ray(float originX, float originY, float originZ,
         float directionX, float directionY, float directionZ) :
        _origin(Tuple::point(originX, originY, originZ)),
        _direction(Tuple::vector(directionX, directionY, directionZ)) {
}

Ray::Ray(const Tuple &origin, const Tuple &direction) : _origin(origin), _direction(direction) {

}

Ray operator*(const Mat4 &lhs, const Ray &rhs) {
    return Ray(lhs * rhs.getOrigin(), lhs * rhs.getDirection());
}

Tuple Ray::getOrigin() const {
    return _origin;
}

Tuple Ray::getDirection() const {
    return _direction;
}

Tuple Ray::getPosition(float distance) const {
    return getOrigin() + getDirection() * distance;
}

