/*
 * EXTI_prog.c
 *
 *  Created on: Aug 30, 2023
 *      Author: DELL
 */


#include "stdTypes.h"
#include "errorState.h"
#include "bit_math.h"

#include "DIO_init.h"
#include "GIE.h"
#include "Interrupt.h"

#include "EXTI_config.h"
#include "EXTI_priv.h"

static void (* EXTI_PtrArrFunc[3]) (void)={NULL , NULL , NULL};


extern EXTI_t EXTI_AstrEXTIConfig [3];

ES_t EXTI_enuInit(void)
{
	ES_t Local_enuErrorState =ES_NOK;

	u8 Local_u8Iterator;
	for(Local_u8Iterator=0 ; Local_u8Iterator<PINS_NUM ; Local_u8Iterator++)
	{
		if(EXTI_AstrEXTIConfig[Local_u8Iterator].EXTI_u8State == ACTIVE)
		{
			switch(Local_u8Iterator)
			{
			case INT0:
				SET_BIT(GICR,GICR_INT0);
				switch(EXTI_AstrEXTIConfig[Local_u8Iterator].EXTI_u8State)
				{
				case LOW_LEVEL:
					CLEAR_BIT(MCUCR,MCUCR_ISC00);
					CLEAR_BIT(MCUCR,MCUCR_ISC01);
					break;
				case LOGICAL_CHANGE:
					SET_BIT(MCUCR,MCUCR_ISC00);
					CLEAR_BIT(MCUCR,MCUCR_ISC01);
					break;
				case FALLING_EDGE:
					CLEAR_BIT(MCUCR,MCUCR_ISC00);
					SET_BIT(MCUCR,MCUCR_ISC01);
					break;
				case RISING_EDGE:
					SET_BIT(MCUCR,MCUCR_ISC00);
					SET_BIT(MCUCR,MCUCR_ISC01);
					break;
				default:
					Local_enuErrorState =ES_OUT_OF_RANGE;
				}
				break;

			case INT1:
				SET_BIT(GICR,GICR_INT1);
				switch(EXTI_AstrEXTIConfig[Local_u8Iterator].EXTI_u8State)
				{
				case LOW_LEVEL:
					CLEAR_BIT(MCUCR,MCUCR_ISC10);
					CLEAR_BIT(MCUCR,MCUCR_ISC11);
					break;
				case LOGICAL_CHANGE:
					SET_BIT(MCUCR,MCUCR_ISC10);
					CLEAR_BIT(MCUCR,MCUCR_ISC11);
					break;
				case FALLING_EDGE:
					CLEAR_BIT(MCUCR,MCUCR_ISC10);
					SET_BIT(MCUCR,MCUCR_ISC11);
					break;
				case RISING_EDGE:
					SET_BIT(MCUCR,MCUCR_ISC10);
					SET_BIT(MCUCR,MCUCR_ISC11);
					break;
				default:
					Local_enuErrorState =ES_OUT_OF_RANGE;
				}
				break;

			case INT2:
				SET_BIT(GICR,GICR_INT2);
				switch(EXTI_AstrEXTIConfig[Local_u8Iterator].EXTI_u8State)
				{
				case FALLING_EDGE :
					CLEAR_BIT(MCUCSR ,MCUCSR_ISC2);
					break;

				case RISING_EDGE:
					SET_BIT(MCUCSR ,MCUCSR_ISC2);
					break;
				default:
					Local_enuErrorState=ES_OUT_OF_RANGE;
				}
				break;

			default:
				Local_enuErrorState=ES_OUT_OF_RANGE;

			}
		}
	}


	return Local_enuErrorState;
}



