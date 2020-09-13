/*
 * MIT License
 *
 * Copyright (c) 2020, Tiziano Bettio, github.com/tcdude
 *
 * Ported to be used in Circle from the implementation of Michal Kozakiewicz,
 * github.com/michal037
 */

#include "derpy2d/st7735.h"

#include <circle/timer.h>

LCD::LCD(unsigned nClockSpeed, unsigned CPOL, unsigned CPHA, unsigned nDevice,
		 unsigned orientation, unsigned gamma, unsigned a0, unsigned rs)
: m_SPIMaster (nClockSpeed, CPOL, CPHA, nDevice), m_a0(a0, GPIOModeOutput),
  m_rs(rs, GPIOModeOutput) {
	m_SPIMaster.Initialize();

	hardware_reset();

	/* Software reset; Wait minimum 120ms */
	write_command(0x01);
	CTimer::SimpleMsDelay(150);

	/* Sleep out; Wait minimum 120ms */
	write_command(0x11);
	CTimer::SimpleMsDelay(150);

	/* Set orientation and the gamma */
	set_orientation(orientation);
	set_gamma(gamma);

	/* Set the pixel format */
	write_command(0x3A);
	#if ST7735S_CFG_PIXEL == ST7735S_PIXEL_FULL
		write_data(0x06);
	#elif ST7735S_CFG_PIXEL == ST7735S_PIXEL_REDUCED
		write_data(0x03);
	#endif
	CTimer::SimpleMsDelay(100);

	/* Display ON; Wait 100ms before start */
	write_command(0x29);
	CTimer::SimpleMsDelay(100);

	set_orientation(orientation);  /* Hack to make the display responsive */

	u8 buff[61440];  /* Clear the buffer to black */
	for (int i = 0; i < 61440; ++i) {
		buff[i] = 0;
	}
	draw_buffer(buff, 61440);
}

LCD::~LCD(void) {
	hardware_reset();
}

void LCD::write_command(u8 cmd) {
	m_a0.Write(LOW);
	m_SPIMaster.Write(0, &cmd, 1);
}

void LCD::write_data(u8 data) {
	m_a0.Write(HIGH);
	m_SPIMaster.Write(0, &data, 1);
}

void LCD::draw_buffer(u8* data, unsigned length) {
	m_a0.Write(HIGH);
	m_SPIMaster.Write(0, data, length);
}

void LCD::hardware_reset(void) {
	m_rs.Write(HIGH);
	m_rs.Write(LOW);
	CTimer::SimpleMsDelay(10);
	m_rs.Write(HIGH);
	CTimer::SimpleMsDelay(150);
}

void LCD::set_orientation(unsigned orientation) {
	write_command(0x36); /* Memory Data Access Control */

	switch (orientation)
	{
		case 1:
			write_data(0x60); /* MX + MV */
			width  = 160;
			height = 128;
			set_window(0, 0, 159, 127);
			break;

		case 2:
			write_data(0xC0); /* MY + MX */
			width  = 128;
			height = 160;
			set_window(0, 0, 127, 159);
			break;

		case 3:
			write_data(0xA0); /* MY + MV */
			width  = 160;
			height = 128;
			set_window(0, 0, 159, 127);
			break;

		default:
			write_data(0x00); /* None */
			width  = 128;
			height = 160;
			set_window(0, 0, 127, 159);
			break;
	}
}

void LCD::set_gamma(unsigned state) {
	/* The status (0 or 1) of the GS pin can only be empirically tested */
	switch(state)
	{
		case 1:  state = 2; break; /* GS_pin=1: 1.8; GS_pin=0: 2.5 */
		case 2:  state = 4; break; /* GS_pin=1: 2.5; GS_pin=0: 2.2 */
		case 3:  state = 8; break; /* GS_pin=1: 1.0; GS_pin=0: 1.8 */
		default: state = 1; break; /* GS_pin=1: 2.2; GS_pin=0: 1.0 */
	}

	/* Set built-in gamma */
	write_command(0x26);
	write_data(state);
}

void LCD::set_inversion(boolean state) {
	/* Display inversion ON/OFF */
	write_command(state ? 0x21 : 0x20);
}

u8 LCD::set_window(u8 x1, u8 y1, u8 x2, u8 y2) {
	/* Accept: 0 <= x1 <= x2 < activeDisplay->width */
	if(x2 < x1) return 1;
	if(x2 >= width) return 1;

	/* Accept: 0 <= y1 <= y2 < activeDisplay->height */
	if(y2 < y1) return 1;
	if(y2 >= height) return 1;

	/* Set column address */
	write_command(0x2A);
	write_data(0); write_data(x1);
	write_data(0); write_data(x2);

	/* Set row address */
	write_command(0x2B);
	write_data(0); write_data(y1);
	write_data(0); write_data(y2);

	/* Activate RAW write */
	write_command(0x2C);

	return 0;
}

void LCD::push_px(u8 r, u8 g, u8 b) {
	write_data(r); write_data(g); write_data(b);
}

void LCD::draw_px(u8 x, u8 y, u8 r, u8 g, u8 b) {
	if(set_window(x, y, x, y)) return;
	write_data(r); write_data(g); write_data(b);
}
