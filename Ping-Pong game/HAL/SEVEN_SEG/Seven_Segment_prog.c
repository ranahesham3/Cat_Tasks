/*
 * Seven_Segment_prog.c
 *
 *  Created on: Aug 24, 2023
 *      Author: DELL
 */
#include "stdTypes.h"
#include "errorState.h"

#include "DIO_init.h"

#include "Seven_Segment_config.h"
#include "Seven_Segment_priv.h"

extern SEG_t SEVSEG_AstrSegConfig[SEG_NUM];

ES_t Seven_Segment_enuInit(void)
{
	ES_t Local_enuErrorState =ES_OK;
	u8 Local_u8Iterator=0;

	for(Local_u8Iterator=0 ; Local_u8Iterator<SEG_NUM ; Local_u8Iterator++)
	{
		u32 Local_u32Check=0;
		Local_u32Check=(DIO_enuSetPinDirection(SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8APORT,SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8APIN,DIO_u8OUTPUT)<<0);
		Local_u32Check=(DIO_enuSetPinDirection(SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8BPORT,SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8BPIN,DIO_u8OUTPUT)<<3);
		Local_u32Check=(DIO_enuSetPinDirection(SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8CPORT,SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8CPIN,DIO_u8OUTPUT)<<6);
		Local_u32Check=(DIO_enuSetPinDirection(SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8DPORT,SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8DPIN,DIO_u8OUTPUT)<<9);
		Local_u32Check=(DIO_enuSetPinDirection(SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8EPORT,SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8EPIN,DIO_u8OUTPUT)<<12);
		Local_u32Check=(DIO_enuSetPinDirection(SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8FPORT,SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8FPIN,DIO_u8OUTPUT)<<15);
		Local_u32Check=(DIO_enuSetPinDirection(SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8GPORT,SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8GPIN,DIO_u8OUTPUT)<<18);

		if(Local_u32Check!=0b001001001001001001001 || Local_enuErrorState!=ES_OK)
		{
			Local_enuErrorState = ES_NOK;
		}
		if(SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8CMN_PORT != NOT_CONNECTED&&
			SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8CMN != NOT_CONNECTED	)
		{
			Local_enuErrorState=DIO_enuSetPinDirection(SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8CMN_PORT,SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8CMN,DIO_u8OUTPUT);
		}
		if(SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8DOT_PORT != NOT_CONNECTED&&
			SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8DOT != NOT_CONNECTED	)
		{
			Local_enuErrorState=DIO_enuSetPinDirection(SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8DOT_PORT,SEVSEG_AstrSegConfig[Local_u8Iterator].SEG_u8DOT,DIO_u8OUTPUT);
		}
	}


	return Local_enuErrorState;
}


ES_t Seven_Segment_enuDisplayNum(u8 Copy_u8DisplayNum, u8 Copy_u8SEGNum)
{
	ES_t Local_enuErrorState =ES_NOK;

	if(Copy_u8DisplayNum<10 && Copy_u8SEGNum<SEG_NUM)
	{
		if(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8TYPE ==COMMON_ANOD)
		{
			u32 Local_u32Check=0;
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8APORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8APIN,!((SEG_Au8NumDisplay[Copy_u8DisplayNum]>>0)&1))<<0);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8BPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8BPIN,!((SEG_Au8NumDisplay[Copy_u8DisplayNum]>>1)&1))<<3);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8CPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8CPIN,!((SEG_Au8NumDisplay[Copy_u8DisplayNum]>>2)&1))<<6);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8DPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8DPIN,!((SEG_Au8NumDisplay[Copy_u8DisplayNum]>>3)&1))<<9);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8EPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8EPIN,!((SEG_Au8NumDisplay[Copy_u8DisplayNum]>>4)&1))<<12);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8FPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8FPIN,!((SEG_Au8NumDisplay[Copy_u8DisplayNum]>>5)&1))<<15);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8GPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8GPIN,!((SEG_Au8NumDisplay[Copy_u8DisplayNum]>>6)&1))<<18);

			if(Local_u32Check == 0b001001001001001001001)
			{
				Local_enuErrorState =ES_OK;
			}
		}
		else if(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8TYPE ==COMMON_CATHOD)
		{
			u32 Local_u32Check=0;
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8APORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8APIN,((SEG_Au8NumDisplay[Copy_u8DisplayNum]>>0)&1))<<0);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8BPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8BPIN,((SEG_Au8NumDisplay[Copy_u8DisplayNum]>>1)&1))<<3);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8CPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8CPIN,((SEG_Au8NumDisplay[Copy_u8DisplayNum]>>2)&1))<<6);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8DPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8DPIN,((SEG_Au8NumDisplay[Copy_u8DisplayNum]>>3)&1))<<9);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8EPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8EPIN,((SEG_Au8NumDisplay[Copy_u8DisplayNum]>>4)&1))<<12);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8FPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8FPIN,((SEG_Au8NumDisplay[Copy_u8DisplayNum]>>5)&1))<<15);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8GPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8GPIN,((SEG_Au8NumDisplay[Copy_u8DisplayNum]>>6)&1))<<18);

			if(Local_u32Check == 0b001001001001001001001)
			{
				Local_enuErrorState =ES_OK;
			}
		}


	}
	else
	{
		Local_enuErrorState =ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}


