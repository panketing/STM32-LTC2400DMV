#ifndef __LED_H
#define __LED_H

#include "stm32f0xx.h"

#define LED_OFF                       GPIOA->BRR = GPIO_Pin_4
#define LED_ON                        GPIOA->BSRR = GPIO_Pin_4 
#define LED_TURN                      GPIOA->ODR ^= GPIO_Pin_4

void LED_Init(void);

#endif
