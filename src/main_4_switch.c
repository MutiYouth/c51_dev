#include "reg52.h"
#include <intrins.h>

// �������Ƶ�

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
	if(k1==0) //��ⰴ�� K1 �Ƿ���
	{
		delay4(1000); //�������� һ���Լ 10ms
		if(k1==0) //�ٴ��жϰ����Ƿ���
		{
			led=~led; //led ״̬ȡ��
		} 
		while(!k1); //��ⰴ���Ƿ��ɿ����� 51 ��Ƭ����������
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