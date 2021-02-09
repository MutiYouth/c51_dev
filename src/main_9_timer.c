/**************************************************************************************
实验现象：下载程序后，D1小灯循环点亮1秒，熄灭1秒。使用单片机内部定时器可以实现准确延时
		  
接线说明： (具体接线图可见开发攻略对应实验的“实验现象”章节)
		   1，单片机-->LED&交通灯模块
		   		P20-->D1
		   	
	
注意事项：																				

  
***************************************************************************************/

#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;

sbit led=P2^3;	 //定义P20口是led


void Timer0Init()
{
	TMOD|=0X01;//选择为定时器0模式，工作方式1，仅用TR0打开启动。

	TH0=0XFC;	//给定时器赋初值，定时1ms
	TL0=0X18;	
	ET0=1;//打开定时器0中断允许
	EA=1;//打开总中断
	TR0=1;//打开定时器			
}

void Timer0() interrupt 1
{
	static u16 i;
	TH0=0XFC;	//给定时器赋初值，定时1ms
	TL0=0X18;
	i++;
	if(i==1000)
	{
		i=0;
		led=~led;	
	}	
}

void demo_timer_0()
{
	Timer0Init();  //定时器0初始化
	while(1);		
}


// -------------------------------------------------

u8 code smgduan_9[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07, 0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//显示0~F的值
u8 timder_1_n=0;

void Timer1Init()
{
	TMOD|=0x10;  //选择为定时器1模式，工作方式1，仅用TR1打开启动。
	TH1=0XFC;	//给定时器赋初值，定时1ms
	TL1=0X18;	
	ET1=1;//打开定时器1中断允许
	EA=1;//打开总中断
	TR1=1;//打开定时器	
}

void Timer1() interrupt 3
{
	static u16 i;
	TH1=0XFC;	//给定时器赋初值，定时1ms
	TL1=0X18;
	i++;
	if(i==1000)
	{
		i=0;
		P0=smgduan_9[timder_1_n++];
		if(timder_1_n==16)timder_1_n=0;	
	}	
}

void demo_timer_1()
{
	Timer1Init();  //定时器1初始化
	while(1);		
}


void main9()
{	
	demo_timer_1();
}