ES_t Seven_Segment_enuEnableCommon(u8 Copy_u8SEGNum)
{
	ES_t Local_enuErrorState =ES_NOK;

	if(Copy_u8SEGNum<SEG_NUM)
	{
		if(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8CMN_PORT != NOT_CONNECTED&&
			SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8CMN != NOT_CONNECTED	)
		{
			if(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8TYPE ==COMMON_ANOD)
			{
				Local_enuErrorState=DIO_enuSetPinDirection(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8CMN_PORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8CMN,DIO_u8LOW);
			}
			else if(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8TYPE ==COMMON_CATHOD)
			{
				Local_enuErrorState=DIO_enuSetPinDirection(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8CMN_PORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8CMN,DIO_u8HIGH);
			}

		}
	}
	else
	{
		Local_enuErrorState =ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}


ES_t Seven_Segment_enuDisableCommon(u8 Copy_u8SEGNum)
{
	ES_t Local_enuErrorState =ES_NOK;

	if(Copy_u8SEGNum<SEG_NUM)
	{
		if(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8CMN_PORT != NOT_CONNECTED&&
			SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8CMN != NOT_CONNECTED	)
		{
			if(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8TYPE ==COMMON_ANOD)
			{
				Local_enuErrorState=DIO_enuSetPinDirection(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8CMN_PORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8CMN,DIO_u8HIGH);
			}
			else if(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8TYPE ==COMMON_CATHOD)
			{
				Local_enuErrorState=DIO_enuSetPinDirection(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8CMN_PORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8CMN,DIO_u8LOW);
			}

		}
	}
	else
	{
		Local_enuErrorState =ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}


ES_t Seven_Segment_enuEnableDot(u8 Copy_u8SEGNum)
{
	ES_t Local_enuErrorState =ES_NOK;

	if(Copy_u8SEGNum<SEG_NUM)
	{
		if(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8DOT_PORT != NOT_CONNECTED&&
			SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8DOT != NOT_CONNECTED	)
		{
			if(SEVSEG_AstrSegConfig[Copy_u8SEGNum].DOT_u8TYPE ==COMMON_ANOD)
			{
				Local_enuErrorState=DIO_enuSetPinDirection(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8DOT_PORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8DOT,DIO_u8LOW);
			}
			else if(SEVSEG_AstrSegConfig[Copy_u8SEGNum].DOT_u8TYPE ==COMMON_CATHOD)
			{
				Local_enuErrorState=DIO_enuSetPinDirection(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8DOT_PORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8DOT,DIO_u8HIGH);
			}

		}
	}
	else
	{
		Local_enuErrorState =ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}


ES_t Seven_Segment_enuDisableDot(u8 Copy_u8SEGNum)
{
	ES_t Local_enuErrorState =ES_NOK;

	if(Copy_u8SEGNum<SEG_NUM)
	{
		if(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8DOT_PORT != NOT_CONNECTED&&
			SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8DOT != NOT_CONNECTED	)
		{
			if(SEVSEG_AstrSegConfig[Copy_u8SEGNum].DOT_u8TYPE ==COMMON_ANOD)
			{
				Local_enuErrorState=DIO_enuSetPinDirection(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8DOT_PORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8DOT,DIO_u8HIGH);
			}
			else if(SEVSEG_AstrSegConfig[Copy_u8SEGNum].DOT_u8TYPE ==COMMON_CATHOD)
			{
				Local_enuErrorState=DIO_enuSetPinDirection(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8DOT_PORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8DOT,DIO_u8LOW);
			}

		}
	}
	else
	{
		Local_enuErrorState =ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}


ES_t Seven_Segment_enuClearDisplay(u8 Copy_u8SEGNum)
{
	ES_t Local_enuErrorState =ES_NOK;

	if(Copy_u8SEGNum<SEG_NUM)
	{
		if(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8TYPE ==COMMON_ANOD)
		{
			u32 Local_u32Check=0;
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8APORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8APIN,DIO_u8HIGH)<<0);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8BPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8BPIN,DIO_u8HIGH)<<3);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8CPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8CPIN,DIO_u8HIGH)<<6);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8DPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8DPIN,DIO_u8HIGH)<<9);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8EPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8EPIN,DIO_u8HIGH)<<12);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8FPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8FPIN,DIO_u8HIGH)<<15);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8GPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8GPIN,DIO_u8HIGH)<<18);

			if(Local_u32Check == 0b001001001001001001001)
			{
				Local_enuErrorState =ES_OK;
			}
		}
		else if(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8TYPE ==COMMON_CATHOD)
		{
			u32 Local_u32Check=0;
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8APORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8APIN,DIO_u8LOW)<<0);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8BPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8BPIN,DIO_u8LOW)<<3);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8CPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8CPIN,DIO_u8LOW)<<6);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8DPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8DPIN,DIO_u8LOW)<<9);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8EPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8EPIN,DIO_u8LOW)<<12);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8FPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8FPIN,DIO_u8LOW)<<15);
			Local_u32Check=(DIO_enuSetPinValue(SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8GPORT,SEVSEG_AstrSegConfig[Copy_u8SEGNum].SEG_u8GPIN,DIO_u8LOW)<<18);

			if(Local_u32Check == 0b001001001001001001001)
			{
				Local_enuErrorState =ES_OK;
			}
		}


	}
	else
	{
		Local_enuErrorState =ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}




