
#ifndef __GPIO_HDQ_H__
#define __GPIO_HDQ_H__
#include "stm32f0xx.h"

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

#define HDQ0 GPIOA->BRR = GPIO_Pin_1
#define HDQ1 GPIOA->BSRR = GPIO_Pin_1
#define HDQ_In (GPIOA->IDR&GPIO_Pin_1)

void HDQ_Write_One(void);
void HDQ_Write_Zero(void);
void HDQ_Reset(void);
void HDQ_Send(u8 com,u8 dat);
u8 HDQ_Read(u8 add);


#endif
