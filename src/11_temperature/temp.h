#ifndef __TEMP_H_
#define __TEMP_H_

#include<reg52.h>


// 温度传感器的驱动程序。 21.2.9 2232

//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

//--定义使用的IO口--//
sbit DSPORT=P3^7;

//--声明全局函数--//
void Delay1ms(uint );
uchar Ds18b20Init();
void Ds18b20WriteByte(uchar com);
uchar Ds18b20ReadByte();
void  Ds18b20ChangTemp();
void  Ds18b20ReadTempCom();
int Ds18b20ReadTemp();

#endif
