/*
 * LCD_prog.c
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */


#include "stdTypes.h"
#include "errorState.h"

#include "DIO_init.h"

#include "LCD_config.h"
#include "LCD_priv.h"

#include "util/delay.h"



ES_t LCD_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	Local_enuErrorState =DIO_enuSetPinDirection(RS_PORT , RS_PIN , DIO_u8OUTPUT);
	Local_enuErrorState =DIO_enuSetPinDirection(RW_PORT , RW_PIN , DIO_u8OUTPUT);
	Local_enuErrorState =DIO_enuSetPinDirection(EN_PORT , EN_PIN , DIO_u8OUTPUT);

	Local_enuErrorState =DIO_enuSetPinDirection(D7_PORT , D7_PIN , DIO_u8OUTPUT);
	Local_enuErrorState =DIO_enuSetPinDirection(D6_PORT , D6_PIN , DIO_u8OUTPUT);
	Local_enuErrorState =DIO_enuSetPinDirection(D5_PORT , D5_PIN , DIO_u8OUTPUT);
	Local_enuErrorState =DIO_enuSetPinDirection(D4_PORT , D4_PIN , DIO_u8OUTPUT);


#if (LCD_MODE == EIGHT_BIT_MODE)
	Local_enuErrorState =DIO_enuSetPinDirection(D3_PORT , D3_PIN , DIO_u8OUTPUT);
	Local_enuErrorState =DIO_enuSetPinDirection(D2_PORT , D2_PIN , DIO_u8OUTPUT);
	Local_enuErrorState =DIO_enuSetPinDirection(D1_PORT , D1_PIN , DIO_u8OUTPUT);
	Local_enuErrorState =DIO_enuSetPinDirection(D0_PORT , D0_PIN , DIO_u8OUTPUT);

	_delay_ms(35);

	Local_enuErrorState = LCD_enuSendCommand(0x38);

#elif (LCD_MODE == FOUR_BIT_MODE)
	_delay_ms(35);

	Local_enuErrorState = LCD_enuSendCommand(0x28);

#else
#error"WRONG MODE SELECTION"

#endif

	_delay_ms(1);
	Local_enuErrorState = LCD_enuSendCommand(0x0F);
	_delay_ms(1);
	Local_enuErrorState = LCD_enuSendCommand(0x01);
	_delay_ms(2);
	Local_enuErrorState = LCD_enuSendCommand(0x06);
    Local_enuErrorState = LCD_enuSendCommand(0x80);

	return Local_enuErrorState;
}



ES_t LCD_enuDisplayChar(u8 Copy_u8Data)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*		LOGICAL PINS		*/
	Local_enuErrorState =DIO_enuSetPinValue(RS_PORT , RS_PIN , DIO_u8HIGH);
	Local_enuErrorState =DIO_enuSetPinValue(RW_PORT , RW_PIN , DIO_u8LOW);
	Local_enuErrorState =DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8LOW);

	/*		 DATA PINS			*/
	Local_enuErrorState =DIO_enuSetPinValue(D7_PORT , D7_PIN , ( ((Copy_u8Data)>>7)&1) );
	Local_enuErrorState =DIO_enuSetPinValue(D6_PORT , D6_PIN , ( ((Copy_u8Data)>>6)&1) );
	Local_enuErrorState =DIO_enuSetPinValue(D5_PORT , D5_PIN , ( ((Copy_u8Data)>>5)&1) );
	Local_enuErrorState =DIO_enuSetPinValue(D4_PORT , D4_PIN , ( ((Copy_u8Data)>>4)&1) );
#if (LCD_MODE == EIGHT_BIT_MODE)
	Local_enuErrorState =DIO_enuSetPinValue(D3_PORT , D3_PIN , ( ((Copy_u8Data)>>3)&1) );
	Local_enuErrorState =DIO_enuSetPinValue(D2_PORT , D2_PIN , ( ((Copy_u8Data)>>2)&1) );
	Local_enuErrorState =DIO_enuSetPinValue(D1_PORT , D1_PIN , ( ((Copy_u8Data)>>1)&1) );
	Local_enuErrorState =DIO_enuSetPinValue(D0_PORT , D0_PIN , ( ((Copy_u8Data)>>0)&1) );

	// Enable latch
	Local_enuErrorState =DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8HIGH);
	_delay_ms(10);
	Local_enuErrorState =DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8LOW);

