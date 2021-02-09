
// 实验现象：下载程序后，LED灯从左往右点亮，类似流水灯效果

#include "reg51.h"
#include "intrins.h"

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;
u8 ledNum;

//--定义使用的IO口--//
sbit SRCLK=P3^6;
sbit RCLK=P3^5;
sbit SER=P3^4;
sbit LED=P0^7;


void delay6(u16 i)
{
	while(i--);	
}

/*
* 函 数 名         : Hc595SendByte(u8 dat)
* 函数功能		   : 向74H595发送一个字节的数据
* 输    入         : 无
* 输    出         : 无
*/
void Hc595SendByte(u8 dat)
{
	u8 a;

	SRCLK = 1;
	RCLK = 1;

	for(a=0;a<8;a++)		 //发送8位数
	{
		SER = dat >> 7;		 //从最高位开始发送
		dat <<= 1;

		SRCLK = 0;			 //发送时序
		_nop_();
		_nop_();
		SRCLK = 1;	
	}
	RCLK = 0;
	_nop_();
	_nop_();
	RCLK = 1;
}


/*
* 函 数 名 : Hc595SendByte2(u8 dat1,u8 dat2)
* 函数功能 : 通过 595 发送 2 个字节的数据
* 输 		入 : dat1：第 2 个 595 输出数值
* 				   dat2: 第 1 个 595 输出数值
* 输 		出 : 无
*/
void Hc595SendByte2(u8 dat1,u8 dat2)
{
	u8 a;
	SRCLK = 1;
	RCLK = 1;
	
	for(a=0;a<8;a++) //发送 8 位数
	{
		SER = dat1 >> 7; //从最高位开始发送
		dat1 <<= 1;
		SRCLK = 0; //发送时序
		_nop_();
		_nop_();
		SRCLK = 1;
	}
	
	for(a=0;a<8;a++) //发送 8 位数
	{
		SER = dat2 >> 7; //从最高位开始发送
		dat2 <<= 1;
		SRCLK = 0; //发送时序
		_nop_();
		_nop_();
		SRCLK = 1;
	} 
	
	RCLK = 0;
	_nop_();
	_nop_();
	RCLK = 1;
}



// DEMO1
// ------------------------------------------------------------
void demo1_light_a_line()
{
	LED=0;
	ledNum = ~0x01;	  

	while(1)
	{
		Hc595SendByte(ledNum);
		ledNum = _crol_(ledNum, 1);
		delay6(50000);
	}
}

// DEMO2
// ------------------------------------------------------------

void demo2_light_a_led()
{
	LED = 0;  //使第一列为低电平
	while(1)
	{
		Hc595SendByte2(0xfe, 0x01);
	}
}


// DEMO3
// ------------------------------------------------------------
/*--  调入了一幅图像：这是新建的'love'图像  --*/
/*--  宽度x高度=8x8  --*/
u8 led_duan[] = {0x00,0xF6,0x11,0x16,0xE0,0xBF,0xF5,0x15,}; // 类似于动态数码管的段选
u8 led_wei[] = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe}; // 类似于位选，这个固定不变

void LED1(u8 dat1)
{
	P0=dat1;
}


void demo3_defined_pic()
{
	u8 i=0;
	while(1)
	{
		for(i=0;i<8;i++)
		{
			Hc595SendByte(led_duan[i]);
			LED1(led_wei[i]);
			delay6(100);
		}
	}
	
}


void main6()
{
	demo3_defined_pic();
}



