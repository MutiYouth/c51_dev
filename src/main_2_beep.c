#include "reg52.h"
#include <intrins.h>  //��ΪҪ�õ������ƺ����� ���Լ������ͷ�ļ�

// BEEP
// WENG 21.2.8
// ʵ������ ���س����"������ģ��"�ķ���������
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
		delay2(2000*100); //100ʱ��ʱ��Լ 1ms ͨ���޸Ĵ���ʱʱ��ﵽ��ͬ�ķ���Ч��
	}
}


