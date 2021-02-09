#include "reg52.h"
#include <intrins.h>

// 按键控制灯

typedef unsigned int u16;
typedef unsigned char u8;

sbit k1=P3^1; //define P3_1 is k1.
sbit led=P2^0; 


void delay4(u16 i)
{
	while(i--);
}

void keypres()
{
	if(k1==0) //检测按键 K1 是否按下
	{
		delay4(1000); //消除抖动 一般大约 10ms
		if(k1==0) //再次判断按键是否按下
		{
			led=~led; //led 状态取反
		} 
		while(!k1); //检测按键是否松开普中 51 单片机开发攻略
	}
}

void main4()
{
	led = 1;
	while(1)
	{
		keypres();
	}
}