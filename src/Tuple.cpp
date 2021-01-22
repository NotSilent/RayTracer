//
// Created by SILENT on 21/01/2021.
//
#include "Tuple.h"
#include "FMath.h"
#include "math.h"

Tuple::Tuple(float x, float y, float z, float w) : _x(x), _y(y), _z(z), _w(w) {

}

Tuple Tuple::point(float x, float y, float z) {
    return Tuple(x, y, z, 1.0f);
}

Tuple Tuple::vector(float x, float y, float z) {
    return Tuple(x, y, z, 0.0f);
}

float Tuple::getX() const {
    return _x;
}

float Tuple::getY() const {
    return _y;
}

float Tuple::getZ() const {
    return _z;
}

float Tuple::getW() const {
    return _w;
}

bool Tuple::isPoint() const {
    return FMath::approximately(_w, 1.0f);
}

bool Tuple::isVector() const {
    return FMath::approximately(_w, 0.0f);
}

bool Tuple::operator==(const Tuple &other) const {
    return FMath::approximately(getX(), other.getX()) && FMath::approximately(getY(), other.getY()) &&
           FMath::approximately(getZ(), other.getZ()) && FMath::approximately(getW(), other.getW());
}

Tuple Tuple::operator+(const Tuple &other) const {
    return Tuple(getX() + other.getX(), getY() + other.getY(), getZ() + other.getZ(), getW() + other.getW());
}

Tuple Tuple::operator-(const Tuple &other) const {
    return Tuple(getX() - other.getX(), getY() - other.getY(), getZ() - other.getZ(), getW() - other.getW());
}

Tuple Tuple::operator-() const {
    return Tuple(-this->getX(), -this->getY(), -this->getZ(), -this->getW());
}

std::ostream &operator<<(std::ostream &os, const Tuple &value) {
    os << "{" << value.getX() << ", " << value.getY() << ", " << value.getZ() << ", " << value.getW() << "}";
    return os;
}

Tuple Tuple::operator*(const float other) const {
    return Tuple(getX() * other, getY() * other, getZ() * other, getW() * other);
}

Tuple Tuple::operator/(const float other) const {
    return Tuple(getX() / other, getY() / other, getZ() / other, getW() / other);
}

float Tuple::magnitude() const {
    return sqrt(getX() * getX() + getY() * getY() + getZ() * getZ() + getW() * getW());
}

void Tuple::normalize() {
    const auto magnitude = this->magnitude();
    _x /= magnitude;
    _y /= magnitude;
    _z /= magnitude;
    _w /= magnitude;
}

Tuple Tuple::normalized() {
    Tuple tuple = *this;
    tuple.normalize();
    return tuple;
}

float Tuple::dot(const Tuple &lhs, const Tuple &rhs) {
    return lhs.getX() * rhs.getX() + lhs.getY() * rhs.getY() + lhs.getZ() * rhs.getZ() + lhs.getW() * rhs.getW();
}

Tuple Tuple::cross(const Tuple &lhs, const Tuple &rhs) {
    return Tuple::vector(lhs.getY() * rhs.getZ() - lhs.getZ() * rhs.getY(),
                         lhs.getZ() * rhs.getX() - lhs.getX() * rhs.getZ(),
                         lhs.getX() * rhs.getY() - lhs.getY() * rhs.getX());
}
