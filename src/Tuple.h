//
// Created by SILENT on 21/01/2021.
//

#ifndef RAYTRACERCHALLENGE_TUPLE_H
#define RAYTRACERCHALLENGE_TUPLE_H

class Tuple {
public:
    explicit Tuple(float x, float y, float z, float w);

    [[nodiscard]] static Tuple point(float x, float y, float z);

    [[nodiscard]] static Tuple vector(float x, float y, float z);

    float getX() const;

    float getY() const;

    float getZ() const;

    float getW() const;

    bool isPoint() const;

    bool isVector() const;

    bool operator==(const Tuple &other) const;

    Tuple operator+(const Tuple &other) const;

    Tuple operator-(const Tuple &other) const;

    Tuple operator-() const;

    Tuple operator*(const float other) const;

    Tuple operator/(const float other) const;

    float magnitude() const;

    void normalize();

    [[nodiscard]] Tuple normalized();

    friend std::ostream &operator<<(std::ostream &os, Tuple const &value);

    static float dot(const Tuple &lhs, const Tuple &rhs);

    [[nodiscard]]static Tuple cross(const Tuple &lhs, const Tuple &rhs);

private:
    float _x;
    float _y;
    float _z;
    float _w;
};

#endif //RAYTRACERCHALLENGE_TUPLE_H
