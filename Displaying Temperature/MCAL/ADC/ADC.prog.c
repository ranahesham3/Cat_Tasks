/*
 * ADC.prog.c
 *
 *  Created on: Sep 18, 2023
 *      Author: DELL
 */

#include "../../LIB/stdTypes.h"
#include "../../LIB/errorState.h"
#include "../../LIB/bit_math.h"
#include "../Interrupt.h"

#include "ADC_init.h"
#include "ADC_priv.h"
#include "ADC_config.h"


/*=======================================================================================================================================================*/

//static to be visible only in this file

//Global pointer to carry the Conversion result in Asynchronous function execution
static u16* ADC_pu16Reading = NULL;

//Global pointer to carry the Notification Function( which is called by ISR ) in Asynchronous function execution
static void (* ADC_pvCallBackNotificationFunction)(void *) ;

//Global pointer to carry the Notification Function Argument ( which is called by ISR ) in Asynchronous function execution
static void* ADC_pvFunctionArgument = NULL;

//Global Flag to know if the ADC function is busy or not
static u8 ADC_u8BusyState =IDLE;

//Global pointer to carry the  chain channel
static u8* ADC_pu8ChainChannel = NULL;

//Global variable to carry the  chain size
static u8 ADC_u8ChainSize ;

//Global variable to indicate which channel in the chain is currently being converted
static u8 ADC_u8ChainID ;

//Global variable to indicate if it is a single channel or chain channel in ISR
static u8 ADC_u8ISRState;


//=======================================================================================================================================================


ES_t ADC_enuInit (void)

{
	ES_t Local_enuErrorState = ES_NOK;

	/* ADC Reference Selection */
#if (ADC_REFRENCE_SELECTION ==ADC_AREF)
	CLEAR_BIT(ADMUX,ADMUX_REFS0);
	CLEAR_BIT(ADMUX,ADMUX_REFS1);

#elif (ADC_REFRENCE_SELECTION ==ADC_AVCC)
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLEAR_BIT(ADMUX,ADMUX_REFS1);

#elif (ADC_REFRENCE_SELECTION ==ADC_INTERNL_REF)
	SET_BIT(ADMUX,ADMUX_REFS0);
	SET_BIT(ADMUX,ADMUX_REFS1);

#else
#error"WRONG ADC_REFRENCE_SELECTION"

#endif


	/* ADC Left Adjust Result */
#if (ADC_RESOLUTION ==ADC_8BIT_RESOLUTION)
	SET_BIT(ADMUX,ADMUX_ADLAR);

#elif (ADC_RESOLUTION ==ADC_10BIT_RESOLUTION)
	CLEAR_BIT(ADMUX,ADMUX_ADLAR);

#else
#error"WRONG ADC RESOLUTION SELECTION"

#endif


	/* ADC_PRESCALER_SELECTION */
#if (ADC_PRESCALER_SELECTION == Division_Factor_2)
	CLEAR_BITS_REG(ADCSRA,Prescaller_Masking);				//clear prescaller bits in ADCSRA register
	SET_BITS_REG(ADCSRA,Division_Factor_2);				//set the required bits according to your choice

#elif (ADC_PRESCALER_SELECTION == Division_Factor_4)
	CLEAR_BITS_REG(ADCSRA,Prescaller_Masking);
	SET_BITS_REG(ADCSRA,Division_Factor_4);

#elif (ADC_PRESCALER_SELECTION == Division_Factor_8)
	CLEAR_BITS_REG(ADCSRA,Prescaller_Masking);
	SET_BITS_REG(ADCSRA,Division_Factor_8);

#elif (ADC_PRESCALER_SELECTION == Division_Factor_16)
	CLEAR_BITS_REG(ADCSRA,Prescaller_Masking);
	SET_BITS_REG(ADCSRA,Division_Factor_16);

#elif (ADC_PRESCALER_SELECTION == Division_Factor_32)
	CLEAR_BITS_REG(ADCSRA,Prescaller_Masking);
	SET_BITS_REG(ADCSRA,Division_Factor_32);

#elif (ADC_PRESCALER_SELECTION == Division_Factor_64)
	CLEAR_BITS_REG(ADCSRA,Prescaller_Masking);
	SET_BITS_REG(ADCSRA,Division_Factor_64);

#elif (ADC_PRESCALER_SELECTION == Division_Factor_128)
	CLEAR_BITS_REG(ADCSRA,Prescaller_Masking);
	SET_BITS_REG(ADCSRA,Division_Factor_128);

#else
#error"WRONG ADC PRESCALLER SELECTION"

#endif


	/* ADC ENABLE */
#if (ADC_INITIAL_STATE == ADC_ENABLE)
	SET_BIT(ADCSRA,ADCSRA_ADEN);

#elif (ADC_INITIAL_STATE == ADC_DISABLE)
	CLEAR_BIT(ADCSRA,ADCSRA_ADEN);

#else
#error"WRONG ADC ENABLE SELECTION"

#endif

	Local_enuErrorState =ES_OK;

	return Local_enuErrorState;
}


