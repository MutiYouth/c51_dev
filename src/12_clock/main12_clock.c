/*
实验现象：下载程序后，数码管显示时钟
		  
接线说明： (具体接线图可见开发攻略对应实验的“实验现象”章节)
		   1，单片机-->DS1302时钟模块
		   	P34-->DIO
				P35-->CE
				P36-->CLK
		   2，单片机-->动态数码管模块
		   	J22-->J6
				P22-->J9(A)
				P23-->J9(B)
				P24-->J9(C)	
*/

#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器
#include "ds1302.h"	

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;


u8 DisplayData12[8];
u8 code smgduan12[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};


void delay12(u16 i)
{
	while(i--);	
}


// 时间读取处理转换函数
void datapros12() 	 
{
  Ds1302ReadTime();
	DisplayData12[0] = smgduan12[TIME[2]/16];				//时, 十位
	DisplayData12[1] = smgduan12[TIME[2]&0x0f];			//时, 个位
	DisplayData12[2] = 0x40;
	DisplayData12[3] = smgduan12[TIME[1]/16];				//分
	DisplayData12[4] = smgduan12[TIME[1]&0x0f];	
	DisplayData12[5] = 0x40;
	DisplayData12[6] = smgduan12[TIME[0]/16];				//秒
	DisplayData12[7] = smgduan12[TIME[0]&0x0f];
}


// 数码管显示函数
void DigDisplay12()
{
	u8 i;
	for(i=0;i<8;i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=1;LSB=1;LSC=1; break;//显示第0位
			case(1):
				LSA=0;LSB=1;LSC=1; break;//显示第1位
			case(2):
				LSA=1;LSB=0;LSC=1; break;//显示第2位
			case(3):
				LSA=0;LSB=0;LSC=1; break;//显示第3位
			case(4):
				LSA=1;LSB=1;LSC=0; break;//显示第4位
			case(5):
				LSA=0;LSB=1;LSC=0; break;//显示第5位
			case(6):
				LSA=1;LSB=0;LSC=0; 
				break;//显示第6位
			case(7):
				LSA=0;LSB=0;LSC=0; 
				break;//显示第7位
		}
		P0=DisplayData12[i];//发送数据
		delay12(100); //间隔一段时间扫描	
		P0=0x00;//消隐
	}		
}


void main12()
{	
	// 第一次初始化后就可以注释该条语句，这样下次重启就不会再次初始化了
	// Ds1302Init();	   //[IMPORTANT] 21.2.10
	while(1)
	{
		datapros12();	 //数据处理函数
		DigDisplay12();//数码管显示函数		
	}		
}

