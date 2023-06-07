/*
 * oled.c
 *
 *  Created on: Jun 19, 2020
 *      Author: Administrator
 */

#include "oled.h"
#include "bmp.h"
#include "oledfont.h"
#include "stm32l4xx_hal.h"
#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1415926

char gram[128 * 8];

void gram_clear(void) {
	memset(gram, 0, 128 * 8);
}

//draw a point
//x range 0~127
//y range 0~63
void gram_draw_point_1(int x, int y) {
	if (x < 0 || x > 127 || y < 0 || y > 63) {
		return;
	}
	gram[x + y / 8 * 128] |= 1 << y % 8;
}

//draw a point
//x range 0~127
//y range 0~63
void gram_draw_point_0(int x, int y) {
	if (x < 0 || x > 127 || y < 0 || y > 63) {
		return;
	}
	gram[x + y / 8 * 128] &= ~(1 << y % 8);
}

// x,y start index
// length length
void gram_draw_vline(int x, int y, int length) {
	for (int iy = y; iy <= y + length; iy++) {
		gram_draw_point_1(x, iy);
	}
}

void gram_draw_vline_0(int x, int y, int length) {
	for (int iy = y; iy <= y + length; iy++) {
		gram_draw_point_0(x, iy);
	}
}

// x,y start index
// length length
void gram_draw_hline(int x, int y, int length) {
	for (int ix = x; ix <= x + length; ix++) {
		gram_draw_point_1(ix, y);
	}
}

void gram_draw_hline_0(int x, int y, int length) {
	for (int ix = x; ix <= x + length; ix++) {
		gram_draw_point_0(ix, y);
	}
}

// Bresenham's line algorithm
void gram_draw_line(int x0, int y0, int x1, int y1) {
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2, e2;

	for (;;) {
		gram_draw_point_1(x0, y0);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = err;
		if (e2 > -dx) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy) {
			err += dx;
			y0 += sy;
		}
	}
}

//x,y定位gram中垂直字节，将其设为b
//如果y正好是0,8,16.... 那么直接拷贝b到gram即可，否则需要按位操作
void gram_set_vertical_bits(int x, int y, char b, int bits_of_last_layer) {
	if ((y % 8 == 0) && (bits_of_last_layer == 8)) { //正好是一个新行
		gram[x + y / 8 * 128] = b;
	} else {
		for (int i = 0; i <= bits_of_last_layer - 1; i++) {
			if ((b >> i) & 0x01) {
				gram_draw_point_1(x, y + i);
			} else {
				gram_draw_point_0(x, y + i);
			}
		}
	}
}

//在gram中贴bmp,y尽量是8的倍数，效率会高很多
void gram_draw_bmp(int x, int y, int w, int h, const unsigned char *bmp) {
	if (x < 0 || y < 0)
		return;
	// 先算有几层， 范围 0 ~ 7
	int idx = 0;
	int layer = (h - 1) / 8;
	int bits_of_last_layer = h % 8;
	if (h % 8 == 0) {
		bits_of_last_layer = 8;
	}
	for (int i = 0; i <= layer; i++) {
		for (int j = 0; j < w; j++) {
			if (i == layer) { // 最后一层，要写的bit数不是8了
				gram_set_vertical_bits(x + j, y + i * 8, bmp[idx++],
						bits_of_last_layer);
			} else {
				gram_set_vertical_bits(x + j, y + i * 8, bmp[idx++], 8);
			}
		}
	}
}

void gram_draw_char_6x8(int x, int y, char c) {
	gram_draw_bmp(x, y, 6, 8, (unsigned char*) F6x8[c - ' ']);
}

void gram_draw_char_12x12(int x, int y, char c) {
	gram_draw_bmp(x, y, 12, 12, (const unsigned char*) obitron1212[c - '-']);
}

/*
 *  for blinking, modifed from gram_draw_bmp()
 */
void gram_draw_blank(int x, int y, int w, int h) {
	if (x < 0 || y < 0)
		return;
	// 先算有几层， 范围 0 ~ 7
	int layer = (h - 1) / 8;
	int bits_of_last_layer = h % 8;
	if (h % 8 == 0) {
		bits_of_last_layer = 8;
	}
	for (int i = 0; i <= layer; i++) {
		for (int j = 0; j < w; j++) {
			if (i == layer) { // 最后一层，要写的bit数不是8了
				gram_set_vertical_bits(x + j, y + i * 8, 0x00,
						bits_of_last_layer);
			} else {
				gram_set_vertical_bits(x + j, y + i * 8, 0x00, 8);
			}
		}
	}
}


