//
// Created by SILENT on 22/01/2021.
//

#ifndef RAYTRACERCHALLENGE_MATRIX_H
#define RAYTRACERCHALLENGE_MATRIX_H

#include <cstdint>
#include <array>
#include <sstream>
#include <exception>
#include "FMath.h"
#include "Tuple.h"

template<uint32_t DIMENSION>
class Matrix {
public:
    Matrix() : _buffer(std::array<float, DIMENSION * DIMENSION>()) {
    }

    ~Matrix() = default;

    template<uint32_t D = DIMENSION>
    requires (D == 2)
    Matrix<DIMENSION>(float v0, float v1, float v2, float v3) :
            _buffer{v0, v1,
                    v2, v3} {
    }

    template<uint32_t D = DIMENSION>
    requires (D == 3)
    Matrix<DIMENSION>(float v0, float v1, float v2,
                      float v3, float v4, float v5,
                      float v6, float v7, float v8) :
            _buffer{v0, v1, v2,
                    v3, v4, v5,
                    v6, v7, v8} {
    }

    template<uint32_t D = DIMENSION>
    requires (D == 4)
    Matrix<DIMENSION>(float v0, float v1, float v2, float v3,
                      float v4, float v5, float v6, float v7,
                      float v8, float v9, float v10, float v11,
                      float v12, float v13, float v14, float v15) :
            _buffer{v0, v1, v2, v3,
                    v4, v5, v6, v7,
                    v8, v9, v10, v11,
                    v12, v13, v14, v15} {
    }

    template<uint32_t D = DIMENSION>
    [[nodiscard]] typename std::enable_if<(D == 4), Matrix<DIMENSION>>::type
    static getViewTransform(const Tuple &from, const Tuple &to, const Tuple &up) {
        const auto forward = (to - from).getNormalized();
        const auto left = Tuple::cross(forward, up.getNormalized());
        const auto trueUp = Tuple::cross(left, forward);

        const Matrix<DIMENSION> orientation(left.getX(), left.getY(), left.getZ(), 0.0f,
                                            trueUp.getX(), trueUp.getY(), trueUp.getZ(), 0.0f,
                                            -forward.getX(), -forward.getY(), -forward.getZ(), 0.0f,
                                            0.0f, 0.0f, 0.0f, 1.0f);

        return orientation * translation(-from.getX(), -from.getY(), -from.getZ());
    }

    template<uint32_t D = DIMENSION>
    [[nodiscard]] typename std::enable_if<(D == 4), Matrix<DIMENSION>>::type
    static translation(const float x, const float y, const float z) {
        return Matrix<DIMENSION>{1.0f, 0.0f, 0.0f, x,
                                 0.0f, 1.0f, 0.0f, y,
                                 0.0f, 0.0f, 1.0f, z,
                                 0.0f, 0.0f, 0.0f, 1.0f};
    }

    template<uint32_t D = DIMENSION>
    [[nodiscard]] typename std::enable_if<(D == 4), Matrix<DIMENSION>>::type
    static scaling(const float x, const float y, const float z) {
        return Matrix<DIMENSION>{x, 0.0f, 0.0f, 0.0f,
                                 0.0f, y, 0.0f, 0.0f,
                                 0.0f, 0.0f, z, 0.0f,
                                 0.0f, 0.0f, 0.0f, 1.0f};
    }

    template<Axis AXIS, uint32_t D = DIMENSION>
    [[nodiscard]] typename std::enable_if<(D == 4), Matrix<DIMENSION>>::type
    static rotation(const float angleRad) {
        if constexpr (AXIS == Axis::X) {
            return Matrix<DIMENSION>{1.0f, 0.0f, 0.0f, 0.0f,
                                     0.0f, FMath::cos(angleRad), -FMath::sin(angleRad), 0.0f,
                                     0.0f, FMath::sin(angleRad), FMath::cos(angleRad), 0.0f,
                                     0.0f, 0.0f, 0.0f, 1.0f};
        } else if constexpr (AXIS == Axis::Y) {
            return Matrix<DIMENSION>{FMath::cos(angleRad), 0.0f, FMath::sin(angleRad), 0.0f,
                                     0.0f, 1.0f, 0.0f, 0.0f,
                                     -FMath::sin(angleRad), 0.0f, FMath::cos(angleRad), 0.0f,
                                     0.0f, 0.0f, 0.0f, 1.0f};
        } else if constexpr (AXIS == Axis::Z) {
            return Matrix<DIMENSION>{FMath::cos(angleRad), -FMath::sin(angleRad), 0.0f, 0.0f,
                                     FMath::sin(angleRad), FMath::cos(angleRad), 0.0f, 0.0f,
                                     0.0f, 0.0f, 1.0f, 0.0f,
                                     0.0f, 0.0f, 0.0f, 1.0f};
        } else {
            throw std::runtime_error("How did it even compile?");
        }
    }

    template<uint32_t D = DIMENSION>
    [[nodiscard]] typename std::enable_if<(D == 4), Matrix<DIMENSION>>::type
    static shearing(const float xToY, const float xToZ,
                    const float yToX, const float yToZ,
                    const float zToX, const float zToY) {
        return Matrix<DIMENSION>{1.0f, xToY, xToZ, 0.0f,
                                 yToX, 1.0f, yToZ, 0.0f,
                                 zToX, zToY, 1.0f, 0.0f,
                                 0.0f, 0.0f, 0.0f, 1.0f};
    }

