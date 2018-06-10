
#include "HDQ.h"
//#include "UART_HDQ.h"
#include "stdio.h"
#include "LCD_5110.h"
u16 Ctrl_Cmd(u16 cmd)  //37 90 94 59 
{
	u8 hh,ll;
	HDQ_Send(0x00,cmd);
	delay_ms(20);
	HDQ_Send(0x01,cmd>>8);
	delay_ms(20);
	ll=HDQ_Read(0x00);
	delay_ms(20);
	hh=HDQ_Read(0x01);
	return ((u16)(hh)<<8)|ll;
}

//void Read_Block_A(u8 *ablock)
//{
//	u8 i,baseaddr;
//	
//	HDQ_Send(0x61,0x00);delay_ms(30);
//	HDQ_Send(0x3e,58);delay_ms(30);
//	HDQ_Send(0x3f,0x00);delay_ms(30);
//	baseaddr=0x40;
//	for(i=0;i<32;i++)
//	{
//		ablock[i]=HDQ_Read(baseaddr);
//		baseaddr++;
//	}
//}

//void Read_Block_B(u8 *ablock)
//{
//	u8 i,baseaddr;
//	
//	HDQ_Send(0x61,0x00);delay_ms(30);
//	HDQ_Send(0x3e,58);  delay_ms(30);
//	HDQ_Send(0x3f,0x01);delay_ms(30);
//	baseaddr=0x40;
//	for(i=0;i<18;i++)
//	{
//		ablock[i]=HDQ_Read(baseaddr);
//		baseaddr++;
//	}
//}


//void WriteBlockData(u8 *dat)
//{
//	u8 i,baseaddr,cs;
//	baseaddr=0x40;
//	for(i=0;i<32;i++)
//	{
//		HDQ_Send(baseaddr,dat[i]);
//		baseaddr++;
//	}
//	cs=Cal_CheckSum(dat,32);
//	HDQ_Send(0x60,cs);
//}

//void Read_LT_Data(u8 *block)
//{
//	u8 i,baseaddr;
//	HDQ_Send(0x61,0x00);delay_ms(30);
//	HDQ_Send(0x3e,59);  delay_ms(30);
//	HDQ_Send(0x3f,0x00);delay_ms(30);
//	baseaddr=0x40;
//	for(i=0;i<32;i++)
//	{
//		block[i]=HDQ_Read(baseaddr);
//		baseaddr++;
//	}
//}

void Read_Cal_Data(u8 *block)
{
	u8 i,baseaddr;
	HDQ_Send(0x61,0x00);delay_ms(20);
	HDQ_Send(0x3e,104);  delay_ms(20);
	HDQ_Send(0x3f,0x00);delay_ms(20);
	baseaddr=0x40;
	for(i=0;i<32;i++)
	{
		block[i]=HDQ_Read(baseaddr);
		baseaddr++;
	}
}

//void Read_LT_Data_Sealed(u8 *block)
//{
//	u8 i,baseaddr;
//	HDQ_Send(0x3f,0x04);delay_ms(30);
//	baseaddr=0x40;
//	for(i=0;i<32;i++)
//	{
//		block[i]=HDQ_Read(baseaddr);
//		baseaddr++;
//	}
//}

//void Read_PCMSN_Sealed(u8 *block)
//{
//	u8 i,baseaddr;
//	HDQ_Send(0x3f,0x01);delay_ms(30);
//	baseaddr=0x40;
//	for(i=0;i<32;i++)
//	{
//		block[i]=HDQ_Read(baseaddr);
//		baseaddr++;
//	}
//}

//void Read_BarCode_Sealed(u8 *block)
//{
//	u8 i,baseaddr;
//	HDQ_Send(0x3f,0x02);delay_ms(30);
//	baseaddr=0x40;
//	for(i=0;i<32;i++)
//	{
//		block[i]=HDQ_Read(baseaddr);
//		baseaddr++;
//	}
//}

//void Read_LT_Res(u8 *block)
//{
//	u8 i,baseaddr;
//	HDQ_Send(0x61,0x00);
//	HDQ_Send(0x3e,0x42);
//	HDQ_Send(0x3f,0x00);
//	baseaddr=0x40;
//	for(i=0;i<32;i++)
//	{
//		block[i]=HDQ_Read(baseaddr);
//		baseaddr++;
//	}	
//}

u8 Cal_CheckSum(u8 *data,u8 len)
{
	u32 sum=0;
	u8 i,cs;
	for(i=0;i<len;i++)
	{
		sum+=data[i];
	}
	cs=255-(sum&0x000000ff);
	return cs;
}

//u16 GetCycleCount(void)
//{
//	u8 hh,ll;
//	ll=HDQ_Read(0x2a);
//	delay_ms(10);
//	hh=HDQ_Read(0x2b);
//	return ((u16)(hh)<<8)|ll; // HDQ_Read(0x2b)<<8|HDQ_Read(0x2a)
//}

