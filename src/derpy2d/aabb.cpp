#include "derpy2d/aabb.h"
#include <assert.h>
#include <math.h>

AABB::AABB(float x1, float y1, float x2, float y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}

boolean AABB::inside(const float x, const float y) {
    return x >= x1 && x <= x2 && y >= y1 && y <= y2;
}

boolean AABB::inside(Vec2 &other) {
    return inside(other.get_x(), other.get_y());
}

boolean AABB::overlap(AABB &other) {
    return (inside(other.x1, other.y1) || inside(other.x1, other.y2)
        || inside(other.x2, other.y1) || inside(other.x2, other.y2)
        || other.inside(x1, y1));
}

AABB AABB::from_corners(Vec2 a, Vec2 b, Vec2 c, Vec2 d) {
    float left = fminf(fminf(fminf(a.get_x(), b.get_x()), c.get_x()), d.get_x());
    float right = fmaxf(fmaxf(fmaxf(a.get_x(), b.get_x()), c.get_x()), d.get_x());
    float top = fminf(fminf(fminf(a.get_y(), b.get_y()), c.get_y()), d.get_y());
    float bottom = fmaxf(fmaxf(fmaxf(a.get_y(), b.get_y()), c.get_y()), d.get_y());
    return AABB(left, top, right, bottom);
}