    [[nodiscard]] static Matrix identity() {
        Matrix<DIMENSION> mat;
        for (uint32_t i = 0; i < DIMENSION; ++i) {
            mat.set(i, i, 1.0f);
        }

        return mat;
    }

    [[nodiscard]] float get(uint32_t row, uint32_t col) const {
        return _buffer[row * DIMENSION + col];
    }

    void set(uint32_t row, uint32_t col, float value) {
        _buffer[row * DIMENSION + col] = value;
    }

    [[nodiscard]] Matrix<DIMENSION> transposed() const {
        Matrix<DIMENSION> mat;
        for (uint32_t rows = 0; rows < DIMENSION; ++rows) {
            for (uint32_t cols = 0; cols < DIMENSION; ++cols) {
                mat.set(cols, rows, get(rows, cols));
            }
        }

        return mat;
    }

    [[nodiscard]] Matrix<DIMENSION - 1> submatrix(uint32_t row, uint32_t col) const {
        Matrix<DIMENSION - 1> m;
        for (uint32_t r = 0; r < DIMENSION - 1; ++r) {
            for (uint32_t c = 0; c < DIMENSION - 1; ++c) {
                m.set(r, c,
                      get(r >= row ? r + 1 : r, c >= col ? c + 1 : c));
            }
        }

        return m;
    }

    [[nodiscard]] float minor(const uint32_t row, const uint32_t col) const {
        return submatrix(row, col).determinant();
    }

    [[nodiscard]] float cofactor(const uint32_t row, const uint32_t col) const {
        const int32_t sign = ((row + col) % 2) == 0 ? 1 : -1;
        return submatrix(row, col).determinant() * sign;
    }

    [[nodiscard]] bool isInvertible() const {
        return determinant() != 0.0f;
    }

    [[nodiscard]] Matrix<DIMENSION> inversed() const {
        // TODO: Change to std::optional
        if (!isInvertible()) {
            throw std::runtime_error("Tried to inverse inreversible matrix");
        }

        Matrix<DIMENSION> mat;

        for (uint32_t row = 0; row < DIMENSION; ++row) {
            for (uint32_t col = 0; col < DIMENSION; ++col) {
                float cof = cofactor(row, col);
                mat.set(col, row, cof / determinant());
            }
        }

        return mat;
    }

    [[nodiscard]] friend bool operator==(const Matrix<DIMENSION> &lhs, const Matrix<DIMENSION> &rhs) {
        if (lhs._buffer.size() != rhs._buffer.size()) {
            return false;
        }

        for (uint32_t i = 0; i < lhs._buffer.size(); ++i) {
            if (!FMath::approximately(lhs._buffer[i], rhs._buffer[i])) {
                return false;
            }
        }

        return true;
    }

    [[nodiscard]] friend bool operator!=(const Matrix<DIMENSION> &lhs, const Matrix<DIMENSION> &rhs) {
        return !(lhs == rhs);
    }

    [[nodiscard]] friend Matrix<DIMENSION> operator*(
            const Matrix<DIMENSION> &lhs, const Matrix<DIMENSION> &rhs) {
        Matrix<DIMENSION> mat;
        for (uint32_t row = 0; row < DIMENSION; row++) {
            for (uint32_t col = 0; col < DIMENSION; col++) {
                float value = 0.0f;
                for (uint32_t i = 0; i < DIMENSION; i++) {
                    value += lhs.get(row, i) * rhs.get(i, col);
                }
                mat.set(row, col, value);
            }
        }

        return mat;
    }

    template<uint32_t D = DIMENSION>
    [[nodiscard]] typename std::enable_if<(D == 4), Tuple>::type
    operator*(const Tuple &tuple) const {
        Tuple t;

        for (uint32_t row = 0; row < DIMENSION; row++) {
            float value = 0.0f;
            for (uint32_t col = 0; col < DIMENSION; col++) {
                value += get(row, col) * tuple[col];
            }
            t[row] = value;
        }

        return t;
    }

    [[nodiscard]] float determinant() const {
        if constexpr (DIMENSION <= 1) {
            //TODO: probably won't be needed, ever
            throw std::runtime_error("Tried to compute determinant of 1x1 matrix");
        } else if constexpr (DIMENSION == 2) {
            return _buffer[0] * _buffer[3] - _buffer[1] * _buffer[2];
        } else {
            float det = 0.0f;

            for (uint32_t col = 0; col < DIMENSION; ++col) {
                det += get(0, col) * cofactor(0, col);
            }

            return det;
        }
    }

    [[nodiscard]] friend std::ostream &operator<<(std::ostream &os, Matrix<DIMENSION> mat) {
        std::stringstream ss;
        ss << "{";
        auto value = mat._buffer.begin();
        for (; value != mat._buffer.end() - 1; ++value) {
            ss << *value << ", ";
        }
        ss << *value << "}";

        os << ss.str();

        return os;
    }

private:
    [[nodiscard]] const Matrix<DIMENSION> &self() const {
        return static_cast<const Matrix<DIMENSION> &>(*this);
    }

protected:
    std::array<float, DIMENSION * DIMENSION> _buffer;
};

using Mat2 = Matrix<2>;
using Mat3 = Matrix<3>;
using Mat4 = Matrix<4>;

static_assert(std::is_trivially_copyable<Mat2>::value, "Mat2 has to be trivially copyable");
static_assert(std::is_trivially_copyable<Mat3>::value, "Mat3 has to be trivially copyable");
static_assert(std::is_trivially_copyable<Mat4>::value, "Mat4 has to be trivially copyable");

#endif //RAYTRACERCHALLENGE_MATRIX_H
