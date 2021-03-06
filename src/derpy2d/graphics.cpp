#include "derpy2d/graphics.h"
#include "derpy2d/vec.h"
#include "derpy2d/aabb.h"

#include <assert.h>


Graphics::Graphics(void) {
    transform = Matrix3::identity();
}

void Graphics::begin(boolean clear, Color color) {
    assert(!drawing);
    if (clear) {
        clear_buffer(color);
    }
    drawing = true;
}

void Graphics::end(LCD &display) {
    assert(drawing);
    display.draw_buffer(buffer, 61440);
    drawing = false;
}

void Graphics::clear_buffer(Color color) {
    const unsigned o = 0;

    for (unsigned i = 0; i < 20480; ++i) {
        buffer[(o + i) * 3] = (u8)color.r;
        buffer[(o + i) * 3 + 1] = (u8)color.g;
        buffer[(o + i) * 3 + 2] = (u8)color.b;
        alpha[i] = (u8)color.a;
    }
}

void Graphics::draw_image(Image &img, float x, float y) {
    draw_sub_image(img, x, y, 0.0f, 0.0f, img.width(), img.height());
}

void Graphics::draw_sub_image(Image &img, float x, float y, float sx, float sy,
                              float sw, float sh) {
    assert(drawing);
    Vec2 origin = {x, y};
    Vec2 tl = {x, y};
    Vec2 tr = {x + sw - sx, y};
    Vec2 bl = {x, y + sh - sy};
    Vec2 br = {x + sw - sx, y + sh - sy};
    AABB dest = AABB::from_corners(transform * origin, transform * tr,
                                   transform * bl, transform * br);
    Matrix3 inv = transform.inverse();

    const int beginx = (int) (dest.x1 + 0.5f);
    const int beginy = (int) (dest.y1 + 0.5f);
    const int endx = (int) (dest.x2 + 1.5f);
    const int endy = (int) (dest.y2 + 1.5f);
    for (int by = beginy; by <= endy; ++by) {
        if (by < 0 || by >= 128) {
            continue;
        }

        for (int bx = beginx; bx <= endx; ++bx) {
            if (bx < 0 || bx >= 160) {
                continue;
            }
            Vec2 point = {(float)bx, (float)by};
            origin = inv * point - tl;
            float ox = origin.get_x(), oy = origin.get_y();
            if (ox < 0.0f || ox > sw - sx - 1.0f || oy < 0.0f || oy > sh - sy - 1.0f) {
                continue;
            }
            Color c = img.get_px(origin.get_x() + sx, origin.get_y() + sy);
            draw_px(bx, by, c);
        }
    }
}

void Graphics::draw_rect(float x, float y, float w, float h, float strength, Color color) {
    const int beginx = (int) (x + 0.5f);
    const int beginy = (int) (y + 0.5f);
    const int endx = (int) (x + w + 1.5f);
    const int endy = (int) (y + h + 1.5f);
    const int s = (int) (strength + 0.5f);

    for (int by = beginy; by <= endy; ++by) {
        if (by < 0 || by >= 128) {
            continue;
        }

        for (int bx = beginx; bx <= endx; ++bx) {
            if (bx < 0 || bx >= 160) {
                continue;
            }
            if (bx <= beginx + s || bx >= endx - s || by <= beginy + s || by >= endy - s) {
                draw_px(bx, by, color);
            }
        }
    }
}

void Graphics::fill_rect(float x, float y, float w, float h, Color color) {
    const int beginx = (int) (x + 0.5f);
    const int beginy = (int) (y + 0.5f);
    const int endx = (int) (x + w + 1.5f);
    const int endy = (int) (y + h + 1.5f);

    for (int by = beginy; by <= endy; ++by) {
        if (by < 0 || by >= 128) {
            continue;
        }

        for (int bx = beginx; bx <= endx; ++bx) {
            if (bx < 0 || bx >= 160) {
                continue;
            }
            draw_px(bx, by, color);
        }
    }
}

void Graphics::draw_px(int x, int y, Color& color) {
    float real_a = color.a * opacity;
    if (real_a <= 0.5f) {
        return;
    }
    unsigned pos = y * 160 + x;
    float r = (float)buffer[pos * 3], g = (float)buffer[pos * 3 + 1],
        b = (float)buffer[pos * 3 + 2], a = (float)alpha[pos];

    float prc = real_a >= 254.5f ? 1.0f : real_a / (real_a + a);
    r = color.r * prc + r * (1.0f - prc);
    g = color.g * prc + g * (1.0f - prc);
    b = color.b * prc + b * (1.0f - prc);
    a = real_a * prc + a * (1.0f - prc);
    buffer[pos * 3] = (u8)b;
    buffer[pos * 3 + 1] = (u8)g;
    buffer[pos * 3 + 2] = (u8)r;
    alpha[pos] = (u8)a;
}

void Graphics::set_transform(Matrix3 t) {
    transform = t;
}

void Graphics::clear_transform(void) {
    transform = Matrix3::identity();
}

void Graphics::set_opacity(const float alpha) {
    opacity = alpha;
    opacity = opacity < 0.0f ? 0.0f : (opacity > 1.0f ? 1.0f : opacity);
}
