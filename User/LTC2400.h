#ifndef __LTC2400_H_
#define __LTC2400_H_
#include "stm32f0xx.h"

#define LTC_SDO (GPIOA->IDR&GPIO_Pin_2)

#define LTC_SCK_H GPIOA->BSRR = GPIO_Pin_1
#define LTC_SCK_L GPIOA->BRR = GPIO_Pin_1

#define LTC_CS_H GPIOA->BSRR = GPIO_Pin_3
#define LTC_CS_L GPIOA->BRR = GPIO_Pin_3

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

u32 Read_LTC2400(void);
#endif