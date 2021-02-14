#include "public.h"  
#include "uart.h"
#include "tftlcd.h"
#include "touch.h"
#include "gui.h"


/*
//字符数字显示测试
void CharacterShow_Test(void)
{
	FRONT_COLOR=RED;
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,12,"Hello World!");
	LCD_ShowString(10,30,tftlcd_data.width,tftlcd_data.height,16,"Hello World!");
	LCD_ShowString(10,50,tftlcd_data.width,tftlcd_data.height,24,"Hello World!");
	FRONT_COLOR=WHITE;
	LCD_ShowString(10,80,tftlcd_data.width,tftlcd_data.height,12,"1234567890");
	LCD_ShowString(10,100,tftlcd_data.width,tftlcd_data.height,16,"1234567890");
	LCD_ShowString(10,120,tftlcd_data.width,tftlcd_data.height,24,"1234567890");
		
}


// ---------------------------------
//几何图形测试
void BaseGraphical_Test(void)
{
	FRONT_COLOR=RED;
	LCD_ShowString(tftlcd_data.width/2-7*12,0,tftlcd_data.width,tftlcd_data.height,16,"Base Graphical Test");
	
	FRONT_COLOR=WHITE;
	gui_draw_bigpoint(10,20,GREEN);
	gui_draw_bline(10,30,120,30,5,WHITE);
	gui_draw_rectangle(10,40,30,30,BLUE);
	gui_draw_arcrectangle(50,40,30,30,5,1,YELLOW,GREEN);
	gui_fill_rectangle(90,40,30,30,BRRED);
	gui_fill_ellipse(30,100,20,10,GBLUE);
	gui_fill_circle(80,100,20,MAGENTA);
	gui_draw_ellipse(30,130,20,10,WHITE);
	gui_draw_arc(60,140,100,180,80,160,20,WHITE,0);		
}


// ---------------------------------

//汉字显示测试
//todo: has bug and need to be solved. 2.12
void HZFontShow_Test(void)
{
	FRONT_COLOR=RED;
	LCD_ShowFontHZ(10,10,"年月日");
	FRONT_COLOR=WHITE;
	LCD_ShowFontHZ(10,50,"星");
	FRONT_COLOR=GREEN;
	LCD_ShowFontHZ(10,90,"期");	
}



// ---------------------------------
#define LED_START_X		20	  				//LED起始X坐标
#define LED_START_Y		80						//LED起始Y坐标
#define LED_SPACE_X		10						//LED间隔X坐标
#define LED_RADIUS		15						//LED图形圆半径
#define LED_DIAMETER	LED_RADIUS*2	//LED图形圆直径

#define LED_BACKCOLOR	WHITE  			//背景色
#define LED_FRONTCOLOR	BLUE   		//前景色
#define LED_SPEED		1000	 				//单位ms


//流水灯滚动测试
void LEDFlow_Test(void)
{
	u8 i=0;

	FRONT_COLOR=RED;
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,16,"LED Flow Test");
	for(i=0;i<4;i++)
	{
		gui_fill_circle(LED_START_X+(LED_DIAMETER+LED_SPACE_X)*i,LED_START_Y,LED_RADIUS,LED_BACKCOLOR);	
	}
	
	while(1)
	{
		gui_fill_circle(LED_START_X+(LED_DIAMETER+LED_SPACE_X)*(3),LED_START_Y,LED_RADIUS,LED_BACKCOLOR);
		gui_fill_circle(LED_START_X+(LED_DIAMETER+LED_SPACE_X)*0,LED_START_Y,LED_RADIUS,LED_FRONTCOLOR);	
		delay_ms(LED_SPEED);
		for(i=1;i<4;i++)
		{
			gui_fill_circle(LED_START_X+(LED_DIAMETER+LED_SPACE_X)*(i-1),LED_START_Y,LED_RADIUS,LED_BACKCOLOR);
			gui_fill_circle(LED_START_X+(LED_DIAMETER+LED_SPACE_X)*i,LED_START_Y,LED_RADIUS,LED_FRONTCOLOR);	
			delay_ms(LED_SPEED);
		}	
	}	
}



// ---------------------------------
#define PROGRESSBAR_START_X		10	  	//进度条起始X坐标
#define PROGRESSBAR_START_Y		50		//进度条起始Y坐标
#define PROGRESSBAR_WIDTH		100		//进度条长
#define PROGRESSBAR_HEIGHT		15		//进度条高

#define PROGRESSBAR_BACKCOLOR	GREEN  	//背景色
#define PROGRESSBAR_FRONTCOLOR	RED   	//前景色
#define PROGRESSBAR_FONTCOLOR	BLUE   //进度数值颜色


//进度条显示
//percent：进度，百分数
void ProgressBar_Show(u8 percent)
{
	static u8 int_flag=0;
	u8 temp[4];
	u8 color_temp=0;
	u8 font_size=12;

	color_temp=BACK_COLOR;
	if(percent<10)
	{
		temp[0]=' ';
		temp[1]=' ';
		temp[2]=percent%100%10+0x30;	
	}	
	else if(percent<100)
	{
		temp[0]=' ';
		temp[1]=percent%100/10+0x30;
		temp[2]=percent%100%10+0x30;
	}
	else
	{
		temp[0]=percent/100+0x30;
		temp[1]=percent%100/10+0x30;
		temp[2]=percent%100%10+0x30;	
	}		
	temp[3]='%';
	if(int_flag==0) //只进行一次初始化
	{
		int_flag=1;
		gui_fill_rectangle(PROGRESSBAR_START_X,PROGRESSBAR_START_Y,PROGRESSBAR_WIDTH,
			PROGRESSBAR_HEIGHT,PROGRESSBAR_BACKCOLOR);		
	}
	gui_fill_rectangle(PROGRESSBAR_START_X,PROGRESSBAR_START_Y,percent,
		PROGRESSBAR_HEIGHT,PROGRESSBAR_FRONTCOLOR);
	if(percent>(PROGRESSBAR_WIDTH/2))
	{
		gui_show_strmidex(PROGRESSBAR_START_X,PROGRESSBAR_START_Y,PROGRESSBAR_WIDTH,
			PROGRESSBAR_HEIGHT,PROGRESSBAR_FONTCOLOR,font_size,temp,1);	
	}
	else
	{
		BACK_COLOR=PROGRESSBAR_BACKCOLOR;
		gui_show_strmidex(PROGRESSBAR_START_X,PROGRESSBAR_START_Y,PROGRESSBAR_WIDTH,
			PROGRESSBAR_HEIGHT,PROGRESSBAR_FONTCOLOR,font_size,temp,0);	
	}	
	BACK_COLOR=color_temp;
}

//进度条测试
void ProgressBar_Test(void)
{
	u8 i=0;

	FRONT_COLOR=RED;
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,16,"ProgressBar Test");
	
	
	while(1)
	{
		gui_fill_rectangle(PROGRESSBAR_START_X,PROGRESSBAR_START_Y,PROGRESSBAR_WIDTH,
			PROGRESSBAR_HEIGHT,PROGRESSBAR_BACKCOLOR);
		for(i=1;i<=100;i++)
		{
			ProgressBar_Show(i);
			delay_ms(50);	
		}	
	}	
}
*/