s16 GetNTCTemp(void)
{
	u8 hh,ll;
	ll=HDQ_Read(0x06);
	delay_ms(10);
	hh=HDQ_Read(0x07);
	return (s16)((((u16)(hh)<<8)|ll));
}

float GetNTCTempf(void)
{

	return (float)(GetNTCTemp()*10-27315)/100;
}


//s16 GetIntTemp(void)
//{
//	u8 hh,ll;
////	float tt;
//	ll=HDQ_Read(0x20);
//	delay_ms(10);
//	hh=HDQ_Read(0x21);
//	//tt=(float)((((u16)(hh)<<8)|ll));
//	//return tt; // 
//	return (s16)((((u16)(hh)<<8)|ll));///-2731;
//}


u16 GetRM(void)
{
	u8 hh,ll;
	ll=HDQ_Read(0x10);
	delay_ms(1);
	hh=HDQ_Read(0x11);
	return ((u16)(hh)<<8)|ll; 
}	

u16 GetFCC(void)
{
	u8 hh,ll;
	ll=HDQ_Read(0x12);
	delay_ms(1);
	hh=HDQ_Read(0x13);
	return ((u16)(hh)<<8)|ll; 
}

u16 GetFAC(void)
{
	u8 hh,ll;
	ll=HDQ_Read(0x0e);
	delay_ms(1);
	hh=HDQ_Read(0x0f);
	return ((u16)(hh)<<8)|ll; 
}

u16 GetQmax(void)
{
	u8 hh,ll;
	ll=HDQ_Read(0x22);
	delay_ms(1);
	hh=HDQ_Read(0x23);
	return ((u16)(hh)<<8)|ll; 
}

u16 GetSOC(void)
{
	u8 hh,ll;
	ll=HDQ_Read(0x2c);
	delay_ms(3);
	hh=HDQ_Read(0x2d);
	return ((u16)(hh)<<8)|ll; // HDQ_Read(0x2b)<<8|HDQ_Read(0x2a)
}

u16 GetVoltage(void)
{
	u8 hh,ll;
	ll=HDQ_Read(0x08);
	delay_ms(3);
	hh=HDQ_Read(0x09);
	return ((u16)(hh)<<8)|ll; // HDQ_Read(0x2b)<<8|HDQ_Read(0x2a)
}

s16 GetRawCurrent(void)
{
	u8 hh,ll;
	ll=HDQ_Read(0x7a);
	hh=HDQ_Read(0x7b);
	return (s16)((hh<<8)|ll);
}

s16 GetCCOffset(void)
{
	u8 temp[32];
	Read_Cal_Data(temp);
	return (s16)(temp[8]<<8|temp[9]);
}

s16 GetCurrent(void)
{
	return (s16)(HDQ_Read(0x15)<<8|HDQ_Read(0x14));
}

void Read_Block_Data(u16 SubClass,u8 Block,u8 *ablock) //SubClassID,Block in the SubClass,Data
{
	u8 i,baseaddr;
	
	HDQ_Send(0x61,0x00);		delay_ms(30);
	HDQ_Send(0x3e,SubClass);  	delay_ms(30);
	HDQ_Send(0x3f,Block);		delay_ms(30);
	baseaddr=0x40;
	for(i=0;i<32;i++)
	{
		ablock[i]=HDQ_Read(baseaddr);
		baseaddr++;
	}
}

void Write_Block_Data(u16 SubClass,u8 Block,u8 *dat)
{
	u8 i,baseaddr,cs;
	HDQ_Send(0x61,0x00);		delay_ms(20);
	HDQ_Send(0x3e,SubClass);  	delay_ms(20);
	HDQ_Send(0x3f,Block);		delay_ms(20);
	baseaddr=0x40;
	for(i=0;i<32;i++)
	{
		HDQ_Send(baseaddr,dat[i]);
		baseaddr++;
	}
	cs=Cal_CheckSum(dat,32);
	HDQ_Send(0x60,cs);
}

//void Rewrite_CycleCount(void)
//{
//	u8 DataSubClass[32];
//	Read_Block_Data(48,0,DataSubClass); //CycleCount is in DataSubClass,offset 2,u16
//	//CycleCountReadOut=(DataSubClass[2]<<8)|DataSubClass[3];
//	//sprintf(disbuf,"%4d",CycleCountReadOut);
//	//Display_String_8x16(4,3,disbuf);
//	DataSubClass[2]=0;
//	DataSubClass[3]=0;
//	WriteBlockData(DataSubClass);
//	delay_ms(150);
//}

void UnSealPack(u32 Key)
{
	u16 key1,key2;
	key1=Key&0x0000ffff;
	key2=Key>>16;
	Ctrl_Cmd(key1);
	Ctrl_Cmd(key2);
	delay_ms(30);
	Ctrl_Cmd(0xffff);
	Ctrl_Cmd(0xffff);
	//delay_ms(30); ////90375994 12 //65441236  06
}

