/*
ʵ���������س�����������ʾʱ��
		  
����˵���� (�������ͼ�ɼ��������Զ�Ӧʵ��ġ�ʵ�������½�)
		   1����Ƭ��-->DS1302ʱ��ģ��
		   	P34-->DIO
				P35-->CE
				P36-->CLK
		   2����Ƭ��-->��̬�����ģ��
		   	J22-->J6
				P22-->J9(A)
				P23-->J9(B)
				P24-->J9(C)	
*/

#include "reg52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���
#include "ds1302.h"	

typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;


u8 DisplayData12[8];
u8 code smgduan12[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};


void delay12(u16 i)
{
	while(i--);	
}


// ʱ���ȡ����ת������
void datapros12() 	 
{
  Ds1302ReadTime();
	DisplayData12[0] = smgduan12[TIME[2]/16];				//ʱ, ʮλ
	DisplayData12[1] = smgduan12[TIME[2]&0x0f];			//ʱ, ��λ
	DisplayData12[2] = 0x40;
	DisplayData12[3] = smgduan12[TIME[1]/16];				//��
	DisplayData12[4] = smgduan12[TIME[1]&0x0f];	
	DisplayData12[5] = 0x40;
	DisplayData12[6] = smgduan12[TIME[0]/16];				//��
	DisplayData12[7] = smgduan12[TIME[0]&0x0f];
}


// �������ʾ����
void DigDisplay12()
{
	u8 i;
	for(i=0;i<8;i++)
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
			case(4):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��4λ
			case(5):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��5λ
			case(6):
				LSA=1;LSB=0;LSC=0; 
				break;//��ʾ��6λ
			case(7):
				LSA=0;LSB=0;LSC=0; 
				break;//��ʾ��7λ
		}
		P0=DisplayData12[i];//��������
		delay12(100); //���һ��ʱ��ɨ��	
		P0=0x00;//����
	}		
}


void main12()
{	
	// ��һ�γ�ʼ����Ϳ���ע�͸�����䣬�����´������Ͳ����ٴγ�ʼ����
	// Ds1302Init();	   //[IMPORTANT] 21.2.10
	while(1)
	{
		datapros12();	 //���ݴ�����
		DigDisplay12();//�������ʾ����		
	}		
}

