//
// Created by SILENT on 22/01/2021.
//

#include <Matrix.h>
#include <Tuple.h>
#include "catch.hpp"

TEST_CASE("Constructing and inspecting a 4x4 matrix") {
    Mat4 mat(1.0f, 2.0f, 3.0f, 4.0f,
             5.5f, 6.5f, 7.5f, 8.5f,
             9.0f, 10.0f, 11.0f, 12.0f,
             13.5f, 14.5f, 15.5f, 16.5f);

    REQUIRE(mat.get(0, 0) == 1.0f);
    REQUIRE(mat.get(0, 3) == 4.0f);
    REQUIRE(mat.get(1, 0) == 5.5f);
    REQUIRE(mat.get(1, 2) == 7.5f);
    REQUIRE(mat.get(2, 2) == 11.0f);
    REQUIRE(mat.get(3, 0) == 13.5f);
    REQUIRE(mat.get(3, 2) == 15.5f);
}

TEST_CASE("A 2x2 matrix ought to be representable") {
    Mat2 mat(-3.0f, 5.0f,
             1.0f, -2.0f);

    REQUIRE(mat.get(0, 0) == -3.0f);
    REQUIRE(mat.get(0, 1) == 5.0f);
    REQUIRE(mat.get(1, 0) == 1.0f);
    REQUIRE(mat.get(1, 1) == -2.0f);
}

TEST_CASE("A 3x3 matrix ought to be representable") {
    Mat3 mat(-3.0f, 5.0f, 0.0f,
             1.0f, -2.0f, -7.0f,
             0.0f, 1.0f, 1.0f);

    REQUIRE(mat.get(0, 0) == -3.0f);
    REQUIRE(mat.get(1, 1) == -2.0f);
    REQUIRE(mat.get(2, 2) == 1.0f);
}

TEST_CASE("Matrix equality with identical matrices") {
    Mat4 m1(1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 8.0f, 7.0f, 6.0f,
            5.0f, 4.0f, 3.0f, 2.0f);
    Mat4 m2(1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 8.0f, 7.0f, 6.0f,
            5.0f, 4.0f, 3.0f, 2.0f);

    REQUIRE(m1 == m2);
}

TEST_CASE("Matrix equality with different matrices") {
    Mat4 m1(1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 8.0f, 7.0f, 6.0f,
            5.0f, 4.0f, 3.0f, 2.0f);
    Mat4 m2(2.0f, 3.0f, 4.0f, 5.0f,
            6.0f, 7.0f, 8.0f, 9.0f,
            8.0f, 7.0f, 6.0f, 5.0f,
            4.0f, 3.0f, 2.0f, 1.0f);

    REQUIRE(m1 != m2);
}

TEST_CASE("Multiplying two matrices") {
    Mat4 m1(1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 8.0f, 7.0f, 6.0f,
            5.0f, 4.0f, 3.0f, 2.0f);
    Mat4 m2(-2.0f, 1.0f, 2.0f, 3.0f,
            3.0f, 2.0f, 1.0f, -1.0f,
            4.0f, 3.0f, 6.0f, 5.0f,
            1.0f, 2.0f, 7.0f, 8.0f);
    Mat4 m12(20.0f, 22.0f, 50.0f, 48.0f,
             44.0f, 54.0f, 114.0f, 108.0f,
             40.0f, 58.0f, 110.0f, 102.0f,
             16.0f, 26.0f, 46.0f, 42.0f);

    REQUIRE(m12 == (m1 * m2));
}

TEST_CASE("A matrix multiplied by a tuple") {
    Mat4 m(1.0f, 2.0f, 3.0f, 4.0f,
           2.0f, 4.0f, 4.0f, 2.0f,
           8.0f, 6.0f, 4.0f, 1.0f,
           0.0f, 0.0f, 0.0f, 1.0f);
    Tuple t(1.0f, 2.0f, 3.0f, 1.0f);
    Tuple mt(18.0f, 24.0f, 33.0f, 1.0f);

    REQUIRE(mt == (m * t));
}

TEST_CASE("Multiplying a matrix by the identity matrix") {
    Mat4 m(0.0f, 1.0f, 2.0f, 3.0f,
           1.0f, 2.0f, 4.0f, 8.0f,
           2.0f, 4.0f, 8.0f, 16.0f,
           4.0f, 8.0f, 16.0f, 32.0f);
    const auto identity = Mat4::identity();

    REQUIRE(m == (m * identity));
}

