/*
 * oled.h
 *
 *  Created on: Jun 19, 2020
 *      Author: Administrator
 */

#ifndef INC_OLED_H_
#define INC_OLED_H_
#include "stm32l4xx_hal.h"

typedef unsigned char u8;
typedef unsigned int u32;

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
#define OLED_MODE 0

#define SIZE 8
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF
#define X_WIDTH 	128
#define Y_WIDTH 	64

#define SHORT_MARK 0
#define LONG_MARK 1

extern SPI_HandleTypeDef hspi1;

//-----------------OLED端口定义----------------


//OLED控制用函数

void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_SSD1306_Init(void);
void COG_ST7565_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_ShowString(u8 x,u8 y, u8 *p);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void oled_turnoff_screen(void);
void gram_draw_point(int x, int y);
void oled_refresh(void);
void gram_draw_vline(int x, int y, int length );
void gram_draw_hline(int x, int y, int length );

void gram_draw_triangle(int x1,int y1,int x2,int y2,int x3,int y3);
void gram_draw_triangle_indicator(int x, int y, int r, int len, int degree);
void gram_draw_degree_line(int x, int y, int r, int degree);
void gram_draw_arc(int x, int y, int r, int width, int begin, int end);
void gram_draw_arc_dash(int x, int y, int r, int width, int begin, int end);
void gram_draw_mark(int x, int y, int degree);
void gram_clear(void);
float get_dx(int,float);
float get_dy(int, float);
void gram_draw_blinking_bmp(int x, int y, int w, int h,
		const unsigned char *bmp);
void gram_draw_blinking_hline(int x, int y, int length);
void gram_draw_blinking_rectangle(int x, int y, int w, int h);
void gram_draw_blinking_corners(uint8_t x, uint8_t y, uint8_t w,
		uint8_t h, uint8_t len);
void gram_draw_string_6x8(int x, int y, char *str);
void gram_draw_num_string_10x10(int x, int y, char *str);
void gram_draw_num_string_08x10(int x, int y, char *str);
void gram_draw_num_string_08x10_slimdot(int x, int y, char *str);
void gram_draw_rectangle(int x, int y, int width, int height);
void gram_draw_num_string_12x12(int x, int y, char *str);
void gram_draw_num_string_12x12_blinking(int x, int y, char *str);
void gram_draw_num_string_10x10(int x, int y, char *str);
void gram_draw_num_string_10x10_blinking(int x, int y, char *str);
void gram_draw_bmp(int x, int y, int w, int h, const unsigned char *bmp);
void gram_draw_rectangle_no_outline(int x, int y, int width, int height);

#endif /* INC_OLED_H_ */