void gram_draw_char_10x10(int x, int y, char c) {
	gram_draw_bmp(x, y, 10, 10, (const unsigned char*) obitron1010[c - '-']);
}

void gram_draw_char_08x10(int x, int y, char c) {
	gram_draw_bmp(x, y, 8, 10, (const unsigned char*) obitron0810[c - '-']);
}

//str = -0.123456789
void gram_draw_num_string_12x12(int x, int y, char *str) {
	int l = strlen(str);
	for (int i = 0; i < l; i++) {
		gram_draw_char_12x12(x + i * 13, y, *str++);
	}
}

/*
 * for blinking
 */
void gram_draw_num_string_12x12_blank(int x, int y, char *str) {
	int l = strlen(str);
	for (int i = 0; i < l; i++) {
		gram_draw_blank(x + i * 13, y, 12, 12);
	}
}

void gram_draw_num_string_12x12_blinking(int x, int y, char *str) {
	static int last = 0;
	static int solid = 1;
	int now = HAL_GetTick();
	int duration = now - last;

	if (duration <= 500) {
		if (solid == 1) {
			gram_draw_num_string_12x12(x, y, str);
		} else {
			gram_draw_num_string_12x12_blank(x, y, str);
		}
	} else {
		last = now;
		solid = solid == 0 ? 1 : 0;
	}
}

void gram_draw_num_string_10x10_blank(int x, int y, char *str) {
	int l = strlen(str);
	for (int i = 0; i < l; i++) {
		gram_draw_blank(x + i * 11, y, 10, 10);
	}
}

void gram_draw_num_string_10x10_blinking(int x, int y, char *str) {
	static int last = 0;
	static int solid = 1;
	int now = HAL_GetTick();
	int duration = now - last;

	if (duration <= 500) {
		if (solid == 1) {
			gram_draw_num_string_10x10(x, y, str);
		} else {
			gram_draw_num_string_10x10_blank(x, y, str);
		}
	} else {
		last = now;
		solid = solid == 0 ? 1 : 0;
	}
}

void gram_draw_num_string_10x10(int x, int y, char *str) {
	int l = strlen(str);
	for (int i = 0; i < l; i++) {
		gram_draw_char_10x10(x + i * 11, y, *str++);
	}
}

void gram_draw_num_string_08x10(int x, int y, char *str) {
	int l = strlen(str);
	for (int i = 0; i < l; i++) {
		gram_draw_char_08x10(x + i * 9, y, *str++);
	}
}

void gram_draw_slim_dot(int x, int y) {
	gram_draw_bmp(x, y, 6, 8, (const unsigned char*) F6x8[14]);
}

void gram_draw_num_string_08x10_slimdot(int x, int y, char *str) {
	int l = strlen(str);
	char reach_dot = 0;
	for (int i = 0; i < l; i++) {
		char c = *str++;
		if(c == '.')
			reach_dot = 1;

		if(!reach_dot)
			gram_draw_char_08x10(x + i * 9, y, c);
		else if(c == '.')
			gram_draw_slim_dot(x + i * 9 - 1, y + 2);
		else
			gram_draw_char_08x10(x + i * 9 - 4, y, c);
	}
}

void gram_draw_string_6x8(int x, int y, char *str) {
	int l = strlen(str);
	for (int i = 0; i < l; i++) {
		gram_draw_char_6x8(x + i * 6, y, *str++);
	}
}



float get_dx(int r, float rad) {
	float dx = r * cos(rad);
	// 4舍5入
	if (dx > 0) {
		dx += 0.5;
	} else if (dx < 0) {
		dx -= 0.5;
	}
	return dx;
}

float get_dy(int r, float rad) {
	float dy = r * sin(rad);
	// 4舍5入
	if (dy > 0) {
		dy += 0.5;
	} else if (dy < 0) {
		dy -= 0.5;
	}
	return dy;
}

void gram_draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
	gram_draw_line(x1, y1, x2, y2);
	gram_draw_line(x2, y2, x3, y3);
	gram_draw_line(x3, y3, x1, y1);
}

void gram_draw_rectangle(int x, int y, int width, int height) {
	gram_draw_hline(x, y, width);
	gram_draw_hline(x, y + height, width);
	gram_draw_vline(x, y, height);
	gram_draw_vline(x + width, y, height);
}

void gram_draw_rectangle_0(int x, int y, int width, int height) {
	gram_draw_hline_0(x, y, width);
	gram_draw_hline_0(x, y + height, width);
	gram_draw_vline_0(x, y, height);
	gram_draw_vline_0(x + width, y, height);
}

