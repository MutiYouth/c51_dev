/*
ģ��ת��


����˵���� (�������ͼ�ɼ��������Զ�Ӧʵ��ġ�ʵ�������½�)
		   1����Ƭ��-->AD/DACģ��
		   		P34-->DI
				P35-->CS
				P36-->CL
				P37-->DO
		   2����Ƭ��-->��̬�����ģ��
		   		J22-->J6
				P22-->J9(A)
				P23-->J9(B)
				P24-->J9(C)	

*/

#include "reg52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���
#include "XPT2046.h"	

typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 disp14[4];
u8 code smgduan14[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};


void delay14(u16 i)
{
	while(i--);	
}

void DigDisplay14(u8 display_dot, u8 location)
{
	u8 i;
	u8 data_display;
	for(i=0;i<4;i++)
	{
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��0λ
			case(1):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��1λ
			case(2):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��2λ
			case(3):
				LSA=0;LSB=0;LSC=1; break;//��ʾ��3λ	
		}
		
		// add dot.
		data_display = disp14[i];
		if(display_dot == 1 && i==location)
		{
			data_display = disp14[i] | 0x80;
		}
		
		//��������
		P0=data_display;
		//���һ��ʱ��ɨ��	
		delay14(100); 
		//����
		P0=0x00;
	}		
}


void datapros14(uchar cmd, bit show_float_or_int)
{
	u16 temp;
	static u8 i;
	float v_value;
	if(i==50)
	{
		i=0;
		temp = Read_AD_Data(cmd);
	}
	i++;
	
	// show type
	if(show_float_or_int == 1)
	{
		// convert int value to float voltage
		// תΪfloat���� 00.00
		v_value = (float)temp / 4096.0f * 5.0f;
		
		disp14[0]=smgduan14[((u8)v_value)/10]; //ʮλ
		disp14[1]=smgduan14[((u8)v_value)%10]; //��λ
		disp14[2]=smgduan14[((u8)(v_value*10))%10]; // .0
		disp14[3]=smgduan14[((u8)(v_value*100))%10]; //.00
	}
	else
	{
		disp14[0]=smgduan14[temp/1000];//ǧλ
		disp14[1]=smgduan14[temp%1000/100];//��λ
		disp14[2]=smgduan14[temp%1000%100/10];//ʮλ
		disp14[3]=smgduan14[temp%1000%100%10];//��λ
	}
	
}


void main14()
{	
	// ��λ��, �س���������ǰ4λ��ʾ��λ������ADֵ����Χ��0-4095��һ��ﲻ���������ܹ����ѹ��Ӱ��
	// 0x94, 	AIN0 ��λ��,		show_type float is 1.
	// 0xD4,  AIN1 ��������,	show_type int is 0;
	// 0xA4,  AIN2 ��������,	show_type int
	// 0xE4,	AIN3 �ⲿ����
	uchar cmd = 0xE4;
	bit show_type = 1;
	
	while(1)
	{
		datapros14(cmd, show_type);	 //���ݴ�����
		DigDisplay14(show_type, 1);//�������ʾ����		
	}		
}