//=====================================================================================================================================================


ES_t ADC_enuStartConversionSync (u8 Copy_u8Channel , u16* Copy_pu16Value)
{
	ES_t Local_enuErrorState =ES_NOK;

	if(ADC_u8BusyState==IDLE)
	{
		if(Copy_pu16Value != NULL)
		{
			if(Copy_u8Channel <= GND)
			{
				u32 Local_u32Counter=0;

				/* update Busy state (making it busy in order not to work until being idle again) */
				ADC_u8BusyState=BUSY;

				/* ADC_CHANNEL_SELLECTION */
				CLEAR_BITS_REG(ADMUX,channel_Masking); 				//clear channel selection bits in ADCSRA register
				SET_BITS_REG(ADMUX,Copy_u8Channel);					//set the required bits according to your choice


				/* ADC Start Conversion */
				SET_BIT(ADCSRA,ADCSRA_ADSC);


				/* Polling (busy waiting) until the flag is set or counter reaching timeout value*/
				//The ADCSRA_ADIF bit is set when an ADC conversion completes and the Data Registers are updated.
				while((CHECK_BIT(ADCSRA,ADCSRA_ADIF)==0)&&(++Local_u32Counter<ADC_U32TIMEOUT));


				if(Local_u32Counter!=ADC_U32TIMEOUT)
				{
					//super loop is broken because of Flag(ADCSRA_ADIF) is raised

					/* Clear Conversion Complete Flag (ADCSRA_ADIF) */
					//ADIF is cleared by hardware when executing the ISR ;in Synchronous Conversion ISR won't be executed so we clear it by S.W.
					SET_BIT(ADCSRA,ADCSRA_ADIF);


					/* returning the ADC result */
					if(ADC_RESOLUTION ==ADC_10BIT_RESOLUTION)
					{
						*Copy_pu16Value=(u16*)ADC_U16;
					}
					else
					{
						*Copy_pu16Value=(u16*)ADCH;
					}

					Local_enuErrorState =ES_OK;
				}
				else
				{
					//super loop is broken because of timeout
					Local_enuErrorState =ES_TIMEOUT;
				}
				/* update Busy state */
				ADC_u8BusyState=IDLE;

			}
			else
			{
				Local_enuErrorState = ES_OUT_OF_RANGE;
			}
		}
		else
		{
			Local_enuErrorState = ES_NULL_POINTER;
		}
	}
	else
	{
		Local_enuErrorState=ES_BUSY_FUNC;
	}
	return Local_enuErrorState;
}


//======================================================================================================================================================


ES_t ADC_enuStartConversionAsync (u8 Copy_u8Channel , u16* Copy_pu16Value, volatile void (*Copy_vNotificationFunction)(void*) , volatile void* Copy_pvArgument )
{
	ES_t Local_enuErrorState =ES_NOK;

	if(ADC_u8BusyState==IDLE)
	{
		if(Copy_pu16Value != NULL && Copy_vNotificationFunction != NULL)
		{
			if(Copy_u8Channel <= GND)
			{
				/* update Busy state (making it busy in order not to work until being idle again) */
				ADC_u8BusyState=BUSY;


				/* ADC_CHANNEL_SELLECTION */
				CLEAR_BITS_REG(ADMUX,channel_Masking); 				//clear channel selection bits in ADCSRA register
				SET_BITS_REG(ADMUX,Copy_u8Channel);					//set the required bits according to your choice


				/* ADC Start Conversion */
				SET_BIT(ADCSRA,ADCSRA_ADSC);


				/* Assign the Reading variable & Callback function & Callback function argument globally */
				ADC_pu16Reading=Copy_pu16Value;
				ADC_pvCallBackNotificationFunction=Copy_vNotificationFunction;
				ADC_pvFunctionArgument=Copy_pvArgument;


				/* Enable ADC Conversion Complete Interrupt */
				SET_BIT(ADCSRA,ADCSRA_ADIE);
			}
			else
			{
				Local_enuErrorState = ES_OUT_OF_RANGE;
			}
		}
		else
		{
			Local_enuErrorState = ES_NULL_POINTER;
		}
	}
	else
	{
		Local_enuErrorState=ES_BUSY_FUNC;
	}
	return Local_enuErrorState;
}