#elif (LCD_MODE == FOUR_BIT_MODE)
	Local_enuErrorState =DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8HIGH);
	_delay_ms(2);
	Local_enuErrorState =DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8LOW);

	Local_enuErrorState =DIO_enuSetPinValue(D7_PORT , D3_PIN , ( ((Copy_u8Data)>>3)&1) );
	Local_enuErrorState =DIO_enuSetPinValue(D6_PORT , D2_PIN , ( ((Copy_u8Data)>>2)&1) );
	Local_enuErrorState =DIO_enuSetPinValue(D5_PORT , D1_PIN , ( ((Copy_u8Data)>>1)&1) );
	Local_enuErrorState =DIO_enuSetPinValue(D4_PORT , D0_PIN , ( ((Copy_u8Data)>>0)&1) );

	Local_enuErrorState =DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8HIGH);
	_delay_ms(2);
	Local_enuErrorState =DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8LOW);

#else
#error"WRONG MODE SELECTION"

#endif

	return Local_enuErrorState;
}



ES_t LCD_enuSendCommand(u8 Copy_u8Command)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*		LOGICAL PINS		*/
	Local_enuErrorState =DIO_enuSetPinValue(RS_PORT , RS_PIN , DIO_u8LOW);
	Local_enuErrorState =DIO_enuSetPinValue(RW_PORT , RW_PIN , DIO_u8LOW);
	Local_enuErrorState =DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8LOW);

	/*		 DATA PINS			*/
	Local_enuErrorState =DIO_enuSetPinValue(D7_PORT , D7_PIN , ( ((Copy_u8Command)>>7)&1) );
	Local_enuErrorState =DIO_enuSetPinValue(D6_PORT , D6_PIN , ( ((Copy_u8Command)>>6)&1) );
	Local_enuErrorState =DIO_enuSetPinValue(D5_PORT , D5_PIN , ( ((Copy_u8Command)>>5)&1) );
	Local_enuErrorState =DIO_enuSetPinValue(D4_PORT , D4_PIN , ( ((Copy_u8Command)>>4)&1) );

#if (LCD_MODE == EIGHT_BIT_MODE)
	Local_enuErrorState =DIO_enuSetPinValue(D3_PORT , D3_PIN , ( ((Copy_u8Command)>>3)&1) );
	Local_enuErrorState =DIO_enuSetPinValue(D2_PORT , D2_PIN , ( ((Copy_u8Command)>>2)&1) );
	Local_enuErrorState =DIO_enuSetPinValue(D1_PORT , D1_PIN , ( ((Copy_u8Command)>>1)&1) );
	Local_enuErrorState =DIO_enuSetPinValue(D0_PORT , D0_PIN , ( ((Copy_u8Command)>>0)&1) );

	// Enable latch
	Local_enuErrorState =DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8HIGH);
	_delay_ms(10);
	Local_enuErrorState =DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8LOW);

#elif (LCD_MODE == FOUR_BIT_MODE)
	Local_enuErrorState =DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8HIGH);
	_delay_ms(2);
	Local_enuErrorState =DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8LOW);

	Local_enuErrorState =DIO_enuSetPinValue(D7_PORT , D7_PIN , ( ((Copy_u8Command)>>3)&1) );
	Local_enuErrorState =DIO_enuSetPinValue(D6_PORT , D6_PIN , ( ((Copy_u8Command)>>2)&1) );
	Local_enuErrorState =DIO_enuSetPinValue(D5_PORT , D5_PIN , ( ((Copy_u8Command)>>1)&1) );
	Local_enuErrorState =DIO_enuSetPinValue(D4_PORT , D4_PIN , ( ((Copy_u8Command)>>0)&1) );

	Local_enuErrorState =DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8HIGH);
	_delay_ms(2);
	Local_enuErrorState =DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8LOW);


#else
#error"WRONG MODE SELECTION"

#endif

	return Local_enuErrorState;
}



