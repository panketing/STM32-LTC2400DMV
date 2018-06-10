#include "stm32f0xx.h"
#include "delay.h"
#include "HDQ.h"
#include "GPIO_HDQ.h"
void HDQ_Write_One(void)
{
	HDQ1;
	HDQ0;
	delay_us(35);
	HDQ1;
	delay_us(190-35);
}

void HDQ_Write_Zero(void)
{
	HDQ1;
	HDQ0;
	delay_us(139);
	HDQ1;
	delay_us(190-139);
}

void HDQ_Reset()
{
	HDQ1;
	HDQ0;
	delay_us(210);
	HDQ1;
	delay_us(80);
}


void HDQ_Send(u8 com,u8 dat) //0:read 1:write
{
	u8 i;
	
	HDQ_Reset();
	for(i=0;i<8;i++)
	{
		if(i<7)
		{
			if(com&0x01)
				HDQ_Write_One();
			else
				HDQ_Write_Zero();
		}
		else
			HDQ_Write_One();
		com=com>>1;
	}
	for(i=0;i<20;i++);
	for(i=0;i<8;i++)
	{
		if(dat&0x01)
			HDQ_Write_One();
		else
			HDQ_Write_Zero();
		dat=dat>>1;
	}
}

u8 HDQ_Read(u8 add)
{
	u8 i,buf=0;
	u16 Time_Buf[10];
	u16 Time_temp;
	u32 Reload_Val=2000*(SystemCoreClock/8000000);
	HDQ_Reset();
	for(i=0;i<8;i++)
	{
		if(add&0x01)
			HDQ_Write_One();
		else
			HDQ_Write_Zero();
		add=add>>1;
	}
	for(i=0;i<20;i++);
	
	for(i=0;i<8;i++)
	{
		SysTick->LOAD=Reload_Val;		//�� 2000us ����װֵ �ݼ�����
		SysTick->VAL=0x00;   //��յδ�
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ; //��ʼ��ʱ
		while(HDQ_In)
		{
			if(SysTick->VAL<=10) return 0; //��ʱ����0
		}
		//��HDQ�½��ؿ�ʼʱ����ʼ��ʱ
		Time_temp=SysTick->VAL;  //�½���ʱ��
		while(!HDQ_In);	//��HDQ�����ؿ�ʼʱ��������ʱ  
		Time_Buf[i]=Time_temp-SysTick->VAL;//�½���ʱ��-������ʱ��
		SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; 
	}
	
//	for(i=0;i<8;i++)
//	{
//		SysTick->LOAD=Reload_Val;		//�� 2000us ����װֵ �ݼ�����
//		while(HDQ_In);	//��HDQ�½��ؿ�ʼʱ����ʼ��ʱ
//		SysTick->VAL=0x00;   //��յδ�
//		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ; //��ʼ��ʱ
//		while(!HDQ_In);	//��HDQ�����ؿ�ʼʱ��������ʱ
//		  
//		Time_Buf[i]=SysTick->VAL;//��¼��ʱֵ
//		SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; 
//	}
	
	for(i=0;i<8;i++)
	{
		buf>>=1;
		if((Time_Buf[i]/6)<=70)
		{
			buf|=0x80;
		}
	}
	return buf;
}
