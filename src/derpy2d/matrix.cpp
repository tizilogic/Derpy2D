
#include "derpy2d/matrix.h"
#include <math.h>
#include <assert.h>

Matrix3::Matrix3(float _00, float _10, float _20, float _01, float _11, float _21,
                 float _02, float _12, float _22)
 : _00(_00), _10(_10), _20(_20), _01(_01), _11(_11), _21(_21), _02(_02), _12(_12), _22(_22) {}

Matrix3& Matrix3::operator=(const Matrix3 &other) {
    _00 = other._00;
    _01 = other._01;
    _02 = other._02;
    _10 = other._10;
    _11 = other._11;
    _12 = other._12;
    _20 = other._20;
    _21 = other._21;
    _22 = other._22;

    return *this;
}

Matrix3 Matrix3::transpose(void) {
    return Matrix3(
        _00, _01, _02,
        _10, _11, _12,
        _20, _21, _22);
}

float Matrix3::cofactor(float m0, float m1, float m2, float m3) {
    return m0 * m3 - m1 * m2;
}

float Matrix3::determinant(void) {
    float c00 = cofactor(_11, _21, _12, _22);
	float c01 = cofactor(_10, _20, _12, _22);
	float c02 = cofactor(_10, _20, _11, _21);
	return _00 * c00 - _01 * c01 + _02 * c02;
}

Matrix3 Matrix3::inverse(void) {
    float c00 = cofactor(_11, _21, _12, _22);
    float c01 = cofactor(_10, _20, _12, _22);
    float c02 = cofactor(_10, _20, _11, _21);

    float det = _00 * c00 - _01 * c01 + _02 * c02;

    assert (fabsf(det) >= 0.000001);

    float c10 = cofactor(_01, _21, _02, _22);
    float c11 = cofactor(_00, _20, _02, _22);
    float c12 = cofactor(_00, _20, _01, _21);

    float c20 = cofactor(_01, _11, _02, _12);
    float c21 = cofactor(_00, _10, _02, _12);
    float c22 = cofactor(_00, _10, _01, _11);

    float invdet = 1.0 / det;
    return Matrix3(
        c00 * invdet,  -c01 * invdet,  c02 * invdet,
        -c10 * invdet,  c11 * invdet, -c12 * invdet,
        c20 * invdet,  -c21 * invdet,  c22 * invdet
    );
}

Matrix3 Matrix3::operator*(const float rhs) {
    Matrix3 m;
    m._00 = _00 * rhs;
    m._01 = _01 * rhs;
    m._02 = _02 * rhs;
    m._10 = _10 * rhs;
    m._11 = _11 * rhs;
    m._12 = _12 * rhs;
    m._20 = _20 * rhs;
    m._21 = _21 * rhs;
    m._22 = _22 * rhs;
    return m;
}

Matrix3& Matrix3::operator*=(const float rhs) {
    _00 *= rhs;
    _01 *= rhs;
    _02 *= rhs;
    _10 *= rhs;
    _11 *= rhs;
    _12 *= rhs;
    _20 *= rhs;
    _21 *= rhs;
    _22 *= rhs;
    return *this;
}

Matrix3 Matrix3::operator*(const Matrix3 &rhs) {
    return Matrix3(
			_00 * rhs._00 + _10 * rhs._01 + _20 * rhs._02, _00 * rhs._10 + _10 * rhs._11 + _20 * rhs._12, _00 * rhs._20 + _10 * rhs._21 + _20 * rhs._22,
			_01 * rhs._00 + _11 * rhs._01 + _21 * rhs._02, _01 * rhs._10 + _11 * rhs._11 + _21 * rhs._12, _01 * rhs._20 + _11 * rhs._21 + _21 * rhs._22,
			_02 * rhs._00 + _12 * rhs._01 + _22 * rhs._02, _02 * rhs._10 + _12 * rhs._11 + _22 * rhs._12, _02 * rhs._20 + _12 * rhs._21 + _22 * rhs._22
    );
}

Matrix3& Matrix3::operator*=(const Matrix3 &rhs) {
    Matrix3 m = *this * rhs;

    _00 = m._00;
    _01 = m._01;
    _02 = m._02;
    _10 = m._10;
    _11 = m._11;
    _12 = m._12;
    _20 = m._20;
    _21 = m._21;
    _22 = m._22;

    return *this;
}

Vec2 Matrix3::operator*(Vec2 &rhs) {
    float w = _02 * rhs.get_x() + _12 * rhs.get_y() + _22 * 1;
	float x = (_00 * rhs.get_x() + _10 * rhs.get_y() + _20 * 1) / w;
	float y = (_01 * rhs.get_x() + _11 * rhs.get_y() + _21 * 1) / w;
	return Vec2(x, y);
}

Matrix3 Matrix3::identity(void) {
    return Matrix3(
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
	);
}

Matrix3 Matrix3::translation(float x, float y) {
    return Matrix3(
		1, 0, x,
		0, 1, y,
		0, 0, 1
	);
}

Matrix3 Matrix3::scale(float x, float y) {
    return Matrix3(
        x, 0, 0,
        0, y, 0,
        0, 0, 1
    );
}

Matrix3 Matrix3::rotation(float alpha) {
	return Matrix3(
        cosf(alpha), -sinf(alpha), 0,
        sinf(alpha), cosf(alpha), 0,
        0, 0, 1
    );
}