// ----------------------------

u8 Touch_RST=0;


//触摸测试
void TOUCH_Test(void)
{
	
	static u16 penColor = BLUE;

	TOUCH_Scan();
	if(xpt_xy.sta)
	{	
		
		if(xpt_xy.lcdx>tftlcd_data.width)
			xpt_xy.lcdx=tftlcd_data.width-1;
		if(xpt_xy.lcdy>tftlcd_data.height)
			xpt_xy.lcdy=tftlcd_data.height-1;
		if((xpt_xy.lcdx>=(tftlcd_data.width-3*12))&&(xpt_xy.lcdy<24))
			Touch_RST=1;
		if(xpt_xy.lcdy > tftlcd_data.height - 20)
		{
			if(xpt_xy.lcdx>100)
			{
				penColor = YELLOW;
			}
			else if(xpt_xy.lcdx>80)
			{
				penColor = CYAN;
			}
			else if(xpt_xy.lcdx>60)
			{
				penColor = GREEN;
			}
			else if(xpt_xy.lcdx>40)
			{
				penColor = MAGENTA;
			}
			else if(xpt_xy.lcdx>20)
			{
				penColor = RED;
			}
			else if(xpt_xy.lcdx>0)
			{
				penColor = BLUE;
			}       
		}
		else
		{
			LCD_Fill(xpt_xy.lcdx-1,xpt_xy.lcdy-1,xpt_xy.lcdx+1,xpt_xy.lcdy+1,penColor);	
		}
							
	}		
}

//GUI测试
void GUI_Test(void)
{
	FRONT_COLOR=WHITE;
	LCD_ShowString(tftlcd_data.width/2-7*12,30,tftlcd_data.width,tftlcd_data.height,24,"draw by yourself!");
	LCD_ShowString(tftlcd_data.width/2-7*8,55,tftlcd_data.width,tftlcd_data.height,24,"GUI Test");
	
	FRONT_COLOR=RED;
	gui_draw_bigpoint(10,55,GREEN);
	gui_draw_bline(10,80,120,80,10,GREEN);
	gui_draw_rectangle(10,95,30,30,GREEN);
	gui_draw_arcrectangle(50,95,30,30,5,1,BLUE,GREEN);
	gui_fill_rectangle(90,95,30,30,GREEN);
	//gui_fill_circle(90,120,20,GREEN);
	gui_fill_ellipse(30,150,20,10,GREEN);

	//更多的GUI等待大家来发掘和编写
	
	delay_ms(2000);
	LCD_Clear(BACK_COLOR);		
}

void demo_touch()
{
	
	u16 color=0;

	UART_Init();
	TFTLCD_Init();

Start:
	//GUI_Test();
		
	FRONT_COLOR=WHITE;
	LCD_ShowString(tftlcd_data.width/2-7*12,30,tftlcd_data.width,tftlcd_data.height,24,"draw by yourself!");
	FRONT_COLOR=RED;
	LCD_ShowString(tftlcd_data.width-3*12,0,tftlcd_data.width,tftlcd_data.height,24,"RST");
	LCD_Fill(0, tftlcd_data.height - 20, 20, tftlcd_data.height, BLUE);
	LCD_Fill(20, tftlcd_data.height - 20, 40, tftlcd_data.height, RED);
	LCD_Fill(40, tftlcd_data.height - 20, 60, tftlcd_data.height, MAGENTA);
	LCD_Fill(60, tftlcd_data.height - 20, 80, tftlcd_data.height, GREEN);
	LCD_Fill(80, tftlcd_data.height - 20, 100, tftlcd_data.height, CYAN);
	LCD_Fill(100, tftlcd_data.height - 20, 120, tftlcd_data.height, YELLOW);
	
		
	while(1)
	{
		if(Touch_RST)
		{
			Touch_RST=0;
			LCD_Clear(BACK_COLOR);
			goto Start;
		}
		
		TOUCH_Test();
			
	}					
}



demo_common()
{
	UART_Init();
	TFTLCD_Init();

	//HZFontShow_Test();
	
	while(1)
	{
				
	}			
}



void main()
{
	demo_touch();
}
