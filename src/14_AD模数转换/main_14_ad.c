/*
模数转换


接线说明： (具体接线图可见开发攻略对应实验的“实验现象”章节)
		   1，单片机-->AD/DAC模块
		   		P34-->DI
				P35-->CS
				P36-->CL
				P37-->DO
		   2，单片机-->动态数码管模块
		   		J22-->J6
				P22-->J9(A)
				P23-->J9(B)
				P24-->J9(C)	

*/

#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器
#include "XPT2046.h"	

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 disp14[4];
u8 code smgduan14[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};


void delay14(u16 i)
{
	while(i--);	
}

void DigDisplay14(u8 display_dot, u8 location)
{
	u8 i;
	u8 data_display;
	for(i=0;i<4;i++)
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
		}
		
		// add dot.
		data_display = disp14[i];
		if(display_dot == 1 && i==location)
		{
			data_display = disp14[i] | 0x80;
		}
		
		//发送数据
		P0=data_display;
		//间隔一段时间扫描	
		delay14(100); 
		//消隐
		P0=0x00;
	}		
}


void datapros14(uchar cmd, bit show_float_or_int)
{
	u16 temp;
	static u8 i;
	float v_value;
	if(i==50)
	{
		i=0;
		temp = Read_AD_Data(cmd);
	}
	i++;
	
	// show type
	if(show_float_or_int == 1)
	{
		// convert int value to float voltage
		// 转为float类型 00.00
		v_value = (float)temp / 4096.0f * 5.0f;
		
		disp14[0]=smgduan14[((u8)v_value)/10]; //十位
		disp14[1]=smgduan14[((u8)v_value)%10]; //个位
		disp14[2]=smgduan14[((u8)(v_value*10))%10]; // .0
		disp14[3]=smgduan14[((u8)(v_value*100))%10]; //.00
	}
	else
	{
		disp14[0]=smgduan14[temp/1000];//千位
		disp14[1]=smgduan14[temp%1000/100];//百位
		disp14[2]=smgduan14[temp%1000%100/10];//十位
		disp14[3]=smgduan14[temp%1000%100%10];//个位
	}
	
}


void main14()
{	
	// 电位器, 载程序后数码管前4位显示电位器检测的AD值，范围是0-4095，一般达不到最大，这个受供电电压的影响
	// 0x94, 	AIN0 电位器,		show_type float is 1.
	// 0xD4,  AIN1 热敏电阻,	show_type int is 0;
	// 0xA4,  AIN2 光敏电阻,	show_type int
	// 0xE4,	AIN3 外部输入
	uchar cmd = 0xE4;
	bit show_type = 1;
	
	while(1)
	{
		datapros14(cmd, show_type);	 //数据处理函数
		DigDisplay14(show_type, 1);//数码管显示函数		
	}		
}

