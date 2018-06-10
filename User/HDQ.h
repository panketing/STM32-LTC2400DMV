#ifndef __HDQ_H__
#define __HDQ_H__
#include "stm32f0xx.h"
#include "delay.h"
#include "led.h"
#include "USART1.h"
#include "HDQ.h"
#include "GPIO_HDQ.h"

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;


u16 Ctrl_Cmd(u16 cmd);
void SealPack(void);
void UnSealPack(u32 Key);
void Read_Block_A(u8 *);
void Read_Block_B(u8 *);
void Read_LT_Data(u8 *);
void Read_Cal_Data(u8 *);
void Read_LT_Data_Sealed(u8 *block);
void Read_PCMSN_Sealed(u8 *block);
void Read_BarCode_Sealed(u8 *block);
void Read_LT_Res(u8 *block);
void WriteBlockData(u8 *);
u8 Cal_CheckSum(u8 *,u8);
void Rewrite_CycleCount(void);
void Read_Block_Data(u16 SubClass,u8 Block,u8 *ablock);
void Write_Block_Data(u16 SubClass,u8 Block,u8 *dat);
u16 GetCycleCount(void);
void ShowCheckSums(void);
u16 GetSOC(void);
u16 GetVoltage(void);

s16 GetCurrent(void);
s16 GetNTCTemp(void);
float GetNTCTempf(void);

#endif
