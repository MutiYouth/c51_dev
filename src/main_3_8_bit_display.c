#include "reg52.h"
#include <intrins.h>

// 8λ����ܵ���ʾ

typedef unsigned int u16;
typedef unsigned char u8;

// λѡ
sbit LSA = P2^2;
sbit LSB = P2^3;
sbit LSC = P2^4;

// ��ʾ0~F��ֵ
u8 code smgduan[18]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
										 0x77,0x7c,0x39,0x5e,0x79,0x71, 0x40};
u8 numbers[8]={1,3,1,4,16,5,2,0};

void delay3(u16 i)
{
	while(i--);
}

//�� �� �� : DigDisplay
//�������� : ����ܶ�̬ɨ�躯���� ѭ��ɨ�� 8 ���������ʾ

void DigDisplay()
{
	u8 i;
	for(i=0;i<8;i++)
	{
		switch(i) //λѡ�� ѡ�����������ܣ�
		{
			case(0):
			LSA=1;LSB=1;LSC=1; break;//��ʾ�� 0 λ
			case(1):
			LSA=0;LSB=1;LSC=1; break;//��ʾ�� 1 λ
			case(2):
			LSA=1;LSB=0;LSC=1; break;//��ʾ�� 2 λ
			case(3):
			LSA=0;LSB=0;LSC=1; break;//��ʾ�� 3 λ
			case(4):
			LSA=1;LSB=1;LSC=0; break;//��ʾ�� 4 λ
			case(5):
			LSA=0;LSB=1;LSC=0; break;//��ʾ�� 5 λ
			case(6):
			LSA=1;LSB=0;LSC=0; break;//��ʾ�� 6 λ
			case(7):
			LSA=0;LSB=0;LSC=0; break;//��ʾ�� 7 λ
		} 
		P0=smgduan[numbers[i]];//���Ͷ���. i --> numbers[i]
		delay3(100); //���һ��ʱ��ɨ��
		P0=0x00;//����
	}
}


void main3()
{
	while(1)
	{
		DigDisplay(); //�������ʾ����
	}
}