TEST_CASE("Multiplying the identity matrix by a tuple") {
    const Tuple t(1.0f, 2.0f, 3.0f, 4.0f);
    const auto identity = Mat4::identity();

    REQUIRE(t == (identity * t));
}

TEST_CASE("Transposing a matrix") {
    Mat4 m(0.0f, 9.0f, 3.0f, 0.0f,
           9.0f, 8.0f, 0.0f, 8.0f,
           1.0f, 8.0f, 5.0f, 3.0f,
           0.0f, 0.0f, 5.0f, 8.0f);

    Mat4 transpose(0.0f, 9.0f, 1.0f, 0.0f,
                   9.0f, 8.0f, 8.0f, 0.0f,
                   3.0f, 0.0f, 5.0f, 5.0f,
                   0.0f, 8.0f, 3.0f, 8.0f);

    REQUIRE(transpose == m.transposed());
}

TEST_CASE("Transposing the identity matrix") {
    const auto m = Mat4::identity();

    REQUIRE(m == m.transposed());
}

TEST_CASE("Calculating the determinant of a 2x2 matrix") {
    const Mat2 m(1.0f, 5.0f, -3.0f, 2.0f);

    REQUIRE(m.determinant() == 17);
}

TEST_CASE("A submatrix of a 3x3 matrix is a 2x2 matrix") {
    const Mat3 m3(1.0f, 5.0f, 0.0f,
                  -3.0f, 2.0f, 7.0f,
                  0.0f, 6.0f, -3.0f);
    const Mat2 m2(-3.0f, 2.0f,
                  0.0f, 6.0f);

    REQUIRE(m2 == m3.submatrix(0, 2));
}

TEST_CASE("A submatrix of a 4x4 matrix is a 3x3 matrix") {
    const Mat4 m4(-6.0f, 1.0f, 1.0f, 6.0f,
                  -8.0f, 5.0f, 8.0f, 6.0f,
                  -1.0f, 0.0f, 8.0f, 2.0f,
                  -7.0f, 1.0f, -1.0f, 1.0f);
    const Mat3 m3(-6.0f, 1.0f, 6.0f,
                  -8.0f, 8.0f, 6.0f,
                  -7.0f, -1.0f, 1.0f);

    REQUIRE(m3 == m4.submatrix(2, 1));
}

TEST_CASE("Calculating a minor of a 3x3 matrix") {
    const Mat3 m3(3.0f, 5.0f, 0.0f,
                  2.0f, -1.0f, -7.0f,
                  6.0f, -1.0f, 5.0f);
    const auto submatrix = m3.submatrix(1, 0);

    REQUIRE(submatrix.determinant() == 25);
    REQUIRE(m3.minor(1, 0) == 25);
}

TEST_CASE("Calculating a cofactor of a 3x3 matrix") {
    const Mat3 m3(3.0f, 5.0f, 0.0f,
                  2.0f, -1.0f, -7.0f,
                  6.0f, -1.0f, 5.0f);

    REQUIRE(m3.minor(0, 0) == -12);
    REQUIRE(m3.cofactor(0, 0) == -12);
    REQUIRE(m3.minor(1, 0) == 25);
    REQUIRE(m3.cofactor(1, 0) == -25);
}

TEST_CASE("Calculating the determinant of a 3x3 matrix") {
    const Mat3 m3(1.0f, 2.0f, 6.0f,
                  -5.0f, 8.0f, -4.0f,
                  2.0f, 6.0f, 4.0f);

    REQUIRE(m3.cofactor(0, 0) == 56);
    REQUIRE(m3.cofactor(0, 1) == 12);
    REQUIRE(m3.cofactor(0, 2) == -46);
    REQUIRE(m3.determinant() == -196);
}

TEST_CASE("Calculating the determinant of a 4x4 matrix") {
    const Mat4 m4(-2.0f, -8.0f, 3.0f, 5.0f,
                  -3.0f, 1.0f, 7.0f, 3.0f,
                  1.0f, 2.0f, -9.0f, 6.0f,
                  -6.0f, 7.0f, 7.0f, -9.0f);

    REQUIRE(m4.cofactor(0, 0) == 690);
    REQUIRE(m4.cofactor(0, 1) == 447);
    REQUIRE(m4.cofactor(0, 2) == 210);
    REQUIRE(m4.cofactor(0, 3) == 51);
    REQUIRE(m4.determinant() == -4071);
}

