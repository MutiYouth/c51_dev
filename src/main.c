#include "reg52.h"		//此文件中定义了单片机的一些特殊功能寄存器
#include<intrins.h> 	//因为要用到左右移函数， 所以加入这个头文件
typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;


// ---------------------------------------------
// lighting the first light
// 实验现象: 下载程序后，D1指示灯点亮
// WENG 21.2.7 2347
sbit led = P2^0;

// 延时函数， i=1 时， 大约延时 9.09us. 因为晶振是11MHz。 
// 假设100个时钟周期才可执行一条语句，则 1/11000000 * 100 = 9.09us
void delay(u16 i)
{
	while(i--);
}

void demo_twinkle()
{
	led = 0;
	while(1)
	{
		led = 1;
		delay(200*100); //500*100时，大约延时450ms
		led = 0;
		delay(200*100); 
	}
}

// ---------------------------------------------

# define led_flow_lights P2  // 将 P2 口定义为 led 后面就可以使用 led 代替 P2

void demo_flow_lights(){
	u8 i;
	led_flow_lights=~0x01; //0x01 取反即为 0xFE
	delay(50000); // 大约延迟450ms
	while(1)
	{
		for(i=0;i<8;i++)
		{
			P2=~(0x01<<i); //将 1 右移 i 位， 然后将结果赋值到 P0 口
			delay(50000);  //大约延时 450ms
		}
	}
}


void demo_flow_lights_2()
{
	u8 i;
	led_flow_lights=~0x01;
	delay(50000); //大约延时 450ms
	while(1)
	{
		for(i=0;i<7;i++) //将 led 左移一位
		{
			led_flow_lights=_crol_(led_flow_lights,1);
			delay(50000); //大约延时 450ms
		} 
		
		for(i=0;i<7;i++) //将 led 右移一位
		{
			led_flow_lights=_cror_(led_flow_lights,1);
			delay(50000); //大约延时 450ms
		}
	}
}
// ---------------------------------------------


void main1()
{
	demo_flow_lights_2();
}