void gram_draw_blank_rectangle(int x, int y, int width, int height) {
	gram_draw_rectangle(x, y, width, height);

	for (int i = x + 1; i < x + width; i++) {
		for (int j = y + 1; j < y + height; j++) {
			gram_draw_point_0(i, j);
		}
	}
}

void gram_draw_rectangle_no_outline(int x, int y, int width, int height) {
	for (int i = x + 1; i < x + width; i++) {
		for (int j = y + 1; j < y + height; j++) {
			gram_draw_point_0(i, j);
		}
	}
}


// x, y  -  center of the arc
// with  -  width of the arc
// begin,end  - start and end degrees of the arc
void gram_draw_arc(int x, int y, int r, int width, int begin, int end) {

	for (int deg = begin; deg <= end; deg += 1) {
		float radian = deg * PI / 180;
		float dx = get_dx(r, radian);
		float dy = get_dy(r, radian);
		for (int i = 0; i < width; i++) {
			gram_draw_point_1((int) (x + dx + i - width / 2), (int) (y - dy));
		}

	}
}

void gram_draw_arc_dash(int x, int y, int r, int width, int begin, int end) {
	for (int i = begin; i <= end; i += 6) {
		gram_draw_arc(x, y, r, width, i, i + 1);
	}
}

void gram_draw_degree_line(int x, int y, int r, int degree) {
	float radian = degree * PI / 180;

	float dx = r * cos(radian);
	float dy = r * sin(radian);

	// 4舍5入
	if (dx > 0) {
		dx += 0.5;
	} else if (dx < 0) {
		dx -= 0.5;
	}

	if (dy > 0) {
		dy += 0.5;
	} else if (dy < 0) {
		dy -= 0.5;
	}

	gram_draw_line((int) (x + dx), (int) (y - dy), (int) (x - dx),
			(int) (y + dy));
}



void gram_draw_blinking_hline(int x, int y, int length) {
	static int last = 0;
	static int solid = 1;
	int now = HAL_GetTick();
	int duration = now - last;

	if (duration <= 500) {
		if (solid == 1) {
			for (int ix = x; ix <= x + length; ix++) {
				gram_draw_point_1(ix, y);
			}
		} else {
			for (int ix = x; ix <= x + length; ix++) {
				gram_draw_point_0(ix, y);
			}
		}
	} else {
		last = now;
		solid = solid == 0 ? 1 : 0;
	}
}

void gram_draw_blinking_rectangle(int x, int y, int w, int h) {
	static int last = 0;
	static int solid = 1;
	int now = HAL_GetTick();
	int duration = now - last;

	if (duration <= 500) {
		if (solid == 1) {
			gram_draw_rectangle(x, y, w, h);
		} else {
			gram_draw_rectangle_0(x, y, w, h);
		}
	} else {
		last = now;
		solid = solid == 0 ? 1 : 0;
	}
}

void gram_draw_blinking_bmp(int x, int y, int w, int h,
		const unsigned char *bmp) {
	static int last = 0;
	static int solid = 1;
	int now = HAL_GetTick();
	int duration = now - last;

	if (duration <= 500) {
		if (solid == 1) {
			gram_draw_bmp(x, y, w, h, bmp);
		} else {
			gram_draw_blank_rectangle(x, y, w, h);
		}
	} else {
		last = now;
		solid = solid == 0 ? 1 : 0;
	}
}

/*
 *
 *  len - the length of the corner lines
 *
 */

void gram_draw_blinking_corners(uint8_t x, uint8_t y, uint8_t w,
		uint8_t h, uint8_t len) {
	uint8_t ulx = x;
	uint8_t uly = y;
	uint8_t urx = x + w;
	uint8_t ury = y;

	uint8_t llx = x;
	uint8_t lly = y + h;
	uint8_t lrx = x + w;
	uint8_t lry = y + h;

	static int last = 0;
	static int solid = 1;
	int now = HAL_GetTick();
	int duration = now - last;

	if (duration <= 500) {
		if (solid == 1) {
			//upper left corner
			gram_draw_hline(ulx, uly, len);
			gram_draw_vline(ulx, uly, len);

			//upper right corner
			gram_draw_hline(urx - len, ury, len);
			gram_draw_vline(urx, ury, len);

			//lower left corner
			gram_draw_hline(llx, lly, len);
			gram_draw_vline(llx, lly - len, len);

			//lower right corner
			gram_draw_hline(lrx - len, lry, len);
			gram_draw_vline(lrx, lry - len, len);

		} else {
			//upper left corner
			gram_draw_hline_0(ulx, uly, len);
			gram_draw_vline_0(ulx, uly, len);

			//upper right corner
			gram_draw_hline_0(urx - len, ury, len);
			gram_draw_vline_0(urx, ury, len);

			//lower left corner
			gram_draw_hline_0(llx, lly, len);
			gram_draw_vline_0(llx, lly - len, len);

			//lower right corner
			gram_draw_hline_0(lrx - len, lry, len);
			gram_draw_vline_0(lrx, lry - len, len);
		}
	} else {
		last = now;
		solid = solid == 0 ? 1 : 0;
	}
}