//void ShowCheckSums(void)
//{
//	
//	printf("DFCS_ALL:        %04X\n",Ctrl_Cmd(0x001a));
//	printf("DFCS_STATIC_CHEM:%04X\n",Ctrl_Cmd(0x001b));
//	printf("DFCS_ALL_STATIC: %04X\n",Ctrl_Cmd(0x001c));
//	delay_ms(20);
//}

//void SealPack()
//{
//	Ctrl_Cmd(0x0020);
//}

//void GetChemElements()
//{
//	u8 Block_Data[32];
//	u8 i;	
//	printf("OCV_Table:\r\n");
//	Read_Block_Data(0x53,0,Block_Data); //SubClassID,Block in the SubClass,Data
//	for(i=0;i<32;i++)
//	{
//		printf("0x%02X,",Block_Data[i]);
//	}
//	printf("\r\n");
//	

//	Read_Block_Data(0x53,1,Block_Data); //SubClassID,Block in the SubClass,Data
//	for(i=0;i<32;i++)
//	{
//		printf("0x%02X,",Block_Data[i]);
//	}
//	printf("\r\n");
//	
//	Read_Block_Data(0x53,2,Block_Data); //SubClassID,Block in the SubClass,Data
//	for(i=0;i<32;i++)
//	{
//		printf("0x%02X,",Block_Data[i]);
//	}
//	printf("\r\n");
//	
//	printf("OCVb_Table:\r\n");
//	
//	Read_Block_Data(0x54,0,Block_Data); //SubClassID,Block in the SubClass,Data
//	for(i=0;i<32;i++)
//	{
//		printf("0x%02X,",Block_Data[i]);
//	}
//	printf("\r\n");
//	

//	Read_Block_Data(0x54,1,Block_Data); //SubClassID,Block in the SubClass,Data
//	for(i=0;i<32;i++)
//	{
//		printf("0x%02X,",Block_Data[i]);
//	}
//	printf("\r\n");
//	
//	Read_Block_Data(0x54,2,Block_Data); //SubClassID,Block in the SubClass,Data
//	for(i=0;i<32;i++)
//	{
//		printf("0x%02X,",Block_Data[i]);
//	}
//	printf("\r\n");
//	
//	printf("Rb_Hi_Table:\r\n");
//	
//	Read_Block_Data(0x55,0,Block_Data); //SubClassID,Block in the SubClass,Data
//	for(i=0;i<32;i++)
//	{
//		printf("0x%02X,",Block_Data[i]);
//	}
//	printf("\r\n");
//	
//	printf("Rb_Lo_Table:\r\n");
//	
//	Read_Block_Data(0x6c,0,Block_Data); //SubClassID,Block in the SubClass,Data
//	for(i=0;i<32;i++)
//	{
//		printf("0x%02X,",Block_Data[i]);
//	}
//	printf("\r\n");
//	
//	printf("Gas_Gauging_IT_Cfg:\r\n");
//	
//	Read_Block_Data(0x50,0,Block_Data); //SubClassID,Block in the SubClass,Data
//	for(i=0;i<32;i++)
//	{
//		printf("0x%02X,",Block_Data[i]);
//	}
//	printf("\r\n");
//	

//	Read_Block_Data(0x50,1,Block_Data); //SubClassID,Block in the SubClass,Data
//	for(i=0;i<32;i++)
//	{
//		printf("0x%02X,",Block_Data[i]);
//	}
//	printf("\r\n");
//	
//	Read_Block_Data(0x50,2,Block_Data); //SubClassID,Block in the SubClass,Data
//	for(i=0;i<32;i++)
//	{
//		printf("0x%02X,",Block_Data[i]);
//	}
//	printf("\r\n");
//	
//	Read_Block_Data(0x50,3,Block_Data); //SubClassID,Block in the SubClass,Data
//	for(i=0;i<32;i++)
//	{
//		printf("0x%02X,",Block_Data[i]);
//	}
//	printf("\r\n");
//	
//	Read_Block_Data(0x50,4,Block_Data); //SubClassID,Block in the SubClass,Data
//	for(i=0;i<32;i++)
//	{
//		printf("0x%02X,",Block_Data[i]);
//	}
//	printf("\r\n");
//	
//	printf("Integrity_Data:\r\n");
//	
//	Read_Block_Data(0x39,0,Block_Data); //SubClassID,Block in the SubClass,Data
//	for(i=0;i<32;i++)
//	{
//		printf("0x%02X,",Block_Data[i]);
//	}
//	printf("\r\n");
//	
//	printf("Ra_Table:\r\n");
//	
//	Read_Block_Data(0x58,0,Block_Data); //SubClassID,Block in the SubClass,Data
//	for(i=0;i<32;i++)
//	{
//		printf("0x%02X,",Block_Data[i]);
//	}
//	printf("\r\n");
//	
//	
//	Read_Block_Data(0x59,0,Block_Data); //SubClassID,Block in the SubClass,Data
//	for(i=0;i<32;i++)
//	{
//		printf("0x%02X,",Block_Data[i]);
//	}
//	printf("\r\n");	
//}