//=======================================================================================================================================================


ES_t ADC_enuStartChainConversionAsync(ADC_Chain_t* Copy_pstChain)
{
	ES_t Local_enuErrorState =ES_NOK;

	if(ADC_u8BusyState==IDLE)
	{
		if(Copy_pstChain != NULL)
		{
			if(Copy_pstChain->Chain_Channel !=NULL && Copy_pstChain->Conversions_Res !=NULL &&
					Copy_pstChain->Func_Argument !=NULL && Copy_pstChain->Notificaton_func !=NULL)
			{
				/* update Busy state (making it busy in order not to work until being idle again) */
				ADC_u8BusyState=BUSY;


				//assign the ID /index of chain channel the ISR 'll start with
				ADC_u8ChainID=0;


				/* ADC_CHANNEL_SELLECTION */
				CLEAR_BITS_REG(ADMUX,channel_Masking); 				//clear channel selection bits in ADCSRA register
				SET_BITS_REG(ADMUX,* Copy_pstChain->Chain_Channel);					//set the required bits according to your choice


				/* ADC Start Conversion */
				SET_BIT(ADCSRA,ADCSRA_ADSC);


				//Assign he data globally
				ADC_pu16Reading = Copy_pstChain->Conversions_Res;
				ADC_pu8ChainChannel = Copy_pstChain->Chain_Channel;
				ADC_pvCallBackNotificationFunction = Copy_pstChain->Notificaton_func;
				ADC_pvFunctionArgument = Copy_pstChain->Func_Argument;
				ADC_u8ChainSize = Copy_pstChain->Chain_size;


				//updating the ISR state
				ADC_u8ISRState=ADC_CHAIN_CHANNEL_ASYNCH;

				/* Enable ADC Conversion Complete Interrupt */
				SET_BIT(ADCSRA,ADCSRA_ADIE);

				Local_enuErrorState=ES_OK;

			}
			else
			{
				Local_enuErrorState = ES_NULL_POINTER;
			}

		}
		else
		{
			Local_enuErrorState = ES_NULL_POINTER;
		}
	}
	else
	{
		Local_enuErrorState=ES_BUSY_FUNC;
	}

	return Local_enuErrorState;
}


//=======================================================================================================================================================


ISR(VECT_ADC)
{
	if(ADC_u8ISRState==ADC_SINGLE_CHANNEL_ASYNCH)
	{
		if((ADC_pu16Reading != NULL) && (ADC_pvCallBackNotificationFunction != NULL))
		{
			/* reading the ADC result */
#if(ADC_RESOLUTION ==ADC_10BIT_RESOLUTION)
			*ADC_pu16Reading=(u16*)ADC_U16;

#elif(ADC_RESOLUTION ==ADC_8BIT_RESOLUTION)
			*ADC_pu16Reading=(u16*)ADCH;

#else
#error"WRONG ADC ADJUSTMENT SELECTION"

#endif

			/* update Busy state (because it finished converting & updating the ADC registers)*/
			ADC_u8BusyState=IDLE;

			/* Invoke/Call the callback notification function */
			ADC_pvCallBackNotificationFunction(ADC_pvFunctionArgument);


			/* Disable ADC Conversion Complete Interrupt */
			CLEAR_BIT(ADCSRA,ADCSRA_ADIE);
		}
	}
	else
	{
		/* reading the ADC result */
#if(ADC_RESOLUTION ==ADC_10BIT_RESOLUTION)
		ADC_pu16Reading[ADC_u8ChainID]= (u16*)ADC_U16;

#elif(ADC_RESOLUTION ==ADC_8BIT_RESOLUTION)
		ADC_pu16Reading[ADC_u8ChainID] = (u16*) ADCH;

#else
#error"WRONG ADC ADJUSTMENT SELECTION"

#endif

		//updating the index/ID
		ADC_u8ChainID++;


		if(ADC_u8ChainID==ADC_u8ChainSize)
		{
			/* update Busy state (because it finished converting & updating the ADC registers)*/
			ADC_u8BusyState=IDLE;

			/* Invoke/Call the callback notification function */
			ADC_pvCallBackNotificationFunction(ADC_pvFunctionArgument);


			/* Disable ADC Conversion Complete Interrupt */
			CLEAR_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			/* ADC_CHANNEL_SELLECTION for next conversion */
			CLEAR_BITS_REG(ADMUX,channel_Masking); 							//clear chain channel bits in ADCSRA register
			SET_BITS_REG(ADMUX, ADC_pu8ChainChannel[ADC_u8ChainID]);     	//set the required bits according to your choice


			/* ADC Start Conversion */
			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}
	}
}


