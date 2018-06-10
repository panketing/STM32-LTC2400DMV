#include "LTC2400.h"
#include "stm32f0xx.h"

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

u32 Read_LTC2400(void)
{
	unsigned char i; 
	unsigned long v=0;   //v是AD转换结果
	LTC_CS_L;
	while(LTC_SDO);
	for(i=0;i<32;i++)
	{
		LTC_SCK_H; 
		delay_ms(1);
		v <<= 1;
		if(LTC_SDO) v++;
		LTC_SCK_L; 
		delay_ms(1);
	}
	LTC_CS_H;
	return ((v>>4)&0xffffff);
}