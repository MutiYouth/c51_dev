
// ʵ���������س����LED�ƴ������ҵ�����������ˮ��Ч��

#include "reg51.h"
#include "intrins.h"

typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;
u8 ledNum;

//--����ʹ�õ�IO��--//
sbit SRCLK=P3^6;
sbit RCLK=P3^5;
sbit SER=P3^4;
sbit LED=P0^7;


void delay6(u16 i)
{
	while(i--);	
}

/*
* �� �� ��         : Hc595SendByte(u8 dat)
* ��������		   : ��74H595����һ���ֽڵ�����
* ��    ��         : ��
* ��    ��         : ��
*/
void Hc595SendByte(u8 dat)
{
	u8 a;

	SRCLK = 1;
	RCLK = 1;

	for(a=0;a<8;a++)		 //����8λ��
	{
		SER = dat >> 7;		 //�����λ��ʼ����
		dat <<= 1;

		SRCLK = 0;			 //����ʱ��
		_nop_();
		_nop_();
		SRCLK = 1;	
	}
	RCLK = 0;
	_nop_();
	_nop_();
	RCLK = 1;
}


/*
* �� �� �� : Hc595SendByte2(u8 dat1,u8 dat2)
* �������� : ͨ�� 595 ���� 2 ���ֽڵ�����
* �� 		�� : dat1���� 2 �� 595 �����ֵ
* 				   dat2: �� 1 �� 595 �����ֵ
* �� 		�� : ��
*/
void Hc595SendByte2(u8 dat1,u8 dat2)
{
	u8 a;
	SRCLK = 1;
	RCLK = 1;
	
	for(a=0;a<8;a++) //���� 8 λ��
	{
		SER = dat1 >> 7; //�����λ��ʼ����
		dat1 <<= 1;
		SRCLK = 0; //����ʱ��
		_nop_();
		_nop_();
		SRCLK = 1;
	}
	
	for(a=0;a<8;a++) //���� 8 λ��
	{
		SER = dat2 >> 7; //�����λ��ʼ����
		dat2 <<= 1;
		SRCLK = 0; //����ʱ��
		_nop_();
		_nop_();
		SRCLK = 1;
	} 
	
	RCLK = 0;
	_nop_();
	_nop_();
	RCLK = 1;
}



// DEMO1
// ------------------------------------------------------------
void demo1_light_a_line()
{
	LED=0;
	ledNum = ~0x01;	  

	while(1)
	{
		Hc595SendByte(ledNum);
		ledNum = _crol_(ledNum, 1);
		delay6(50000);
	}
}

// DEMO2
// ------------------------------------------------------------

void demo2_light_a_led()
{
	LED = 0;  //ʹ��һ��Ϊ�͵�ƽ
	while(1)
	{
		Hc595SendByte2(0xfe, 0x01);
	}
}


// DEMO3
// ------------------------------------------------------------
/*--  ������һ��ͼ�������½���'love'ͼ��  --*/
/*--  ���x�߶�=8x8  --*/
u8 led_duan[] = {0x00,0xF6,0x11,0x16,0xE0,0xBF,0xF5,0x15,}; // �����ڶ�̬����ܵĶ�ѡ
u8 led_wei[] = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe}; // ������λѡ������̶�����

void LED1(u8 dat1)
{
	P0=dat1;
}


void demo3_defined_pic()
{
	u8 i=0;
	while(1)
	{
		for(i=0;i<8;i++)
		{
			Hc595SendByte(led_duan[i]);
			LED1(led_wei[i]);
			delay6(100);
		}
	}
	
}


void main6()
{
	demo3_defined_pic();
}



