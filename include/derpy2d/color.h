#ifndef _COLOR_HPP_
#define _COLOR_HPP_

#include <circle/types.h>

class Color {
public:
    Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f);
    boolean operator==(const Color &rhs);

    static Color transparent(void);
    static Color black(void);
    float r, g, b, a;
private:
};

#endif // _GRAPHICS_HPP_