ES_t EXTI_enuSetSenceMode(u8 Copy_u8EXTI_ID , u8 Copy_u8SenseLevel)
{
	ES_t Local_enuErrorState =ES_NOK;
	switch(Copy_u8EXTI_ID)
	{
	case INT0:
		switch(Copy_u8SenseLevel)
		{
		case LOW_LEVEL:
			CLEAR_BIT(MCUCR,MCUCR_ISC00);
			CLEAR_BIT(MCUCR,MCUCR_ISC01);
			Local_enuErrorState =ES_OK;
			break;
		case LOGICAL_CHANGE:
			SET_BIT(MCUCR,MCUCR_ISC00);
			CLEAR_BIT(MCUCR,MCUCR_ISC01);
			Local_enuErrorState =ES_OK;
			break;
		case FALLING_EDGE:
			CLEAR_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);
			Local_enuErrorState =ES_OK;
			break;
		case RISING_EDGE:
			SET_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);
			Local_enuErrorState =ES_OK;
			break;
		default:
			Local_enuErrorState =ES_OUT_OF_RANGE;
		}
		break;

	case INT1:
		switch(Copy_u8SenseLevel)
		{
		case LOW_LEVEL:
			CLEAR_BIT(MCUCR,MCUCR_ISC10);
			CLEAR_BIT(MCUCR,MCUCR_ISC11);
			Local_enuErrorState =ES_OK;
			break;
		case LOGICAL_CHANGE:
			SET_BIT(MCUCR,MCUCR_ISC10);
			CLEAR_BIT(MCUCR,MCUCR_ISC11);
			Local_enuErrorState =ES_OK;
			break;
		case FALLING_EDGE:
			CLEAR_BIT(MCUCR,MCUCR_ISC10);
			SET_BIT(MCUCR,MCUCR_ISC11);
			Local_enuErrorState =ES_OK;
			break;
		case RISING_EDGE:
			SET_BIT(MCUCR,MCUCR_ISC10);
			SET_BIT(MCUCR,MCUCR_ISC11);
			Local_enuErrorState =ES_OK;
			break;
		default:
			Local_enuErrorState =ES_OUT_OF_RANGE;
		}
		break;

	case INT2:
		switch(Copy_u8SenseLevel)
		{
		case FALLING_EDGE :
			CLEAR_BIT(MCUCSR ,MCUCSR_ISC2);
			Local_enuErrorState =ES_OK;
			break;

		case RISING_EDGE:
			SET_BIT(MCUCSR ,MCUCSR_ISC2);
			Local_enuErrorState =ES_OK;
			break;
		default:
			Local_enuErrorState=ES_OUT_OF_RANGE;
		}
		break;

	default:
		Local_enuErrorState=ES_OUT_OF_RANGE;

	}


	return Local_enuErrorState;
}


ES_t EXTI_enuEnableINT(u8 Copy_u8EXTI_ID)
{
	ES_t Local_enuErrorState =ES_OK;

	switch(Copy_u8EXTI_ID)
	{
	case INT0:
		SET_BIT(GICR,GICR_INT0);
		break;

	case INT1:
		SET_BIT(GICR,GICR_INT1);
		break;

	case INT2:
		SET_BIT(GICR,GICR_INT2);
		break;

	default:
		Local_enuErrorState=ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}

ES_t EXTI_enuDisableINT(u8 Copy_u8EXTI_ID)
{
	ES_t Local_enuErrorState =ES_OK;

	switch(Copy_u8EXTI_ID)
	{
	case INT0:
		CLEAR_BIT(GICR,GICR_INT0);
		break;

	case INT1:
		CLEAR_BIT(GICR,GICR_INT1);
		break;

	case INT2:
		CLEAR_BIT(GICR,GICR_INT2);
		break;

	default:
		Local_enuErrorState=ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}




ES_t EXTI_enuCallBack(u8 Copy_u8EXTI_ID , void (*Copy_PtrFunc)(void))
{
	ES_t Local_enuErrorState =ES_OK;

	if(Copy_PtrFunc !=NULL)
	{
		switch(Copy_u8EXTI_ID)
		{
		case INT0:
			EXTI_PtrArrFunc[0]=Copy_PtrFunc;
			break;

		case INT1:
			EXTI_PtrArrFunc[1]=Copy_PtrFunc;
			break;

		case INT2:
			EXTI_PtrArrFunc[2]=Copy_PtrFunc;
			break;

		default:
			Local_enuErrorState=ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}






ISR(VECT_INT0)
{
	if(EXTI_PtrArrFunc[0] !=NULL)
	{
		EXTI_PtrArrFunc[0]();
	}
}


ISR(VECT_INT1)
{
	if(EXTI_PtrArrFunc[1] !=NULL)
	{
		EXTI_PtrArrFunc[1]();
	}
}


ISR(VECT_INT2)
{
	if(EXTI_PtrArrFunc[2] !=NULL)
	{
		EXTI_PtrArrFunc[2]();
	}
}
