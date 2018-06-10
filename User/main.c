#include "stm32f0xx.h"
#include "LQ12864.h"
#include "delay.h"
#include "led.h"
#include "USART1.h"
#include "HDQ.h"
#include "GPIO_HDQ.h"
#include "LTC2400.h"

void GPIOX_Init(void);

int main(void)
{	
	u8 dispbuf[32];
	float Voltage;
	u32 vv,i,j,max,min;
	u32 ad[18];
	delay_init();
	LED_Init();
	GPIOX_Init();
	USART1_Init();	
	
	LCD_Init();
	LCD_CLS();
//	LCD_P8x16Str(0,0,"  LTC2400 DMV");
	LED_TURN;
	for(i=0;i<10;i++)
	{
		ad[i]=0;
	}
	i=0;
	max=0;min=0;
	while(1)
	{
		LED_TURN;
		ad[i]=Read_LTC2400();
		i++;
		if(i>=10) i=0;
		vv=0;
		max=0;min=0xffffffff;
		for(j=0;j<10;j++)	
		{
			vv+=ad[j];
			if(ad[j]>max) max=ad[j];
			if(ad[j]<min) min=ad[j];
		}
		vv=(vv-max-min)>>3;
		LED_TURN;
		Voltage=(float)(vv)*0.0009763875+0.2355;
		sprintf(dispbuf,"% 10.5fV DC",Voltage/1000.0f);	
		LCD_P8x16Str(0,2,dispbuf);   
		sprintf(dispbuf,"ADC:% 8d",vv);
		LCD_P8x16Str(0,4,dispbuf); 
		//LED_TURN;
	}	
}



void GPIOX_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* Ê¹ÄÜGPIOAÊ±ÖÓ */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //LTC2400 SDO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}


#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{

  while (1)
  {
  }
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
