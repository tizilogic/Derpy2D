#ifndef _VEC_HPP_
#define _VEC_HPP_

#include <circle/types.h>

class Vec2 {
public:
    Vec2(void);
    Vec2(const float v);
    Vec2(const float x, const float y);
    Vec2(const Vec2& other);
    Vec2& operator=(const Vec2& other);

    float dot(const Vec2& other);
    boolean normalize(void);
    Vec2 normalized(void);
    float magnitude(void);
    float length(void);
    boolean almost_equal(Vec2& other, const float epsilon = 1e-6f);

    float get_x(void);
    float get_y(void);
    void set_x(const float v);
    void set_y(const float v);
    Vec2 operator+(const Vec2& rhs);
    Vec2 operator+(const float rhs);
    Vec2& operator+=(const Vec2& rhs);
    Vec2& operator+=(const float rhs);
    Vec2 operator-(const Vec2& rhs);
    Vec2 operator-(const float rhs);
    Vec2& operator-=(const Vec2& rhs);
    Vec2& operator-=(const float rhs);
    Vec2 operator*(const float rhs);
    Vec2& operator*=(const float rhs);
    Vec2 operator/(const float rhs);
    Vec2& operator/=(const float rhs);
    boolean operator==(const Vec2& rhs);
    boolean operator!=(const Vec2& rhs);
private:
    float x = 0.0f, y = 0.0f, len = 0.0f, mag = 0.0f;
    u8 state = 0;
};

#endif // _VEC_HPP_