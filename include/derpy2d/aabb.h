#ifndef _AABB_HPP_
#define _AABB_HPP_

#include <circle/types.h>
#include "vec.h"

class AABB {
public:
    AABB(float x1, float y1, float x2, float y2);

    boolean inside(const float x, const float y);
    boolean inside(Vec2 &other);
    boolean overlap(AABB &other);

    static AABB from_corners(Vec2 a, Vec2 b, Vec2 c, Vec2 d);

    float x1 = 0.0f, y1 = 0.0f, x2 = 1.0f, y2 = 1.0f;
};

#endif // _AABB_HPP_