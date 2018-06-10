#ifndef __LQ12864_H_
#define __LQ12864_H_

//#include "codetab.h"
#include "stm32f0xx.h"

#define SCL_H GPIOA->BSRR = GPIO_Pin_7
#define SCL_L GPIOA->BRR = GPIO_Pin_7

#define SDA_H GPIOB->BSRR = GPIO_Pin_1
#define SDA_L GPIOB->BRR = GPIO_Pin_1

#define RST_H GPIOA->BSRR = GPIO_Pin_5
#define RST_L GPIOA->BRR = GPIO_Pin_5

#define DC_H GPIOA->BSRR = GPIO_Pin_6
#define DC_L GPIOA->BRR = GPIO_Pin_6

#define XLevelL		0x00
#define XLevelH		0x10
#define XLevel	      ((XLevelH&0x0F)*16+XLevelL)
#define Max_Column	128
#define Max_Row		64
#define Brightness	0xCF 
#define X_WIDTH 		128
#define Y_WIDTH 		64


void LCD_WrDat(unsigned char dat);
void LCD_WrCmd(unsigned char cmd);
void LCD_Set_Pos(unsigned char x, unsigned char y);
void LCD_Fill(unsigned char bmp_dat);
void LCD_CLS(void);
void LCD_Init(void);
void LCD_P6x8Str(unsigned char x, unsigned char y,unsigned char ch[]);
void LCD_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[]);
void LCD_P16x16Ch(unsigned char x,unsigned char y,unsigned char  N);
void Draw_BMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);

#endif