// push gram into oled ram
void oled_refresh(void) {
	for (int y = 0; y < 8; y++) {
		OLED_Set_Pos(0, y);
		//Write data
		OLED_DC_Set();
		//for(int x = 0; x < 128; x++) {
		//	HAL_SPI_Transmit(&hspi1, &gram[y*128+x], 1, 10);
		//}
		// TODO:USE HAL SPI DMA
		HAL_SPI_Transmit(&hspi1, (uint8_t*) &gram[y * 128], 128, 10);
	}

}

void OLED_WR_Byte(u8 dat, u8 cmd) {
	if (cmd)
		OLED_DC_Set();
	else
		OLED_DC_Clr();

	HAL_SPI_Transmit(&hspi1, &dat, 1, 1);

	OLED_DC_Set();
}

void OLED_Set_Pos(unsigned char x, unsigned char y) {
	OLED_WR_Byte(0xb0 + y, OLED_CMD);	// Page Addressing Mode 设置页地址(0<=y<=7)

#ifdef SH1106
	x += 2; // SH1106 start from column 0x02
#endif

#if(defined ST7565 && defined LCD_UPSIDEDOWN)
	x += 4;
#endif

	OLED_WR_Byte((x & 0x0f), OLED_CMD); //Page Addressing Mode, 设置列低4位
	OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10, OLED_CMD); //Page Addressing Mode, 设置列高4位
}

void OLED_Display_On(void) {
	OLED_WR_Byte(0X8D, OLED_CMD); //SET DCDC锟斤拷锟斤拷
	OLED_WR_Byte(0X14, OLED_CMD); //DCDC ON
	OLED_WR_Byte(0XAF, OLED_CMD); //DISPLAY ON
}

void OLED_Display_Off(void) {
	OLED_WR_Byte(0X8D, OLED_CMD); //SET DCDC锟斤拷锟斤拷
	OLED_WR_Byte(0X10, OLED_CMD); //DCDC OFF
	OLED_WR_Byte(0XAE, OLED_CMD); //DISPLAY OFF
}

void OLED_Clear(void) {
	u8 i, n;
	for (i = 0; i < 8; i++) {
		OLED_Set_Pos(0, i);
#ifdef ST7565
		for (n = 0; n < 132; n++)
#endif

#ifdef SSD1306
		for (n = 0; n < 128; n++)
#endif
			OLED_WR_Byte(0, OLED_DATA);
	}

}

//x:0~127
//y:0~7
void OLED_ShowChar(u8 x, u8 y, u8 chr) {
	unsigned char c = 0, i = 0;
	c = chr - ' ';
	if (x > Max_Column - 1) {
		x = 0;
		y = y + 2;
	}
	if (SIZE == 16) {
		OLED_Set_Pos(x, y);
		for (i = 0; i < 8; i++)
			OLED_WR_Byte(F8X16[c * 16 + i], OLED_DATA);

		OLED_Set_Pos(x, y + 1);
		for (i = 0; i < 8; i++)
			OLED_WR_Byte(F8X16[c * 16 + i + 8], OLED_DATA);
	} else {
		OLED_Set_Pos(x, y + 1);
		for (i = 0; i < 6; i++)
			OLED_WR_Byte(F6x8[c][i], OLED_DATA);
	}
}

void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1,
		unsigned char y1, unsigned char BMP[]) {
	unsigned int j = 0;
	unsigned char x, y;

	if (y1 % 8 == 0)
		y = y1 / 8;
	else
		y = y1 / 8 + 1;
	for (y = y0; y < y1; y++) {
		OLED_Set_Pos(x0, y);
		for (x = x0; x < x1; x++) {
			OLED_WR_Byte(BMP[j++], OLED_DATA);
		}
	}
}


void oled_turnoff_screen() {
#ifdef ST7565
	OLED_WR_Byte(0xAE, OLED_CMD);
#endif
}

