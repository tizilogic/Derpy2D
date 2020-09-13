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
#define ST7735S_CLOCK_SPEED 30000000
#define ST7735S_CPOL 0
#define ST7735S_CPHA 0
#define ST7735S_DEVICE 0
#define ST7735S_ORIENTATION 3
#define ST7735S_GAMMA 2
#define ST7735S_A0 24
#define ST7735S_RS 25
#define ST7735S_SCREEN_WIDTH 160
#define ST7735S_SCREEN_HEIGHT 128
#define ST7735S_BUFFER_SIZE 61440
#define ST7735S_SCREEN_SIZE 20480
/**************************** END CONFIGURATION END ***************************/

#include <circle/types.h>
#include <circle/spimaster.h>  /* TODO: Change to DMA */
#include <circle/gpiopin.h>


class LCD {
public:
    LCD(unsigned nClockSpeed = ST7735S_CLOCK_SPEED, unsigned CPOL = ST7735S_CPOL,
        unsigned CPHA = ST7735S_CPHA, unsigned nDevice = ST7735S_DEVICE,
        unsigned orientation = ST7735S_ORIENTATION, unsigned gamma = ST7735S_GAMMA,
        unsigned a0 = ST7735S_A0, unsigned rs = ST7735S_RS);
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
