/*
 * main.c
 *
 *  Created on: Aug 30, 2023
 *      Author: DELL
 */
#include "stdTypes.h"
#include "errorState.h"

#include "PORT_init.h"
#include "DIO_init.h"
#include "EXTI_init.h"
#include "LCD_init.h"
#include "GIE.h"

#include "util/delay.h"

u8 volatile p1=0,p2=0,p=0;//p is working as a switch to turn on\off the game

void func1(void);
void func2(void);
void func3(void);


int main()
{
	PORT_enuInit();
	DIO_enuInit();
	LCD_enuInit();
	EXTI_enuInit();

	EXTI_enuCallBack(INT0,&func1);
	EXTI_enuCallBack(INT1,&func2);
	EXTI_enuCallBack(INT2,&func3);

	EnableGlobalEnterrupt();

	u8 Local_Iterator;

	LCD_enuSendCommand(0x0c);//to turn off  the cursor and its blink

	LCD_enuGoToXY(0,0);
	LCD_enuSendString("Press the button");
	LCD_enuGoToXY(1,5);
	LCD_enuSendString("to play");

	while(1)
	{
		while(p)
		{
		if(p1==1)
		{
			if(!p)
				break;
			LCD_enuClearLCD();
			LCD_enuGoToXY(0,2);
			LCD_enuSendString("Player 2 WIN");
			_delay_ms(500);
			LCD_enuGoToXY(1,3);
			LCD_enuSendString("Play again?");
			p=0;
			break;
		}
		for(Local_Iterator=1;Local_Iterator<15;Local_Iterator++)
		{
			if(!p)
				break;
			LCD_enuGoToXY(!(Local_Iterator&1),Local_Iterator);
			LCD_enuDisplayChar('o');
			_delay_ms(150);
			LCD_enuGoToXY(!(Local_Iterator&1),Local_Iterator);
			LCD_enuDisplayChar(' ');
		}
		if(p2==0)
		{
			if(!p)
				break;
			LCD_enuClearLCD();
			LCD_enuGoToXY(0,2);
			LCD_enuSendString("Player 1 WIN");
			_delay_ms(500);
			LCD_enuGoToXY(1,3);
			LCD_enuSendString("Play again?");
			p=0;
			break;
		}
		for(Local_Iterator=14;Local_Iterator>0;Local_Iterator--)
		{
			if(!p)
				break;
			LCD_enuGoToXY(!(Local_Iterator&1),Local_Iterator);
			LCD_enuDisplayChar('o');
			_delay_ms(150);
			LCD_enuGoToXY(!(Local_Iterator&1),Local_Iterator);
			LCD_enuDisplayChar(' ');
		}
		}
	}
}




void func1(void)
{
	if(p1==1)
	{
		LCD_enuGoToXY(1,0);
		LCD_enuDisplayChar(' ');
		LCD_enuGoToXY(0,0);
		LCD_enuDisplayChar('|');
		p1=0;
	}
	else
	{
		LCD_enuGoToXY(0,0);
		LCD_enuDisplayChar(' ');
		LCD_enuGoToXY(1,0);
		LCD_enuDisplayChar('|');
		p1=1;
	}
}

void func2(void)
{
	if(p2==1)
	{
		LCD_enuGoToXY(1,15);
		LCD_enuDisplayChar(' ');
		LCD_enuGoToXY(0,15);
		LCD_enuDisplayChar('|');
		p2=0;
	}
	else
	{
		LCD_enuGoToXY(0,15);
		LCD_enuDisplayChar(' ');
		LCD_enuGoToXY(1,15);
		LCD_enuDisplayChar('|');
		p2=1;
	}
}

void func3(void)
{
	if(p==1)
	{
		LCD_enuClearLCD();
		LCD_enuGoToXY(0,0);
		LCD_enuSendString("Press the button");
		LCD_enuGoToXY(1,5);
		LCD_enuSendString("to play");
		p=0;
		_delay_ms(300);
	}
	else
	{
		LCD_enuClearLCD();
		LCD_enuGoToXY(0,0);
		LCD_enuDisplayChar('|');
		LCD_enuGoToXY(0,15);
		LCD_enuDisplayChar('|');
		p=1;
	}
}
