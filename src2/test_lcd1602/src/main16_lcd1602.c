/*
ʵ���������س�������LCD1602Һ���ڿ������ϣ�������ʾ
		  
����˵���� (�������ͼ�ɼ��������Զ�Ӧʵ��ġ�ʵ�������½�)

ע����������Լ�ʹ�õ�LCD1602�Ƿ����ת�Ӱ壬�������ת�Ӱ�ļ�Ϊ4λ������LCD.Hͷ�ļ���
����#define LCD1602_4PINS�򿪣���������ʹ�õ�LCD1602��8λ������Ĭ�Ͻ��ú�ע��										
*/

#include "reg52.h"
#include "lcd.h"

typedef unsigned int u16;
typedef unsigned char u8;

u8 Disp_1[]=" ---- LOVE ---- ";
u8 Disp_2[]="   2021 SPRING  ";


void main(void)
{
	u8 i;
	LcdInit();
	for(i=0;i<16;i++)
	{
		LcdWriteData(Disp_1[i]);	
	}
	
	// line2
	LcdWriteCom(0x40+0x80);
	for(i=0;i<16;i++)
	{
		LcdWriteData(Disp_2[i]);	
	}
	
	while(1);				
}
