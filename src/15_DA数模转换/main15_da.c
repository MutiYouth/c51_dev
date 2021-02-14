/*
实验现象：下载程序后AD/DAC模块上的DA1指示灯呈呼吸灯效果，由暗变亮再由亮变暗
		  
接线说明： (具体接线图可见开发攻略对应实验的“实验现象”章节)
		   1，单片机-->AD/DAC模块
		   		P21-->J50(PWM)
	
注意事项：										
*/

#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;

//--定义使用的IO口--//
sbit PWM=P2^1;
bit DIR;

//--定义一个全局变量--// 
u16 count,value,timer1_cnt;

// 定时器1初始化
void timer1Init15()
{
	TMOD|=0X10;//选择为定时器1模式，工作方式1，仅用TR1打开启动。

	TH1 = 0xFF; 
	TL1 = 0xff;   //定时时间1us
		
	ET1=1;//打开定时器1中断允许
	EA=1;//打开总中断
	TR1=1;//打开定时器			
}



// 定时器1的中断函数
void Time1(void) interrupt 3    //3 为定时器1的中断号  1 定时器0的中断号 0 外部中断1 2 外部中断2  4 串口中断
{
	// 重新设置初值
	TH1 = 0xFF; 
	TL1 = 0xff;   //1us
	
	timer1_cnt++; 
  count++;
}


void main15()
{	
	timer1Init15();  //定时器1初始化
	while(1)
	{
		if(count>100)							
		{  
			count=0;
			if(DIR==1)					   //DIR控制增加或减小
			  value++;	
			if(DIR==0)
			  value--;
		}

		// 控制电平是增加还是减少
		if(value==1000)
		  DIR=0;
		if(value==0)
		  DIR=1;
		
		// PWM周期为1ms = 1000*1us	
		if(timer1_cnt>1000)  
			timer1_cnt=0;
		
		// 最终输出数字电平的类型
		if(timer1_cnt <value)	
			PWM=1;
		else
			PWM=0;
	}		
}


