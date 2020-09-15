#ifndef _GRAPHICS_HPP_
#define _GRAPHICS_HPP_

#include <circle/types.h>
#include <circle/new.h>
#include "derpy2d/st7735.h"
#include "derpy2d/color.h"
#include "derpy2d/image.h"
#include "derpy2d/matrix.h"
#include <vector>

class Graphics {
public:
    Graphics(void);
    //void set_display(LCD *display);
    void begin(boolean clear = true, Color color = Color::transparent());
    void end(LCD &display);
    void clear_buffer(Color color);
    void draw_image(Image &img, float x, float y);
    void draw_sub_image(Image &img, float x, float y, float sx, float sy, float sw, float sh);
    void draw_rect(float x, float y, float w, float h, float strength, Color color);
    void fill_rect(float x, float y, float w, float h, Color color);
    void set_transform(Matrix3 t);
    void clear_transform(void);
    void set_opacity(const float alpha);
private:
    void draw_px(int x, int y, Color& color);

    Matrix3 transform;
    u8 buffer[ST7735S_BUFFER_SIZE];
    u8 alpha[ST7735S_SCREEN_SIZE];
    float opacity = 1.0;
    boolean drawing = false;
};

#endif // _GRAPHICS_HPP_
