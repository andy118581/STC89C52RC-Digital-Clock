#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
#include "Timer0.h"
#include "UART.h"
void Data_update();

unsigned char SettingMode=0; 
unsigned char KeyNum=0;      //遞增或遞減及確認鍵變數


unsigned char Key_Scan(void)
{
	KeyNum=0;
	if(P3_1==0)
	{
		Delay(30);
		if(P3_1==0)
		{
			while(P3_1==0);
			Delay(30);
			KeyNum=1;
		}
	}else if(P3_0==0)
	{
		Delay(30);
		if(P3_0==0)
		{
			while(P3_0==0);
			Delay(30);
			KeyNum=2;
		}
	}else if(P3_2==0)
	{
		Delay(30);
		if(P3_2==0)
		{
			while(P3_2==0);
			Delay(30);
			KeyNum=3;
		}
	}
	return KeyNum;
}


unsigned int min=59;
unsigned int hr=11;

unsigned int day=31;
unsigned int mon=12;
unsigned int year=2026;

unsigned int am_pm=1;
unsigned int T0Count=0;

unsigned int sec=50;


unsigned char GetMaxDay(void)
{
	if(mon==2)
	{
		if((year%4==0&&year%100!=0)||(year%400==0))
		{
			return 29;
		}else
		{
			return 28;
		}
	}else if(mon==4||mon==6||mon==9||mon==11)
	{
		return 30;
	}else
	{
		return 31;
	}
}


void main()
{	
	LCD_Init();
	Timer0_Init();
	UART_Init();
	while(1)
	{	
		if(am_pm%2==0)
		{
			LCD_ShowString(1,1,"AM");
		}else if(am_pm%2==1)
		{
			LCD_ShowString(1,1,"PM");
		}
		LCD_ShowNum(1,9,hr,2);
		LCD_ShowChar(1,11,':');

		LCD_ShowNum(1,12,min,2);
		LCD_ShowChar(1,14,':');

		LCD_ShowNum(1,15,sec,2);

		LCD_ShowNum(2,7,year,4);
		LCD_ShowChar(2,11,'/');

		LCD_ShowNum(2,12,mon,2);
		LCD_ShowChar(2,14,'/');

		LCD_ShowNum(2,15,day,2);
		
		KeyNum=Key_Scan();
		switch(SettingMode)
		{
			case 0:
				if(KeyNum==1)
				{
					TR0=0;
					SettingMode=1;
				}
				break;
			case 1:
				if(KeyNum==1)
				{
					hr++;
					if(hr>12)
					{
						hr=1;
					}
					LCD_ShowNum(1,9,hr,2);
				}else if(KeyNum==2)
				{
					if(hr<=1)
					{
						hr=12;
					}else
					{
						hr--;
					}
					LCD_ShowNum(1,9,hr,2);
				}else if(KeyNum==3)
				{
					SettingMode=2;
				}
				break;
			case 2:
				if(KeyNum==1)
				{
					min++;
					if(min>59)
					{
						min=0;
					}
					LCD_ShowNum(1,12,min,2);
				}else if(KeyNum==2)
				{
					if(min==0)
					{
						min=59;
					}else
					{
						min--;
					}
					LCD_ShowNum(1,12,min,2);
				}else if(KeyNum==3)
				{
					SettingMode=3;
				}
				break;
			case 3:
				if(KeyNum==1)
				{
					sec++;
					if(sec>59)
					{
						sec=0;
					}
					LCD_ShowNum(1,15,sec,2);
				}else if(KeyNum==2)
				{
					if(sec==0)
					{
						sec=59;
					}else
					{
						sec--;
					}
					LCD_ShowNum(1,15,sec,2);
				}else if(KeyNum==3)
				{
					SettingMode=4;
				}
				break;
			case 4:
				if(KeyNum==1)
				{
					am_pm=1-am_pm;
				}else if(KeyNum==2)
				{
					am_pm=1-am_pm;
				}else if(KeyNum==3)
				{
					SettingMode=5;
				}
				if(am_pm==0)
				{
					LCD_ShowString(1,1,"AM");
				}else
				{
					LCD_ShowString(1,1,"PM");
				}
				break;
			case 5:
				if(KeyNum==1)
				{
					year++;
					if(year>9999)
					{
						year=1;
					}
					LCD_ShowNum(2,7,year,4);
				}else if(KeyNum==2)
				{
					if(year<=1)
					{
						year=9999;
					}else
					{
						year--;
					}
					LCD_ShowNum(2,7,year,4);
				}else if(KeyNum==3)
				{
					SettingMode=6;
				}
				break;
			case 6:
				if(KeyNum==1)
				{
					mon++;
					if(mon>12)
					{
						mon=1;
					}
					LCD_ShowNum(2,12,mon,2);
				}else if(KeyNum==2)
				{
					if(mon==1)
					{
						mon=12;
					}else
					{
						mon--;
					}
					LCD_ShowNum(2,12,mon,2);
				}else if(KeyNum==3)
				{
					SettingMode=7;
				}
				break;
			case 7:
				if(KeyNum==1)
				{
					day++;
					if(day>GetMaxDay())
					{
						day=1;
					}
					LCD_ShowNum(2,15,day,2);
				}else if(KeyNum==2)
				{
					if(day<=1)
					{
						day=GetMaxDay();
					}else
					{
						day--;
					}
					LCD_ShowNum(2,15,day,2);
				}else if(KeyNum==3)
				{
					SettingMode=8;
				}
				break;
			case 8:
				TR0=1;
				SettingMode=0;
			break;
		}
		
		if(P3_3==0)
		{
			Delay(30);
			while(P3_3==0);
			Delay(30);
			UART_SendTime(hr,min,sec);
		}
	}
}

void Timer0_RoCount() interrupt 1
{
	TH0=64614/256;
	TL0=64614%256;

	T0Count++;

	if(T0Count>=1000)
	{
		T0Count=0;
		sec++;
	}
		//  秒
	if(sec==60)
	{
		sec=0;
		min++;
	}
		
	//  分
	if(min==60)
	{
		min=0;
		hr++;
		//  時
		if(hr%12==0)
		{
			am_pm=1-am_pm;
			if(am_pm==0)
			{
				day++;
				Data_update();
			}
		}
		if(hr==13)
		{
			hr=1;
		}
	}
}

void Data_update(){
	//  日(大月)
	if(mon==1||mon==3||mon==5||mon==7||mon==8||mon==10||mon==12)
	{
		if(day==32)
		{
			day=1;
			mon++;
		}

	//  日(小月)
	}else if(mon==4||mon==6||mon==9||mon==11)
	{
		if(day==31)
		{
			day=1;
			mon++;
		}
			
	//  日(閏年2月)
	}else if(mon==2&&((year%4==0&&year%100!=0)||(year%100==0&&year%400==0)))
	{
		if(day==30)
		{
			day=1;
			mon++;
		}
		
	//  日(平年2月)
	}else if(mon==2&&!((year%4==0&&year%100!=0)||(year%400==0)))
	{
		if(day==29)
		{
			day=1;
			mon++;
		}
	}
	//  月
	if(mon==13)
	{
		mon=1;
		year++;
	}
}
