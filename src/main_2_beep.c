#include "reg52.h"
#include <intrins.h>  //因为要用到左右移函数， 所以加入这个头文件

// BEEP
// WENG 21.2.8
// 实验现象： 下载程序后"蜂鸣器模块"的蜂鸣器发声
typedef unsigned int u16;
typedef unsigned char u8;

sbit beep=P2^5;


void delay2(u16 i)
{
	while(i--);
}


void main2()
{
	while(1)
	{
		beep=~beep;
		delay2(2000*100); //100时延时大约 1ms 通过修改此延时时间达到不同的发声效果
	}
}


