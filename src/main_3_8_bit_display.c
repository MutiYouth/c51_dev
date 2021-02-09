#include "reg52.h"
#include <intrins.h>

// 8位数码管的显示

typedef unsigned int u16;
typedef unsigned char u8;

// 位选
sbit LSA = P2^2;
sbit LSB = P2^3;
sbit LSC = P2^4;

// 显示0~F的值
u8 code smgduan[18]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
										 0x77,0x7c,0x39,0x5e,0x79,0x71, 0x40};
u8 numbers[8]={1,3,1,4,16,5,2,0};

void delay3(u16 i)
{
	while(i--);
}

//函 数 名 : DigDisplay
//函数功能 : 数码管动态扫描函数， 循环扫描 8 个数码管显示

void DigDisplay()
{
	u8 i;
	for(i=0;i<8;i++)
	{
		switch(i) //位选， 选择点亮的数码管，
		{
			case(0):
			LSA=1;LSB=1;LSC=1; break;//显示第 0 位
			case(1):
			LSA=0;LSB=1;LSC=1; break;//显示第 1 位
			case(2):
			LSA=1;LSB=0;LSC=1; break;//显示第 2 位
			case(3):
			LSA=0;LSB=0;LSC=1; break;//显示第 3 位
			case(4):
			LSA=1;LSB=1;LSC=0; break;//显示第 4 位
			case(5):
			LSA=0;LSB=1;LSC=0; break;//显示第 5 位
			case(6):
			LSA=1;LSB=0;LSC=0; break;//显示第 6 位
			case(7):
			LSA=0;LSB=0;LSC=0; break;//显示第 7 位
		} 
		P0=smgduan[numbers[i]];//发送段码. i --> numbers[i]
		delay3(100); //间隔一段时间扫描
		P0=0x00;//消隐
	}
}


void main3()
{
	while(1)
	{
		DigDisplay(); //数码管显示函数
	}
}
