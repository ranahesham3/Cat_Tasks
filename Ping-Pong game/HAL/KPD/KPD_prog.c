/*
 * KPD_prog.c
 *
 *  Created on: Aug 27, 2023
 *      Author: DELL
 */


#include "stdTypes.h"
#include "errorState.h"

#include "DIO_init.h"

#include "KPD_config.h"
#include "KPD_priv.h"

#include "util/delay.h"


ES_t Keypad_enuInit()
{
	ES_t Local_enuErrorState =ES_NOK;
	/*						Direction						*/
	Local_enuErrorState = DIO_enuSetPinDirection(C1_PORT , C1_PIN , DIO_u8OUTPUT);
	Local_enuErrorState = DIO_enuSetPinDirection(C2_PORT , C2_PIN , DIO_u8OUTPUT);
	Local_enuErrorState = DIO_enuSetPinDirection(C3_PORT , C3_PIN , DIO_u8OUTPUT);
	Local_enuErrorState = DIO_enuSetPinDirection(C4_PORT , C4_PIN , DIO_u8OUTPUT);

	Local_enuErrorState = DIO_enuSetPinDirection(R1_PORT , R1_PIN , DIO_u8INPUT);
	Local_enuErrorState = DIO_enuSetPinDirection(R2_PORT , R2_PIN , DIO_u8INPUT);
	Local_enuErrorState = DIO_enuSetPinDirection(R3_PORT , R3_PIN , DIO_u8INPUT);
    Local_enuErrorState = DIO_enuSetPinDirection(R4_PORT , R4_PIN , DIO_u8INPUT);

    /*						Value						*/
	Local_enuErrorState = DIO_enuSetPinValue(C1_PORT , C1_PIN , DIO_u8HIGH);
	Local_enuErrorState = DIO_enuSetPinValue(C2_PORT , C2_PIN , DIO_u8HIGH);
	Local_enuErrorState = DIO_enuSetPinValue(C3_PORT , C3_PIN , DIO_u8HIGH);
    Local_enuErrorState = DIO_enuSetPinValue(C4_PORT , C4_PIN , DIO_u8HIGH);

	Local_enuErrorState = DIO_enuSetPinValue(R1_PORT , R1_PIN , DIO_u8PULL_UP);
	Local_enuErrorState = DIO_enuSetPinValue(R2_PORT , R2_PIN , DIO_u8PULL_UP);
	Local_enuErrorState = DIO_enuSetPinValue(R3_PORT , R3_PIN , DIO_u8PULL_UP);
    Local_enuErrorState = DIO_enuSetPinValue(R4_PORT , R4_PIN , DIO_u8PULL_UP);

    Local_enuErrorState =ES_OK;

    return Local_enuErrorState;
}

u8 Keypad_enuGetPressedKey()
{
	ES_t Local_enuErrorState =ES_NOK;



		static u8 Local_Au8RowPins [ROWS_NUM] = { R1_PIN , R2_PIN , R3_PIN , R4_PIN };
		static u8 Local_Au8ColPins [COLS_NUM] = { C1_PIN , C2_PIN , C3_PIN , C4_PIN };
		static u8 Local_Au8RowPorts[ROWS_NUM] = { R1_PORT , R2_PORT , R3_PORT , R4_PORT };
		static u8 Local_Au8ColPorts[COLS_NUM] = { C1_PORT , C2_PORT , C3_PORT , C4_PORT };
		//static so you don't use too much memory in stack

		u8 Copy_pu8KeyValue =NOT_PRESSED;
		static u8 Local_Au8KPDArr[ROWS_NUM][COLS_NUM]={{'7', '8', '9', '+'},{'4', '5', '6', '-'},{'1', '2', '3', 'x'},{'c', '0', '=', '/'}};
		u8 Local_u8RowIdx=0,Local_u8ColIdx=0,Local_u8Pinval=0xff;

		 for(Local_u8ColIdx=0 ; Local_u8ColIdx <COLS_NUM ; Local_u8ColIdx ++)
		 {
			 /* activate the current col*/
			 DIO_enuSetPinValue(Local_Au8ColPorts [Local_u8ColIdx] , Local_Au8ColPins [Local_u8ColIdx] , DIO_u8LOW);

			 for(Local_u8RowIdx=0 ; Local_u8RowIdx <ROWS_NUM ; Local_u8RowIdx++)
			 {
				 DIO_enuGetPinValue(Local_Au8RowPorts [Local_u8RowIdx] , Local_Au8RowPins [Local_u8RowIdx] , &Local_u8Pinval);
				 if(Local_u8Pinval == 0)
				 {
					 Copy_pu8KeyValue =Local_Au8KPDArr[Local_u8RowIdx][Local_u8ColIdx];
					 /*Polling (busy waiting) until the key is released*/
					 while(Local_u8Pinval== 0)
					 {
						 //Local_u8Pinval=1;
						 DIO_enuGetPinValue(Local_Au8RowPorts [Local_u8RowIdx] , Local_Au8RowPins [Local_u8RowIdx] , &Local_u8Pinval);
					 }
					 Local_enuErrorState= ES_OK;
					 return Copy_pu8KeyValue;

				 }
			 }
			 DIO_enuSetPinValue(Local_Au8ColPorts [Local_u8ColIdx] , Local_Au8ColPins [Local_u8ColIdx] , DIO_u8HIGH);
		 }
	return Copy_pu8KeyValue;
}


