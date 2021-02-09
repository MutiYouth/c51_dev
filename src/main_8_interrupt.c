/*
ʵ���������س���󣬲��� K3 ����ʹ D1 ״̬ȡ��
1����Ƭ��-->LED&��ͨ��ģ��
P20-->D1
2����Ƭ��-->��������ģ��
P32-->K3
*/
#include "reg52.h" 
typedef unsigned int u16;
typedef unsigned char u8;
sbit k3=P3^2; //���尴�� K3 -- P3^2
sbit k4=P3^3;
sbit led=P2^0; //���� P20 ���� led
sbit led2=P2^1;

// i=1 ʱ����Լ��ʱ 10us
void delay8(u16 i)
{
	while(i--);
}


void Int_0_1_Init()
{
	//�����ⲿ�ж� 1
	//���� INT0
	IT0=1;//�����س�����ʽ���½��أ�
	EX0=1;//�� INT0 ���ж�����
	//EA=1;//�����ж�
	
	// �ⲿ�ж�2
	// ����INT1
	// todo: �ⲿ�ж�2�޷�ʹ�ã������ԡ� 21.2.9. 
	// Done! Int1() interrupt [1]  ��Ϊ2���ɡ�
	IT1=1;
	EX1=1;
	EA=1;//�����ж�
}

void main8()
{
Int_0_1_Init(); // �����ⲿ�ж� 0
while(1);
}

// �ⲿ�ж� 0 ���жϺ���
void Int0() interrupt 0 
{
	delay8(1000); //��ʱ����
	if(k3==0)
	{
	led=~led;
	}
}

// �ⲿ�ж� 1 ���жϺ���
void Int1() interrupt 2
{
	delay8(1000);
	if(k4==0)
	{
	led2=~led2;
	}
}