/**************************************************************************************
ʵ���������س��������ܺ�4λ��ʾ0����K1������ʾ�����ݣ���K2��ȡ�ϴα�������ݣ�
		  ��K3��ʾ���ݼ�һ����K4��ʾ�������㡣�����д���������255
		  
����˵���� (�������ͼ�ɼ��������Զ�Ӧʵ��ġ�ʵ�������½�)
		  
	
ע�����																				  
***************************************************************************************/

#include "reg52.h"
#include "i2c.h"	

typedef unsigned int u16;
typedef unsigned char u8;

// λѡ�ܽ�
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

// ���尴���˿�
sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;

char num=0;
u8 disp[4];
u8 code smgduan10[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};


void delay10(u16 i)
{
	while(i--);	
}


// ����������
void Keypros()
{
	if(k1==0)
	{
		delay10(1000);  //��������
		if(k1==0)
		{
			At24c02Write(1,num);   //�ڵ�ַ1��д������num
		}
		while(!k1);
	}
	if(k2==0)
	{
		delay10(1000);  //��������
		if(k2==0)
		{
			num=At24c02Read(1);	  //��ȡEEPROM��ַ1�ڵ����ݱ�����num��
		}
		while(!k2);
	}
	if(k3==0)
	{
		delay10(100);  //��������
		if(k3==0)
		{
			num++;	   //���ݼ�1
			if(num>255)num=0;
		}
		while(!k3);
	}
	if(k4==0)
	{
		delay10(1000);  //��������
		if(k4==0)
		{
			num=0;		 //��������
		}
		while(!k4);
	}		
}

// ���ݴ�����
void datapros()
{
	disp[0]=smgduan10[num/1000];//ǧλ
	disp[1]=smgduan10[num%1000/100];//��λ
	disp[2]=smgduan10[num%1000%100/10];//ʮλ
	disp[3]=smgduan10[num%1000%100%10];		
}


// �������ʾ����
void DigDisplay10()
{
	u8 i;
	for(i=0;i<4;i++)
	{
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��0λ
			case(1):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��1λ
			case(2):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��2λ
			case(3):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��3λ
		}
		P0=disp[i];//��������
		delay10(100); //���һ��ʱ��ɨ��	
		P0=0x00;//����
	}		
}


void main10()
{	
	while(1)
	{
		Keypros();	 //����������
		datapros();	 //���ݴ�����
		DigDisplay10();//�������ʾ����		
	}		
}