/*ES_t Keypad_enuGetPressedKey(u8 * Copy_pu8KeyValue)
{
	ES_t Local_enuErrorState =ES_NOK;

	if (Copy_pu8KeyValue != NULL)
	{
		u8 Local_Au8RowPins [ROWS_NUM] = { R1_PIN , R2_PIN , R3_PIN , R4_PIN };
		u8 Local_Au8ColPins [COLS_NUM] = { C1_PIN , C2_PIN , C3_PIN , C4_PIN };
		u8 Local_Au8RowPorts[ROWS_NUM] = { R1_PORT , R2_PORT , R3_PORT , R4_PORT };
		u8 Local_Au8ColPorts[COLS_NUM] = { C1_PORT , C2_PORT , C3_PORT , C4_PORT };

		*Copy_pu8KeyValue = NOT_PRESSED;

		u8 Local_Au8KeyValues[ROWS_NUM][COLS_NUM] = KEYS_VALUES;

		u8 Local_u8PinValue = 0xff;

		u8 Local_u8RowIter , Local_u8ColIter;

		for (Local_u8ColIter =0; Local_u8ColIter < COLS_NUM ; Local_u8ColIter ++)
		{
			DIO_enuSetPinValue(Local_Au8ColPorts[Local_u8ColIter] , Local_Au8ColPins[Local_u8ColIter] , DIO_u8LOW);

			for (Local_u8RowIter =0 ; Local_u8RowIter <ROWS_NUM ; Local_u8RowIter ++)
			{
				DIO_enuGetPinValue(Local_Au8RowPorts[Local_u8RowIter], Local_Au8RowPins[Local_u8RowIter], &Local_u8PinValue);
				if (! Local_u8PinValue)
				{
					//_delay_ms(10);
					DIO_enuGetPinValue(Local_Au8RowPorts[Local_u8RowIter], Local_Au8RowPins[Local_u8RowIter], &Local_u8PinValue);
					if (! Local_u8PinValue)
					{
						while (! Local_u8PinValue)
						{
							DIO_enuGetPinValue(Local_Au8RowPorts[Local_u8RowIter], Local_Au8RowPins[Local_u8RowIter], &Local_u8PinValue);
						}

						*Copy_pu8KeyValue = Local_Au8KeyValues[Local_u8RowIter][Local_u8ColIter];

						return Local_enuErrorState=ES_OK;
					}
				}
			}

			DIO_enuSetPinValue(Local_Au8ColPorts[Local_u8ColIter] , Local_Au8ColPins[Local_u8ColIter] , DIO_u8HIGH);
		}
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}*/


/*
ES_t Keypad_enuGetPressedKey(u8 * Copy_pu8KeyValue)
{
	ES_t Local_enuErrorState =ES_NOK;

	if(Copy_pu8KeyValue != NULL)
	{
		static u8 Local_Au8RowPins [ROWS_NUM] = { R1_PIN , R2_PIN , R3_PIN , R4_PIN };
		static u8 Local_Au8ColPins [COLS_NUM] = { C1_PIN , C2_PIN , C3_PIN , C4_PIN };
		static u8 Local_Au8RowPorts[ROWS_NUM] = { R1_PORT , R2_PORT , R3_PORT , R4_PORT };
		static u8 Local_Au8ColPorts[COLS_NUM] = { C1_PORT , C2_PORT , C3_PORT , C4_PORT };
		//static so you don't use too much memory in stack

		* Copy_pu8KeyValue =NOT_PRESSED;
		static u8 Local_Au8KPDArr[ROWS_NUM][COLS_NUM]=KEYS_VALUES;
		 u8 Local_u8RowIdx=0,Local_u8ColIdx=0,Local_u8Pinval=0xff;

		 for(Local_u8ColIdx=0 ; Local_u8ColIdx <COLS_NUM ; Local_u8ColIdx ++)
		 {
			*/ /* activate the current col*/
/*
			 Local_enuErrorState = DIO_enuSetPinValue(Local_Au8ColPorts [Local_u8ColIdx] , Local_Au8ColPins [Local_u8ColIdx] , DIO_u8LOW);

			 for(Local_u8RowIdx=0 ; Local_u8RowIdx <ROWS_NUM ; Local_u8RowIdx++)
			 {
				 Local_enuErrorState = DIO_enuGetPinValue(Local_Au8RowPorts [Local_u8RowIdx] , Local_Au8RowPins [Local_u8RowIdx] , &Local_u8Pinval);
				 if(Local_u8Pinval == PRESSED)
				 {
					 //_delay_ms(10);
					 *Copy_pu8KeyValue =Local_Au8KPDArr[Local_u8RowIdx][Local_u8ColIdx];
				*/	 /*Polling (busy waiting) until the key is released*/
/*					 while(Local_u8Pinval== PRESSED)
					 {
						 DIO_enuGetPinValue(Local_Au8RowPorts [Local_u8RowIdx] , Local_Au8RowPins [Local_u8RowIdx] , &Local_u8Pinval);
					 }
					 return Local_enuErrorState;

				 }
			 }
			 Local_enuErrorState = DIO_enuSetPinValue(Local_Au8RowPorts [Local_u8RowIdx] , Local_Au8RowPins [Local_u8RowIdx] , DIO_u8HIGH);
		 }
	}
	else
	{
		Local_enuErrorState =ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}
*/
