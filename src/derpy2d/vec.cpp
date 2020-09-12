#include "derpy2d/vec.h"
#include <assert.h>
#include <math.h>

Vec2::Vec2(void) {}

Vec2::Vec2(const float v) : x(v), y(v) {}

Vec2::Vec2(const float x, const float y) : x(x), y(y) {}

float Vec2::dot(const Vec2& other) {
    return x * other.x + y * other.y;
}

boolean Vec2::normalize(void) {
    float l = length();
    if (l > 0.0f) {
        x /= l;
        y /= l;
        len = mag = 1.0;
        state = 2;
        return true;
    }
    return false;
}

Vec2 Vec2::normalized(void) {
    Vec2 v = Vec2(x, y);
    assert(v.normalize());
    return v;
}

float Vec2::magnitude(void) {
    if (state < 1) {
        mag = dot(*this);
        state = 1;
    }
    return mag;
}

float Vec2::length(void) {
    if (state < 2) {
        const float m = magnitude();
        len = m > 0 ? sqrtf(m) : 0.0;
    }
    return len;
}

boolean Vec2::almost_equal(Vec2& other, const float epsilon) {
    return fabsf(x - other.x) + fabsf(y - other.y) <= epsilon;
}

float Vec2::get_x(void) {
    return x;
}

float Vec2::get_y(void) {
    return y;
}

void Vec2::set_x(const float v) {
    state = 0;
    x = v;
}

void Vec2::set_y(const float v) {
    state = 0;
    y = v;
}

Vec2 Vec2::operator+(const Vec2& rhs) {
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator+(const float rhs) {
    return Vec2(x + rhs, y + rhs);
}

Vec2& Vec2::operator+=(const Vec2& rhs) {
    state = 0;
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vec2& Vec2::operator+=(const float rhs) {
    state = 0;
    x += rhs;
    y += rhs;
    return *this;
}

Vec2 Vec2::operator-(const Vec2& rhs) {
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator-(const float rhs) {
    return Vec2(x - rhs, y - rhs);
}

Vec2& Vec2::operator-=(const Vec2& rhs) {
    state = 0;
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Vec2& Vec2::operator-=(const float rhs) {
    state = 0;
    x -= rhs;
    y -= rhs;
    return *this;
}

Vec2 Vec2::operator*(const float rhs) {
    return Vec2(x * rhs, y * rhs);
}

Vec2& Vec2::operator*=(const float rhs) {
    state = 0;
    x *= rhs;
    y *= rhs;
    return *this;
}

Vec2 Vec2::operator/(const float rhs) {
    assert(rhs != 0.0f);
    return Vec2(x / rhs, y / rhs);
}

Vec2& Vec2::operator/=(const float rhs) {
    assert(rhs != 0.0f);
    state = 0;
    x /= rhs;
    y /= rhs;
    return *this;
}

boolean Vec2::operator==(const Vec2& rhs) {
    return (x == rhs.x && y == rhs.y);
}

boolean Vec2::operator!=(const Vec2& rhs) {
    return !(*this == rhs);
}