TEST_CASE("Testing an invertible matrix for invertibility") {
    const Mat4 m4(6.0f, 4.0f, 4.0f, 4.0f,
                  5.0f, 5.0f, 7.0f, 6.0f,
                  4.0f, -9.0f, 3.0f, -7.0f,
                  9.0f, 1.0f, 7.0f, -6.0f);

    REQUIRE(m4.determinant() == -2120);
    REQUIRE(m4.isInvertible());
}

TEST_CASE("Calculating the inverse of a matrix") {
    const Mat4 m4(-5.0f, 2.0f, 6.0f, -8.0f,
                  1.0f, -5.0f, 1.0f, 8.0f,
                  7.0f, 7.0f, -6.0f, -7.0f,
                  1.0f, -3.0f, 7.0f, 4.0f);

    const Mat4 inv(0.218045115f, 0.451127827f, 0.24060151f, -0.0451127812f,
                   -0.808270693f, -1.45676696f, -0.443609029f, 0.520676672f,
                   -0.0789473652f, -0.223684207f, -0.0526315793f, 0.197368428f,
                   -0.522556365f, -0.813909769f, -0.300751865f, 0.306390971f);

    const auto inverse = m4.inversed();

    REQUIRE(m4.determinant() == 532);
    REQUIRE(m4.cofactor(2, 3) == -160);
    REQUIRE(inverse.get(3, 2) == (-160.0f / 532.0f));
    REQUIRE(m4.cofactor(3, 2) == 105);
    REQUIRE(inverse.get(2, 3) == (105.f / 532));
    REQUIRE(inv == inverse);
}

TEST_CASE("Calculating the inverse of another matrix") {
    const Mat4 m4(8.0f, -5.0f, 9.0f, 2.0f,
                  7.0f, 5.0f, 6.0f, 1.0f,
                  -6.0f, 0.0f, 9.0f, 6.0f,
                  -3.0f, 0.0f, -9.0f, -4.0f);

    const Mat4 inv(-0.15384616f, -0.15384616f, -0.282051295f, -0.538461566f,
                   -0.0769230798f, 0.123076923f, 0.025641026f, 0.0307692308f,
                   0.358974367f, 0.358974367f, 0.43589744f, 0.923076927f,
                   -0.692307711f, -0.692307711f, -0.769230782f, -1.92307687f);

    const auto inverse = m4.inversed();

    REQUIRE(inv == inverse);
}

TEST_CASE("Calculating the inverse of a third matrix") {
    const Mat4 m4(9.0f, 3.0f, 0.0f, 9.0f,
                  -5.0f, -2.0f, -6.0f, -3.0f,
                  -4.0f, 9.0f, 6.0f, 4.0f,
                  -7.0f, 6.0f, 6.0f, 2.0f);

    const Mat4 inv(-0.0407407396f, -0.0777777805f, 0.144444451f, -0.222222224f,
                   -0.0777777805f, 0.0333333351f, 0.366666675f, -0.333333343f,
                   -0.0290123448f, -0.146296293f, -0.109259263f, 0.129629627f,
                   0.177777782f, 0.0666666701f, -0.266666681f, 0.333333343);

    const auto inverse = m4.inversed();

    REQUIRE(inv == inverse);
}

TEST_CASE("Multiplying a product by its inverse") {
    const Mat4 mat1(3.0f, -9.0f, 7.0f, 3.0f,
                    3.0f, -8.0f, 2.0f, -9.0f,
                    -4.0f, 4.0f, 4.0f, 1.0f,
                    -6.0f, 5.0f, -1.0f, 1.0f);

    const Mat4 mat2(8.0f, 2.0f, 2.0f, 2.0f,
                    3.0f, -1.0f, 7.0f, 0.0f,
                    7.0f, 0.0f, 5.0f, 4.0f,
                    6.0f, -2.0f, 0.0f, 5.0f);

    const auto mul = mat1 * mat2;
    const auto a = (mul * mat2.inversed());
    REQUIRE(mat1 == (mul * mat2.inversed()));
}