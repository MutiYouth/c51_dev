/*
实验现象：下载程序后插上LCD1602液晶在开发板上，即可显示
		  
接线说明： (具体接线图可见开发攻略对应实验的“实验现象”章节)

注意事项：根据自己使用的LCD1602是否带有转接板，如果带有转接板的即为4位，需在LCD.H头文件中
将宏#define LCD1602_4PINS打开，我们这里使用的LCD1602是8位，所以默认将该宏注释										
*/

#include "reg52.h"
#include "lcd.h"

typedef unsigned int u16;
typedef unsigned char u8;

u8 Disp_1[]=" ---- LOVE ---- ";
u8 Disp_2[]="   2021 SPRING  ";


void main(void)
{
	u8 i;
	LcdInit();
	for(i=0;i<16;i++)
	{
		LcdWriteData(Disp_1[i]);	
	}
	
	// line2
	LcdWriteCom(0x40+0x80);
	for(i=0;i<16;i++)
	{
		LcdWriteData(Disp_2[i]);	
	}
	
	while(1);				
}
