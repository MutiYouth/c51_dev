/*************************************************************************************

*
实验现象：下载程序后，数码管显示红外遥控键值数据
		  
接线说明： (具体接线图可见开发攻略对应实验的“实验现象”章节)
		   1，单片机-->红外接收模块
		   		P32-->J11
		   2，单片机-->动态数码管模块
		   		J22-->J6
				P22-->J9(A)
				P23-->J9(B)
				P24-->J9(C)	
	
注意事项：红外遥控器上的电池绝缘隔片要拿掉										

										  
**************************************************************************************

*/

#include "reg52.h"
	

typedef unsigned int u16;	  
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

sbit IRIN=P3^2;

u8 IrValue[6];
u8 Time13;

u8 DisplayData13[8];
u8 code smgduan13[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0X76};
//0、1、2、3、4、5、6、7、8、9、A、b、C、d、E、F、H的显示码


void delay13(u16 i)
{
	while(i--);	
}



void DigDisplay13()
{
	u8 i;
	for(i=0;i<3;i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=1;LSB=1;LSC=1; break;//显示第0位	
			case(1):
				LSA=0;LSB=1;LSC=1; break;//显示第1位
			case(2):
				LSA=1;LSB=0;LSC=1; break;//显示第2位 
		}
		P0=DisplayData13[i];//发送数据
		delay13(100); //间隔一段时间扫描	
		P0=0x00;//消隐
	}		
}


// 初始化红外线接收
void IrInit()
{
	IT0=1;//下降沿触发
	EX0=1;//打开中断0允许
	EA=1;	//打开总中断

	IRIN=1;//初始化端口
}


// 读取红外数值的中断函数
void ReadIr() interrupt 0
{
	u8 j,k;
	u16 err;
	Time13=0;					 
	delay13(700);	//7ms
	
	//进入中断函数内首先确认是否接收到的信号（引导码） 是真正的信号
	if(IRIN==1)
		return;
	
	
	// 继续判断输出数据是 1 还是 0。
	// 一个标准数据供有 32 位， 将其分别保存在IrValue 数组内， 
	// 并且根据数据与数据反码的规律判断此数据是否正确。
	// 当接收外一组数据后会自动退出中断服务函数， 从而继续执行主函数。
	
	
	// 当两个条件都为真是循环， 如果有一个条件为假的时候跳出循环，免得程序出错的时侯， 程序死在这里
	err=1000;				//1000*10us=10ms,超过说明接收到错误的信号
	while((IRIN==0)&&(err>0))	// 等待前面9ms的低电平过去
	{			
		delay13(1);
		err--;
	}
	
	if(IRIN==1)			//如果正确等到9ms低电平
	{
		err=500;
		//等待4.5ms的起始高电平过去
		while((IRIN==1)&&(err>0))		 
		{
			delay13(1);
			err--;
		}
		
		
		// 共有4组数据
		// --------------------------------------------------------
		for(k=0;k<4;k++)		
		{				
			for(j=0;j<8;j++) //接收一组数据
			{
				
				//等待信号前面的560us低电平过去
				err=60;		
				while((IRIN==0)&&(err>0))
				{
					delay13(1);
					err--;
				}
				
				//计算高电平的时间长度。
				err=500;
				while((IRIN==1)&&(err>0))	 
				{
					delay13(10);	 //0.1ms
					Time13++;
					err--;
					if(Time13>30)
					{
						return;
					}
				}
				
				IrValue[k]>>=1;	 //k表示第几组数据
				if(Time13>=8)		 //如果高电平出现大于565us，那么是1
				{
					IrValue[k]|=0x80;
				}
				Time13=0;		//用完时间要重新赋值							
			} // end for j
		} // end for k
		// --------------------------------------------------------
		
	} // end if
	
	
	if(IrValue[2]!=~IrValue[3])
		return;
			
}

void main13()
{	
	IrInit();
	while(1)
	{	
		DisplayData13[0] = smgduan13[IrValue[2]/16];
		DisplayData13[1] = smgduan13[IrValue[2]%16];
		DisplayData13[2] = smgduan13[16];
	  DigDisplay13();		
	}		
}

