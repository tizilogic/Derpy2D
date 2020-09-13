#include "derpy2d/color.h"

Color Color::transparent(void) {
    return Color();
}

Color Color::black(void) {
    return Color(0, 0, 0, 255);
}

Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
