#include "reg52.h"
#include <intrins.h>

// �������

typedef unsigned int u16;
typedef unsigned char u8;

#define GPIO_DIG P0
#define GPIO_KEY P1

u8 KeyValue; //������Ŷ�ȡ���ļ�ֵ
u8 code smgduan_5[17] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8, 0x80,0x90,
												 0x88,0x83,0xc6,0xa1,0x86,0x8e};


void delay5(u16 i)
{
	while(i--);
}

void KeyDown(void)
{
	char a=0;
	if(GPIO_KEY!=0x0f)//��ȡ�����Ƿ���
	{
		delay5(1000);//��ʱ 10ms ��������
		if(GPIO_KEY!=0x0f)//�ٴμ������Ƿ���
		{
			//������
			GPIO_KEY=0X0F;
			switch(GPIO_KEY)
			{
				case(0X07): KeyValue=0;break;
				case(0X0b): KeyValue=1;break;
				case(0X0d): KeyValue=2;break;
				case(0X0e): KeyValue=3;break;
			} 
			//������
			GPIO_KEY=0XF0;
			switch(GPIO_KEY)
			{
				case(0X70): KeyValue=KeyValue;break;
				case(0Xb0): KeyValue=KeyValue+4;break;
				case(0Xd0): KeyValue=KeyValue+8;break;
				case(0Xe0): KeyValue=KeyValue+12;break;
			}
		}
	} 
	while((a<50)&&(GPIO_KEY!=0xf0)) //��ⰴ�����ּ��
	{
		delay5(100);
		a++;
	}
}

void main5()
{
	while(1)
	{
		KeyDown(); //�����жϺ���
		GPIO_DIG=~smgduan_5[KeyValue];
	}
}