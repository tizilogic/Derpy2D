/*
 * MIT License
 *
 * Copyright (c) 2020, Tiziano Bettio, github.com/tcdude
 *
 * Ported to be used in Circle from the implementation of Michal Kozakiewicz,
 * github.com/michal037
 */

#ifndef _LIBRARY_ST7735_
#define _LIBRARY_ST7735_

/* Pixel sizes */
#define ST7735S_PIXEL_FULL 1
#define ST7735S_PIXEL_REDUCED 0  /* Note: Not yet implemented */

/*
 * This setting determines the number of bits per pixel.
 * Choose the above pixel size, enter it in the configuration.
 * Without change, default value are selected.
 ******************************** CONFIGURATION *******************************/
#define ST7735S_CFG_PIXEL ST7735S_PIXEL_FULL
/**************************** END CONFIGURATION END ***************************/

#include <circle/types.h>
#include <circle/spimaster.h>
#include <circle/gpiopin.h>


class LCD {
public:
    LCD(unsigned nClockSpeed = 30000000, unsigned CPOL = 0, unsigned CPHA = 0,
        unsigned nDevice = 0, unsigned orientation = 0, unsigned gamma = 2,
        unsigned a0 = 24, unsigned rs = 25);
    ~LCD(void);
    void set_orientation(unsigned orientation = 0);
    void set_gamma(unsigned state = 2);
    void set_inversion(boolean state);
    u8 set_window(u8 x1, u8 y1, u8 x2, u8 y2);
    void push_px(u8 r, u8 g, u8 b);
    void draw_px(u8 x, u8 y, u8 r, u8 g, u8 b);
    void draw_buffer(u8* data, unsigned length);
private:
    void write_command(u8 cmd);
    void write_data(u8 data);
    void hardware_reset(void);

    CSPIMaster m_SPIMaster;
    CGPIOPin m_a0, m_rs;
    u8 width, height;
};


#endif // _LIBRARY_ST7735_
