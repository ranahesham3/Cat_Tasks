/*
 * LED_prog.c
 *
 *  Created on: Aug 23, 2023
 *      Author: DELL
 */

#include "stdTypes.h"
#include "errorState.h"
#include "LED_priv.h"
#include "LED_config.h"
#include "DIO_init.h"


ES_t LED_enuInit(LED_t * Copy_pstrLedConfig)
{
	ES_t Local_enuErrorState =ES_NOK;
	if(Copy_pstrLedConfig != NULL)
	{
		u8 Local_u8Iterator=0;
		for(Local_u8Iterator=0 ; Local_u8Iterator<LED_NUM ; Local_u8Iterator++)
		{
			Local_enuErrorState=DIO_enuSetPinDirection(Copy_pstrLedConfig[Local_u8Iterator].LED_PortID,Copy_pstrLedConfig[Local_u8Iterator].LED_PinID,DIO_u8OUTPUT);
		}
		if(Copy_pstrLedConfig[Local_u8Iterator].LED_Connection == LED_SINK)
		{
			if(Copy_pstrLedConfig[Local_u8Iterator].LED_start == LED_ON)
			{
				Local_enuErrorState=DIO_enuSetPinValue(Copy_pstrLedConfig[Local_u8Iterator].LED_PortID,Copy_pstrLedConfig[Local_u8Iterator].LED_PinID,DIO_u8LOW);
			}
			else if(Copy_pstrLedConfig[Local_u8Iterator].LED_start == LED_OFF)
			{
				Local_enuErrorState=DIO_enuSetPinValue(Copy_pstrLedConfig[Local_u8Iterator].LED_PortID,Copy_pstrLedConfig[Local_u8Iterator].LED_PinID,DIO_u8HIGH);
			}
			else
			{
				Local_enuErrorState=ES_OUT_OF_RANGE;
			}
		}
		else if(Copy_pstrLedConfig[Local_u8Iterator].LED_Connection == LED_SOURC)
		{
			if(Copy_pstrLedConfig[Local_u8Iterator].LED_start == LED_ON)
			{
				Local_enuErrorState=DIO_enuSetPinValue(Copy_pstrLedConfig[Local_u8Iterator].LED_PortID,Copy_pstrLedConfig[Local_u8Iterator].LED_PinID,DIO_u8HIGH);
			}
			else if(Copy_pstrLedConfig[Local_u8Iterator].LED_start == LED_OFF)
			{
				Local_enuErrorState=DIO_enuSetPinValue(Copy_pstrLedConfig[Local_u8Iterator].LED_PortID,Copy_pstrLedConfig[Local_u8Iterator].LED_PinID,DIO_u8LOW);
			}
			else
			{
				Local_enuErrorState=ES_OUT_OF_RANGE;
			}
		}
		else
		{
			Local_enuErrorState=ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}
	return Local_enuErrorState;
}




ES_t LED_enuTurnON(LED_t * Copy_pstrLedID)
{
	ES_t Local_enuErrorState =ES_NOK;
	if(Copy_pstrLedID != NULL)
	{
		if(Copy_pstrLedID->LED_Connection == LED_SINK)
		{
			Local_enuErrorState = DIO_enuSetPinValue(Copy_pstrLedID->LED_PortID , Copy_pstrLedID->LED_PinID , DIO_u8LOW);
		}
		else if(Copy_pstrLedID->LED_Connection == LED_SOURC)
		{
			Local_enuErrorState = DIO_enuSetPinValue(Copy_pstrLedID->LED_PortID , Copy_pstrLedID->LED_PinID , DIO_u8HIGH);
		}
		else
		{
			Local_enuErrorState = ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}
	return Local_enuErrorState;
}


ES_t LED_enuTurnOFF(LED_t * Copy_pstrLedID)
{
	ES_t Local_enuErrorState =ES_NOK;
	if(Copy_pstrLedID != NULL)
	{
		if(Copy_pstrLedID->LED_Connection == LED_SINK)
		{
			Local_enuErrorState = DIO_enuSetPinValue(Copy_pstrLedID->LED_PortID , Copy_pstrLedID->LED_PinID , DIO_u8HIGH);
		}
		else if(Copy_pstrLedID->LED_Connection == LED_SOURC)
		{
			Local_enuErrorState = DIO_enuSetPinValue(Copy_pstrLedID->LED_PortID , Copy_pstrLedID->LED_PinID , DIO_u8LOW);
		}
		else
		{
			Local_enuErrorState = ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}
	return Local_enuErrorState;
}
