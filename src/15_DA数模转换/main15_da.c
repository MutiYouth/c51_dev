/*
ʵ���������س����AD/DACģ���ϵ�DA1ָʾ�Ƴʺ�����Ч�����ɰ������������䰵
		  
����˵���� (�������ͼ�ɼ��������Զ�Ӧʵ��ġ�ʵ�������½�)
		   1����Ƭ��-->AD/DACģ��
		   		P21-->J50(PWM)
	
ע�����										
*/

#include "reg52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���

typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;

//--����ʹ�õ�IO��--//
sbit PWM=P2^1;
bit DIR;

//--����һ��ȫ�ֱ���--// 
u16 count,value,timer1_cnt;

// ��ʱ��1��ʼ��
void timer1Init15()
{
	TMOD|=0X10;//ѡ��Ϊ��ʱ��1ģʽ��������ʽ1������TR1��������

	TH1 = 0xFF; 
	TL1 = 0xff;   //��ʱʱ��1us
		
	ET1=1;//�򿪶�ʱ��1�ж�����
	EA=1;//�����ж�
	TR1=1;//�򿪶�ʱ��			
}



// ��ʱ��1���жϺ���
void Time1(void) interrupt 3    //3 Ϊ��ʱ��1���жϺ�  1 ��ʱ��0���жϺ� 0 �ⲿ�ж�1 2 �ⲿ�ж�2  4 �����ж�
{
	// �������ó�ֵ
	TH1 = 0xFF; 
	TL1 = 0xff;   //1us
	
	timer1_cnt++; 
  count++;
}


void main15()
{	
	timer1Init15();  //��ʱ��1��ʼ��
	while(1)
	{
		if(count>100)							
		{  
			count=0;
			if(DIR==1)					   //DIR�������ӻ��С
			  value++;	
			if(DIR==0)
			  value--;
		}

		// ���Ƶ�ƽ�����ӻ��Ǽ���
		if(value==1000)
		  DIR=0;
		if(value==0)
		  DIR=1;
		
		// PWM����Ϊ1ms = 1000*1us	
		if(timer1_cnt>1000)  
			timer1_cnt=0;
		
		// ����������ֵ�ƽ������
		if(timer1_cnt <value)	
			PWM=1;
		else
			PWM=0;
	}		
}


