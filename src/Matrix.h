//
// Created by SILENT on 22/01/2021.
//

#ifndef RAYTRACERCHALLENGE_MATRIX_H
#define RAYTRACERCHALLENGE_MATRIX_H

#include <cstdint>
#include <vector>
#include <sstream>
#include <exception>
#include "FMath.h"
#include "Tuple.h"

template<uint32_t DIMENSION>
class Matrix {
public:
    Matrix() {
        _buffer = std::vector<float>(DIMENSION * DIMENSION);
    }

    [[nodiscard]] static Matrix<DIMENSION> identity() {
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

        for (uint32_t row = 0; row < 4; ++row) {
            for (uint32_t col = 0; col < 4; ++col) {
                float cof = cofactor(row, col);
                mat.set(col, row, cof / determinant());
            }
        }

        return mat;
    }

    [[nodiscard]] friend bool operator==(const Matrix<DIMENSION> &lhs, const Matrix<DIMENSION> &rhs) {
        //Tests need smaller precision
        //TODO: Create some engine utils class and change it to constexpr
#ifndef NDEBUG
        if (lhs._buffer.size() != rhs._buffer.size()) {
            return false;
        }

        for (uint32_t i = 0; i < lhs._buffer.size(); ++i) {
            if (!FMath::approximately(lhs._buffer[i], rhs._buffer[i])) {
                return false;
            }
        }

        return true;
#else
        return lhs._buffer == rhs._buffer;
#endif
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
    operator*(Tuple const &tuple) const {
        Tuple t;

        for (uint32_t row = 0; row < 4; row++) {
            float value = 0.0f;
            for (uint32_t col = 0; col < 4; col++) {
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
            float det = 0;

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
    std::vector<float> _buffer;
};

class Mat2 : public Matrix<2> {
public:
    Mat2(float v0, float v1, float v2, float v3) {
        _buffer = std::vector<float>{v0, v1, v2, v3};
    }
};

class Mat3 : public Matrix<3> {
public:
    Mat3(float v0, float v1, float v2,
         float v3, float v4, float v5,
         float v6, float v7, float v8) {
        _buffer = std::vector<float>{v0, v1, v2,
                                     v3, v4, v5,
                                     v6, v7, v8};
    }
};

class Mat4 : public Matrix<4> {
public:
    Mat4(float v0, float v1, float v2, float v3,
         float v4, float v5, float v6, float v7,
         float v8, float v9, float v10, float v11,
         float v12, float v13, float v14, float v15) {
        _buffer = std::vector<float>{v0, v1, v2, v3,
                                     v4, v5, v6, v7,
                                     v8, v9, v10, v11,
                                     v12, v13, v14, v15};
    }
};

#endif //RAYTRACERCHALLENGE_MATRIX_H