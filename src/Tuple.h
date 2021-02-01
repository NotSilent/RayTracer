//
// Created by SILENT on 21/01/2021.
//

#ifndef RAYTRACERCHALLENGE_TUPLE_H
#define RAYTRACERCHALLENGE_TUPLE_H

#include <ostream>
#include <array>

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

    template<uint32_t COMPONENT>
    void set(float value) {
        _buffer[COMPONENT] = value;
    }

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

    [[nodiscard]] float getMagnitude() const;

    void normalize();

    [[nodiscard]] Tuple getNormalized() const;

    [[nodiscard]] Tuple getReflected(const Tuple &normal) const;

    friend std::ostream &operator<<(std::ostream &os, Tuple const &value);

    [[nodiscard]] static float dot(const Tuple &lhs, const Tuple &rhs);

    [[nodiscard]] static Tuple cross(const Tuple &lhs, const Tuple &rhs);

private:
    std::array<float, 4> _buffer;
};

static_assert(std::is_trivially_copyable<Tuple>::value, "Tuple has to be trivially copyable!");

#endif //RAYTRACERCHALLENGE_TUPLE_H