//SSD1306 initiation
//Also works for SH1106
void OLED_SSD1306_Init(void) {

	OLED_RST_Set();
	HAL_Delay(10);
	OLED_RST_Clr();
	HAL_Delay(10);
	OLED_RST_Set();

	OLED_WR_Byte(0xAE, OLED_CMD); //--turn  oled panel
	OLED_WR_Byte(0x00, OLED_CMD); //---set low column address
	OLED_WR_Byte(0x10, OLED_CMD); //---set high column address
	OLED_WR_Byte(0x40, OLED_CMD); //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81, OLED_CMD); //--set contrast control register
	OLED_WR_Byte(0xCF, OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1, OLED_CMD); //--Set SEG/Column Mapping
	OLED_WR_Byte(0xC8, OLED_CMD); //Set COM/Row Scan Direction
	OLED_WR_Byte(0xA6, OLED_CMD); //--set normal display
	OLED_WR_Byte(0xA8, OLED_CMD); //--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f, OLED_CMD); //--1/64 duty
	OLED_WR_Byte(0xD3, OLED_CMD); //-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00, OLED_CMD); //-not offset
	OLED_WR_Byte(0xd5, OLED_CMD); //--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0xF0, OLED_CMD); //--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9, OLED_CMD); //--set pre-charge period
	OLED_WR_Byte(0xF1, OLED_CMD); //Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA, OLED_CMD); //--set com pins hardware configuration
	OLED_WR_Byte(0x12, OLED_CMD);
	OLED_WR_Byte(0xDB, OLED_CMD); //--set vcomh
	OLED_WR_Byte(0x40, OLED_CMD); //Set VCOM Deselect Level
	OLED_WR_Byte(0x20, OLED_CMD); //-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02, OLED_CMD); //  0x02 -- Page addressing mode
	OLED_WR_Byte(0x8D, OLED_CMD); //--set Charge Pump enable/disable
	OLED_WR_Byte(0x14, OLED_CMD); //--set(0x10) disable
	OLED_WR_Byte(0xA4, OLED_CMD); // Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6, OLED_CMD); // Disable Inverse Display On (0xa6/a7)
	OLED_WR_Byte(0xAF, OLED_CMD); //--turn on oled panel

	OLED_WR_Byte(0xAF, OLED_CMD); /*display ON*/
	OLED_Clear();
	OLED_Set_Pos(0, 0);
}

//ST7565 initiation
void COG_ST7565_Init(void) {

	OLED_RST_Set();
	HAL_Delay(10);
	OLED_RST_Clr();
	HAL_Delay(10);
	OLED_RST_Set();

	OLED_WR_Byte(0xE2, OLED_CMD); //-- Reset

#ifdef LCD_UPSIDEDOWN
	OLED_WR_Byte(0xA1, OLED_CMD); //---左右 A0正向 A1反向
	OLED_WR_Byte(0xC0, OLED_CMD); //---上下 C0正向 C8反向
#else
	OLED_WR_Byte(0xA0, OLED_CMD); //---左右 A0正向 A1反向
	OLED_WR_Byte(0xC8, OLED_CMD); //---上下 C0正向 C8反向
#endif

	OLED_WR_Byte(0x2F, OLED_CMD); //-- 打开内部电源

	OLED_WR_Byte(0x27, OLED_CMD); // Set regulation resistor ratio
	OLED_WR_Byte(0xAF, OLED_CMD); // Display  ON

#ifdef JHD_16
	/*
	 * Set display start line from the middle the 32nd line
	 * This is a workaround for for JHD 1.6'' screen  only
	 */
	OLED_WR_Byte(0x60, OLED_CMD);

#else
	OLED_WR_Byte(0x40, OLED_CMD); //Set display start line
#endif

	OLED_WR_Byte(0xA6, OLED_CMD); // A6正常 A7反显

	OLED_WR_Byte(0xA4, OLED_CMD); // A4正常显示, A5所有都点亮

	OLED_WR_Byte(0xA2, OLED_CMD); // Bias 设置 A2 - 1/9 A3 - 1/7

	OLED_WR_Byte(0x81, OLED_CMD); // 设置对比度？
	OLED_WR_Byte(0x04, OLED_CMD); // 0x01 0x02 0x04 0x08 0x10 0x20

	OLED_WR_Byte(0xF8, OLED_CMD); //设置电压booster 开关
	OLED_WR_Byte(0x00, OLED_CMD); // 0x00 X4  0x01 X5


	OLED_Clear();
	OLED_Set_Pos(0, 0);
}

