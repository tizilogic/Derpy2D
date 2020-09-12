#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <circle/types.h>
#include "vec.h"

class Matrix3 {
public:
    Matrix3(float _00 = 0.0f, float _10 = 0.0f, float _20 = 0.0f,
            float _01 = 0.0f, float _11 = 0.0f, float _21 = 0.0f,
            float _02 = 0.0f, float _12 = 0.0f, float _22 = 0.0f);
    Matrix3& operator=(const Matrix3 &other);

    Matrix3 transpose(void);
    float cofactor(float m0, float m1, float m2, float m3);
    float determinant(void);
    Matrix3 inverse(void);
    Matrix3 operator*(const float rhs);
    Matrix3& operator*=(const float rhs);
    Matrix3 operator*(const Matrix3 &rhs);
    Matrix3& operator*=(const Matrix3 &rhs);
    Vec2 operator*(Vec2 &rhs);

    static Matrix3 identity(void);
    static Matrix3 translation(float x, float y);
    static Matrix3 scale(float x, float y);
    static Matrix3 rotation(float alpha);
    float _00 = 0.0f, _10 = 0.0f, _20 = 0.0f,
          _01 = 0.0f, _11 = 0.0f, _21 = 0.0f,
          _02 = 0.0f, _12 = 0.0f, _22 = 0.0f;
};

#endif // _MATRIX_HPP_
