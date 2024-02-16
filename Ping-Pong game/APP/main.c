#include "stdTypes.h"
#include "errorState.h"

#include "PORT_init.h"
#include "DIO_init.h"
#include "EXTI_init.h"
#include "LCD_init.h"
#include "GIE.h"

#include "util/delay.h"


u8 volatile Player_1=0,Player_2=0, Switch=0;//Switch is working as a switch to turn on\off the game

void Player1Rocket(void* Copy_pvArg);
void Player2Rocket(void* Copy_pvArg);
void TurnOn_Off(void* Copy_pvArg);

void IntryToPlay(void);
void BallMovment (u8 Copy_u8Address);


int main()
{
	PORT_enuInit();
	DIO_enuInit();
	LCD_enuInit();
	EXTI_enuInit();

	EXTI_enuCallBack(INT0,Player1Rocket,NULL);
	EXTI_enuCallBack(INT1,Player2Rocket,NULL);
	EXTI_enuCallBack(INT2,TurnOn_Off,NULL);

	EnableGlobalEnterrupt();

	LCD_enuSendCommand(0x0c);//to turn off  the cursor and its blink


	u8 Local_Iterator;

	IntryToPlay();

	while(1)
	{

		while(Switch)
		{
			if(Player_1==1)
			{
				if(!Switch)
				{
					break;
				}
				else
				{
					LCD_enuClearLCD();
					LCD_enuGoToXY(0,2);
					LCD_enuSendString("Player 2 WIN");
					_delay_ms(500);
					LCD_enuGoToXY(1,3);
					LCD_enuSendString("Play again?");
					Switch=0;
					break;
				}
			}
			for(Local_Iterator=1;Local_Iterator<15;Local_Iterator++)
			{
				if(!Switch)
				{
					break;
				}
				else
				{
					BallMovment(Local_Iterator);
				}
			}
			if(Player_2==0)
			{
				if(!Switch)
				{
					break;
				}
				else
				{
				LCD_enuClearLCD();
				LCD_enuGoToXY(0,2);
				LCD_enuSendString("Player 1 WIN");
				_delay_ms(500);
				LCD_enuGoToXY(1,3);
				LCD_enuSendString("Play again?");
				Switch=0;
				break;
				}
			}
			for(Local_Iterator=14;Local_Iterator>0;Local_Iterator--)
			{
				if(!Switch)
				{
					break;
				}
				else
				{
					BallMovment(Local_Iterator);
				}
			}
		}
		Player_1=0,Player_2=0;
	}
}

//==============================================================================================================================================


void Player1Rocket(void* Copy_pvArg)
{
	if(Player_1==1)
	{
		LCD_enuGoToXY(1,0);
		LCD_enuDisplayChar(' ');
		LCD_enuGoToXY(0,0);
		LCD_enuDisplayChar('|');
		Player_1=0;
	}
	else
	{
		LCD_enuGoToXY(0,0);
		LCD_enuDisplayChar(' ');
		LCD_enuGoToXY(1,0);
		LCD_enuDisplayChar('|');
		Player_1=1;
	}
}

void Player2Rocket(void* Copy_pvArg)
{
	if(Player_2==1)
	{
		LCD_enuGoToXY(1,15);
		LCD_enuDisplayChar(' ');
		LCD_enuGoToXY(0,15);
		LCD_enuDisplayChar('|');
		Player_2=0;
	}
	else
	{
		LCD_enuGoToXY(0,15);
		LCD_enuDisplayChar(' ');
		LCD_enuGoToXY(1,15);
		LCD_enuDisplayChar('|');
		Player_2=1;
	}
}

void TurnOn_Off(void* Copy_pvArg)
{
	if(Switch==1)
	{
		IntryToPlay();
		Switch=0;
		_delay_ms(300);
	}
	else
	{
		LCD_enuClearLCD();
		LCD_enuGoToXY(0,0);
		LCD_enuDisplayChar('|');
		LCD_enuGoToXY(0,15);
		LCD_enuDisplayChar('|');
		Switch=1;
	}
}

//===============================================================================================================================================

void IntryToPlay(void)
{
	LCD_enuClearLCD();
	LCD_enuGoToXY(0,0);
	LCD_enuSendString("Press the button");
	LCD_enuGoToXY(1,5);
	LCD_enuSendString("to play");
}

void BallMovment (u8 Copy_u8Address)
{
	LCD_enuGoToXY(!(Copy_u8Address&1),Copy_u8Address);
	LCD_enuDisplayChar('o');
	_delay_ms(150);
	LCD_enuGoToXY(!(Copy_u8Address&1),Copy_u8Address);
	LCD_enuDisplayChar(' ');
}
