#ifndef __LCD_5110_H__
#define __LCD_5110_H__

#define sce0   GPIOA->BRR = GPIO_Pin_7  //GPIO_ResetBits(GPIOB, GPIO_Pin_6)  //片选
#define res0   GPIOA->BRR = GPIO_Pin_5  //GPIO_ResetBits(GPIOB, GPIO_Pin_7)  //复位,0复位
#define dc0    GPIOA->BRR = GPIO_Pin_6  //GPIO_ResetBits(GPIOB, GPIO_Pin_8)   //1写数据，0写指令
#define sdin0  GPIOA->BRR = GPIO_Pin_3   
#define sclk0  GPIOA->BRR = GPIO_Pin_2   
 
#define sce1   GPIOA->BSRR = GPIO_Pin_7    //GPIO_SetBits(GPIOB, GPIO_Pin_6)  //片选
#define res1   GPIOA->BSRR = GPIO_Pin_5    //GPIO_SetBits(GPIOB, GPIO_Pin_7)  //复位,0复位
#define dc1    GPIOA->BSRR = GPIO_Pin_6    //GPIO_SetBits(GPIOB, GPIO_Pin_8)   //1写数据，0写指令
#define sdin1  GPIOA->BSRR = GPIO_Pin_3
#define sclk1  GPIOA->BSRR = GPIO_Pin_2

#define WIDTH    6
#define HEIGHT   8

void LCD_WriteByte(unsigned char dt, unsigned char command);
void LCD_Init(void);
void LCD_Set_XY(unsigned char X, unsigned char Y);
void LCD_Clear(void);
void LCD_WriteChar(unsigned char X,unsigned char Y,unsigned char c);
void LCD_WriteString_en(unsigned char X,unsigned char Y,char *s);
//void delay_mss(int t);

#endif