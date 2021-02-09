#include "reg52.h"		//���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���
#include<intrins.h> 	//��ΪҪ�õ������ƺ����� ���Լ������ͷ�ļ�
typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;


// ---------------------------------------------
// lighting the first light
// ʵ������: ���س����D1ָʾ�Ƶ���
// WENG 21.2.7 2347
sbit led = P2^0;

// ��ʱ������ i=1 ʱ�� ��Լ��ʱ 9.09us. ��Ϊ������11MHz�� 
// ����100��ʱ�����ڲſ�ִ��һ����䣬�� 1/11000000 * 100 = 9.09us
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
		delay(200*100); //500*100ʱ����Լ��ʱ450ms
		led = 0;
		delay(200*100); 
	}
}

// ---------------------------------------------

# define led_flow_lights P2  // �� P2 �ڶ���Ϊ led ����Ϳ���ʹ�� led ���� P2

void demo_flow_lights(){
	u8 i;
	led_flow_lights=~0x01; //0x01 ȡ����Ϊ 0xFE
	delay(50000); // ��Լ�ӳ�450ms
	while(1)
	{
		for(i=0;i<8;i++)
		{
			P2=~(0x01<<i); //�� 1 ���� i λ�� Ȼ�󽫽����ֵ�� P0 ��
			delay(50000);  //��Լ��ʱ 450ms
		}
	}
}


void demo_flow_lights_2()
{
	u8 i;
	led_flow_lights=~0x01;
	delay(50000); //��Լ��ʱ 450ms
	while(1)
	{
		for(i=0;i<7;i++) //�� led ����һλ
		{
			led_flow_lights=_crol_(led_flow_lights,1);
			delay(50000); //��Լ��ʱ 450ms
		} 
		
		for(i=0;i<7;i++) //�� led ����һλ
		{
			led_flow_lights=_cror_(led_flow_lights,1);
			delay(50000); //��Լ��ʱ 450ms
		}
	}
}
// ---------------------------------------------


void main1()
{
	demo_flow_lights_2();
}
