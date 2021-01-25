//
// Created by SILENT on 21/01/2021.
//

#ifndef RAYTRACERCHALLENGE_TUPLE_H
#define RAYTRACERCHALLENGE_TUPLE_H

#include <ostream>

class Tuple {
public:
    Tuple();

    explicit Tuple(float x, float y, float z, float w);

    [[nodiscard]]  static Tuple point(float x, float y, float z);

    [[nodiscard]] static Tuple vector(float x, float y, float z);

    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;

    [[nodiscard]] float getZ() const;

    [[nodiscard]] float getW() const;

    [[nodiscard]] bool isPoint() const;

    [[nodiscard]] bool isVector() const;

    bool operator==(const Tuple &other) const;

    Tuple operator+(const Tuple &other) const;

    Tuple operator-(const Tuple &other) const;

    Tuple operator-() const;

    Tuple operator*(float other) const;

    Tuple operator/(float other) const;

    float &operator[](uint32_t i);

    const float &operator[](uint32_t i) const;

    [[nodiscard]] float magnitude() const;

    void normalize();

    [[nodiscard]] Tuple normalized();

    friend std::ostream &operator<<(std::ostream &os, Tuple const &value);

    [[nodiscard]] static float dot(const Tuple &lhs, const Tuple &rhs);

    [[nodiscard]] static Tuple cross(const Tuple &lhs, const Tuple &rhs);

private:
    float _buffer[4];
};

#endif //RAYTRACERCHALLENGE_TUPLE_H