ES_t LCD_enuSendString(const char* Copy_pcString)
{
	ES_t Local_enuErrorState = ES_NOK;
if(Copy_pcString != NULL)
{
	u8 Local_u8Iterator=0;
	while(Copy_pcString[Local_u8Iterator]!='\0')
	{
		Local_enuErrorState = LCD_enuDisplayChar(Copy_pcString[Local_u8Iterator]);
		Local_u8Iterator ++;
	}

}
else
{
	Local_enuErrorState=ES_NULL_POINTER;
}

	return Local_enuErrorState;
}



ES_t LCD_enuGoToXY(u8 Copy_u8X , u8 Copy_u8Y)
{
	ES_t Local_enuErrorState = ES_NOK;


	if(Copy_u8X== 0)
	{
		Local_enuErrorState = LCD_enuSendCommand((0x80)+Copy_u8Y);
	}
	else if(Copy_u8X== 1)
	{
		Local_enuErrorState = LCD_enuSendCommand((0xC0)+Copy_u8Y);
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}



ES_t LCD_enuSaveSpecialChar(u8 * Copy_pu8Arr,u8 Copy_u8Pattern_num )
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pu8Arr != NULL)
	{
		if(Copy_u8Pattern_num<=Pattern7)
		{
			Local_enuErrorState =LCD_enuSendCommand((8*Copy_u8Pattern_num)+0x40);
			u8 Local_u8Iterator=0;
			for(Local_u8Iterator =0 ;Local_u8Iterator<8 ; Local_u8Iterator++ )
			{
				Local_enuErrorState =LCD_enuDisplayChar(Copy_pu8Arr[Local_u8Iterator]);
			}
//			Local_enuErrorState =LCD_enuGoToXY(Copy_u8X , Copy_u8Y);
//			Local_enuErrorState =LCD_enuDisplayChar(Copy_u8Pattern_num);
		}
		else
		{
			Local_enuErrorState =ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorState =ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}



ES_t LCD_enuDisplaySpecialChar(u8 Copy_u8Pattern_num, u8 Copy_u8X , u8 Copy_u8Y)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_u8Pattern_num<=Pattern7)
	{
	Local_enuErrorState =LCD_enuGoToXY(Copy_u8X , Copy_u8Y);
	Local_enuErrorState =LCD_enuDisplayChar(Copy_u8Pattern_num);
	}
	else
	{
		Local_enuErrorState =ES_OUT_OF_RANGE;
	}
	return Local_enuErrorState;
}



ES_t LCD_enuWriteNum(s32 Copy_s32Num)
{
	ES_t Local_enuErrorState = ES_NOK;
	u32 Local_u32FinalNum=0 , Local_u32Num=0;
	u8 Local_u8NumDigit=0;
	if(Copy_s32Num<0)
	{
		Copy_s32Num*=-1;
		Local_enuErrorState =LCD_enuDisplayChar('-');
	}
	if(Copy_s32Num!=0)
	{
	while(Copy_s32Num>0)
	{
		Local_u32Num=Copy_s32Num%10;
		Local_u32FinalNum = Local_u32FinalNum*10 + Local_u32Num;
		Copy_s32Num/=10;
		Local_u8NumDigit ++;

	}

	while(Local_u8NumDigit)
	{
		Local_u32Num = Local_u32FinalNum%10;
		Local_enuErrorState = LCD_enuDisplayChar(Local_u32Num+'0');
		Local_u32FinalNum/=10;

		Local_u8NumDigit--;
	}
	}
	else
	{
		Local_enuErrorState = LCD_enuDisplayChar('0');
	}
	return Local_enuErrorState;
}



ES_t LCD_enuClearLCD()
{
	ES_t Local_enuErrorState = ES_NOK;

	LCD_enuSendCommand(0x01);		/* clear display */
	LCD_enuSendCommand(0x80);

	return Local_enuErrorState;
}


/*
 Local_enuErrorState =ES_OK;


 if( Local_enuErrorState ==ES_OK)
 DIO_enuSetPinValue(RS_PORT , RS_PIN , DIO_u8HIGH);
 else
 Local_enuErrorState =DIO_enuSetPinValue(RS_PORT , RS_PIN , DIO_u8HIGH);
 */
