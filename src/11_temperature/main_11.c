/*************************************************************************************

*
ʵ���������س�������¶ȴ������ӿڴ�������˿ӡ�������¶ȴ�����������ܾͻ���ʾ
			�����¶�ֵ
		  
����˵���� (�������ͼ�ɼ��������Զ�Ӧʵ��ġ�ʵ�������½�)
		 
	
ע�����										

										  
**************************************************************************************

*/

#include "reg52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���
#include"temp.h"	

typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;


char num=0;
u8 DisplayData[8];
u8 code smgduan11[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};


void delay11(u16 i)
{
	while(i--);	
}


// �¶ȶ�ȡ����ת������
void datapros(int temp) 	 
{
  float tp;  
	if(temp< 0)				//���¶�ֵΪ����
	{
		DisplayData[0] = 0x40; 	  //   -
		//��Ϊ��ȡ���¶���ʵ���¶ȵĲ��룬���Լ�1����ȡ�����ԭ��
		temp=temp-1;
		temp=~temp;
		tp=temp;
		temp=tp*0.0625*100+0.5;	
		//������С�����*100��+0.5���������룬��ΪC���Ը�����ת��Ϊ���͵�ʱ���С����
		//��������Զ�ȥ���������Ƿ����0.5����+0.5֮�����0.5�ľ��ǽ�1�ˣ�С��0.5�ľ�
		//�����0.5��������С������档

	}
 	else
  {			
		DisplayData[0] = 0x00;
		tp=temp;//��Ϊ���ݴ�����С�������Խ��¶ȸ���һ�������ͱ���
		//����¶���������ô����ô������ԭ����ǲ���������
		temp=tp*0.0625*100+0.5;	
	}
	DisplayData[1] = smgduan11[temp % 10000 / 1000];
	DisplayData[2] = smgduan11[temp % 1000 / 100];
	DisplayData[3] = smgduan11[temp %  100 / 10];
	DisplayData[4] = smgduan11[temp %  10 / 1];

}


void DigDisplay11()
{
	u8 i;
	u8 data_display;
	for(i=0;i<6;i++)
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
		}
		
		data_display = DisplayData[i];
		if(i==2){
			data_display = data_display|0x80;
		}
		P0= data_display; //��������
		delay11(50); //���һ��ʱ��ɨ��	
		P0=0x00;//����
	}		
}


void main()
{	
	while(1)
	{
		datapros(Ds18b20ReadTemp());	 //���ݴ�������
		DigDisplay11();//�������ʾ����		
	}		
}