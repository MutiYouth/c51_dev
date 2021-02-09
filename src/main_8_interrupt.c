/*
实验现象：下载程序后，操作 K3 按键使 D1 状态取反
1，单片机-->LED&交通灯模块
P20-->D1
2，单片机-->独立按键模块
P32-->K3
*/
#include "reg52.h" 
typedef unsigned int u16;
typedef unsigned char u8;
sbit k3=P3^2; //定义按键 K3 -- P3^2
sbit k4=P3^3;
sbit led=P2^0; //定义 P20 口是 led
sbit led2=P2^1;

// i=1 时，大约延时 10us
void delay8(u16 i)
{
	while(i--);
}


void Int_0_1_Init()
{
	//设置外部中断 1
	//设置 INT0
	IT0=1;//跳变沿出发方式（下降沿）
	EX0=1;//打开 INT0 的中断允许。
	//EA=1;//打开总中断
	
	// 外部中断2
	// 设置INT1
	// todo: 外部中断2无法使用，待调试。 21.2.9. 
	// Done! Int1() interrupt [1]  改为2即可。
	IT1=1;
	EX1=1;
	EA=1;//打开总中断
}

void main8()
{
Int_0_1_Init(); // 设置外部中断 0
while(1);
}

// 外部中断 0 的中断函数
void Int0() interrupt 0 
{
	delay8(1000); //延时消抖
	if(k3==0)
	{
	led=~led;
	}
}

// 外部中断 1 的中断函数
void Int1() interrupt 2
{
	delay8(1000);
	if(k4==0)
	{
	led2=~led2;
	}
}