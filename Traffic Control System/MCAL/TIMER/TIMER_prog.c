/*
 * TIMER_prog.c
 *
 *  Created on: Feb 22, 2024
 *      Author: DELL
 */


#include "../../LIB/stdTypes.h"
#include "../../LIB/errorState.h"
#include "../../LIB/bit_math.h"
#include "../Interrupt.h"

#include "Timer_init.h"
#include "TIMER_priv.h"
#include "TIMER_config.h"

//=================================================================================================================

volatile static void (* TIMER_PfunOVF) (void*)=NULL;
volatile static void* TIMER_PfunOVFArg=NULL;

volatile static u32  TIMER0_u8NumberOfOverflow=0;
volatile static u8  TIMER0_u8Preload = 0;
volatile static u32 ISR_u32Counter=0;

//=================================================================================================================
ES_t TIMER_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	/* Clock Select used by the counter */
#if (TIMER_CLOCK_SELECT==TIMER_NO_CLOCK)
	CLEAR_BIT(TCCR0,TCCR0_CS00);
	CLEAR_BIT(TCCR0,TCCR0_CS01);
	CLEAR_BIT(TCCR0,TCCR0_CS10);

#elif (TIMER_CLOCK_SELECT==TIMER_NO_Prescaler)
	SET_BIT(TCCR0,TCCR0_CS00);
	CLEAR_BIT(TCCR0,TCCR0_CS01);
	CLEAR_BIT(TCCR0,TCCR0_CS10);

#elif (TIMER_CLOCK_SELECT==TIMER_Prescaler8)
	CLEAR_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLEAR_BIT(TCCR0,TCCR0_CS10);

#elif (TIMER_CLOCK_SELECT==TIMER_Prescaler64)
	SET_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLEAR_BIT(TCCR0,TCCR0_CS10);

#elif (TIMER_CLOCK_SELECT==TIMER_Prescaler256)
	CLEAR_BIT(TCCR0,TCCR0_CS00);
	CLEAR_BIT(TCCR0,TCCR0_CS01);
	SET_BIT(TCCR0,TCCR0_CS10);

#elif (TIMER_CLOCK_SELECT==TIMER_Prescaler1024)
	SET_BIT(TCCR0,TCCR0_CS00);
	CLEAR_BIT(TCCR0,TCCR0_CS01);
	SET_BIT(TCCR0,TCCR0_CS10);

#elif (TIMER_CLOCK_SELECT==TIMER_EXTERNAL_CLOCK_SOURCE_FALING)
	CLEAR_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	SET_BIT(TCCR0,TCCR0_CS10);

#elif (TIMER_CLOCK_SELECT==TIMER_EXTERNAL_CLOCK_SOURCE_RISING)
	CLEAR_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	SET_BIT(TCCR0,TCCR0_CS10);

#else
#error " Attention!!, Wrong Timer Clock Selection.... "

#endif



	/* Waveform Generation Mode */
#if (WAVEFORM_GENERATION_MODE == TIMER0_NORMAL_MODE)
	CLEAR_BIT(TCCR0,TCCR0_WGM00);
	CLEAR_BIT(TCCR0,TCCR0_WGM01);
#if (COMPARE_MATCH_OUTPUT_MODE == OC0_DISCONNECTED )
	CLEAR_BIT(TCCR0,TCCR0_COM00);
	CLEAR_BIT(TCCR0,TCCR0_COM01);

#else
#error"Attention!!, you must disable OC0_PIN at overflow MODE...."

#endif

#elif (WAVEFORM_GENERATION_MODE == TIMER0_PHASE_CORRECT_PWM_MODE)
	SET_BIT(TCCR0,TCCR0_WGM00);
	CLEAR_BIT(TCCR0,TCCR0_WGM01);
#if (COMPARE_MATCH_OUTPUT_MODE == OC0_DISCONNECTED )
	CLEAR_BIT(TCCR0,TCCR0_COM00);
	CLEAR_BIT(TCCR0,TCCR0_COM01);

#elif (COMPARE_MATCH_OUTPUT_MODE == OC0_NON_INVERTING_MODE)
	CLEAR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

#elif (COMPARE_MATCH_OUTPUT_MODE == OC0_INVERTING_MODE)
	SET_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

#else
#error"Attention!!, wrong OC0_PIN selection...."

#endif

#elif (WAVEFORM_GENERATION_MODE == TIMER0_CTC_MODE)
	CLEAR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
#if (COMPARE_MATCH_OUTPUT_MODE == OC0_DISCONNECTED )
	CLEAR_BIT(TCCR0,TCCR0_COM00);
	CLEAR_BIT(TCCR0,TCCR0_COM01);

#elif (COMPARE_MATCH_OUTPUT_MODE == OC0_TOGGLE)
	SET_BIT(TCCR0,TCCR0_COM00);
	CLEAR_BIT(TCCR0,TCCR0_COM01);
#elif (COMPARE_MATCH_OUTPUT_MODE == OC0_CLEAR)
	CLEAR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

#elif (COMPARE_MATCH_OUTPUT_MODE == OC0_SET)
	SET_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

#else
#error"Attention!!, wrong OC0_PIN selection...."

#endif

#elif (WAVEFORM_GENERATION_MODE == TIMER0_FAST_PWM_MODE)
	SET_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
#if (COMPARE_MATCH_OUTPUT_MODE == OC0_DISCONNECTED )
	CLEAR_BIT(TCCR0,TCCR0_COM00);
	CLEAR_BIT(TCCR0,TCCR0_COM01);

#elif (COMPARE_MATCH_OUTPUT_MODE == OC0_NON_INVERTING_MODE)
	CLEAR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

#elif (COMPARE_MATCH_OUTPUT_MODE == OC0_INVERTING_MODE)
	SET_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

#else
#error"Attention!!, wrong OC0_PIN selection...."

#endif

#else
#error " Attention!!, Wrong Waveform Generation Mode Selection.... "

#endif


	/* Clear Force Output Compare (FOC0_PIN) */
	CLEAR_BIT(TCCR0,TCCR0_FOC0);

	Local_enuErrorState=ES_OK;
	return Local_enuErrorState;
}



ES_t TIMER0_enuDelayMilliSecondSynch(u32 Copy_u32Time )
{
	ES_t Local_enuErrorState = ES_NOK;

#if ((TIMER_CLOCK_SELECT == TIMER_NO_Prescaler || TIMER_CLOCK_SELECT == TIMER_Prescaler8 || TIMER_CLOCK_SELECT == TIMER_Prescaler64 || TIMER_CLOCK_SELECT == TIMER_Prescaler256 || TIMER_CLOCK_SELECT == TIMER_Prescaler1024)&&WAVEFORM_GENERATION_MODE == TIMER0_NORMAL_MODE)
	/* Setting and Calculating Desired Time */
	f32 Local_f32OVFTime=TIMER0_OVF_COUNTS*((f32)TIMER_CLOCK_SELECT/TIMER0_F_CPU);
	f32 Local_f32NumOfOVF=Copy_u32Time/Local_f32OVFTime;
	if ((Local_f32NumOfOVF - ((u32)Local_f32NumOfOVF)) > 0 )
	{
		TCNT0=(Local_f32NumOfOVF - ((u32)Local_f32NumOfOVF))*Local_f32OVFTime;
		u8 Local_u8NumberOfOverflow=(u32)Local_f32NumOfOVF+1;

		while(Local_u8NumberOfOverflow--)
		{
			/* Checking if the flag is fired */
			while(CHECK_BIT(TIFR,TIFR_TOV0)==0);
			/* Clearing the flag */
			SET_BIT(TIFR,TIFR_TOV0);
		}
	}
	else
	{
		u8 Local_u8NumberOfOverflow=(u32)Local_f32NumOfOVF;
		while(Local_u8NumberOfOverflow--)
		{
			/* Checking if the flag is fired */
			while(CHECK_BIT(TIFR,TIFR_TOV0)==0);
			/* Clearing the flag */
			SET_BIT(TIFR,TIFR_TOV0);
		}
	}
#elif ((TIMER_CLOCK_SELECT == TIMER_NO_Prescaler || TIMER_CLOCK_SELECT == TIMER_Prescaler8 || TIMER_CLOCK_SELECT == TIMER_Prescaler64 || TIMER_CLOCK_SELECT == TIMER_Prescaler256 || TIMER_CLOCK_SELECT == TIMER_Prescaler1024)&&WAVEFORM_GENERATION_MODE == TIMER0_CTC_MODE)
	/* Setting and Calculating Desired Time */
	f32 Local_f32OVFTime=TIMER0_OVF_COUNTS*((f32)TIMER_CLOCK_SELECT/TIMER0_F_CPU);
	TIMER0_u8Preload =(Copy_u32Time/Local_f32OVFTime)*Local_f32OVFTime;
	OCR0=TIMER0_u8Preload;
	/* Checking if the flag is fired */
	while(CHECK_BIT(TIFR,TIFR_OCF0)==0);
	/* Clearing the flag */
	SET_BIT(TIFR,TIFR_OCF0);


#endif

	Local_enuErrorState=ES_OK;
	return Local_enuErrorState;

}



ES_t TIMER0_enuDelayMilliSecondAsynch(u32 Copy_u32Time , void (*Copy_PfunCallBack)(void*) , void * Copy_PvidArg)
{
	ES_t Local_enuErrorState = ES_NOK;

#if ((TIMER_CLOCK_SELECT == TIMER_NO_Prescaler || TIMER_CLOCK_SELECT == TIMER_Prescaler8 || TIMER_CLOCK_SELECT == TIMER_Prescaler64 || TIMER_CLOCK_SELECT == TIMER_Prescaler256 || TIMER_CLOCK_SELECT == TIMER_Prescaler1024)&&WAVEFORM_GENERATION_MODE == TIMER0_NORMAL_MODE)
	/* Setting and Calculating Desired Time */
	f32 Local_f32OVFTime=TIMER0_OVF_COUNTS*((f32)TIMER_CLOCK_SELECT/TIMER0_F_CPU);
	f32 Local_f32NumOfOVF=Copy_u32Time/Local_f32OVFTime;
	if ((Local_f32NumOfOVF - ((u32)Local_f32NumOfOVF)) > 0 )
	{
		TIMER0_u8Preload =(Local_f32NumOfOVF - ((u32)Local_f32NumOfOVF))*Local_f32OVFTime;
		TCNT0=TIMER0_u8Preload;
		TIMER_PfunOVF=Copy_PfunCallBack;
		TIMER_PfunOVFArg=Copy_PvidArg;
		TIMER0_u8NumberOfOverflow=(u32)Local_f32NumOfOVF+1;
		ISR_u32Counter=0;
	}
	else
	{
		TIMER_PfunOVF=Copy_PfunCallBack;
		TIMER_PfunOVFArg=Copy_PvidArg;
		TIMER0_u8NumberOfOverflow=1;
		ISR_u32Counter=0;
	}
	/* Enabling OverFlow Interrupt (TOIE0 bit) */
	SET_BIT(TIMSK,TIMSK_TOIE0);


#elif ((TIMER_CLOCK_SELECT == TIMER_NO_Prescaler || TIMER_CLOCK_SELECT == TIMER_Prescaler8 || TIMER_CLOCK_SELECT == TIMER_Prescaler64 || TIMER_CLOCK_SELECT == TIMER_Prescaler256 || TIMER_CLOCK_SELECT == TIMER_Prescaler1024)&&WAVEFORM_GENERATION_MODE == TIMER0_CTC_MODE)
	/* Setting and Calculating Desired Time */
	f32 Local_f32OVFTime=TIMER0_OVF_COUNTS*((f32)TIMER_CLOCK_SELECT/TIMER0_F_CPU);
	TIMER0_u8Preload =(Copy_u32Time/Local_f32OVFTime)*Local_f32OVFTime;
	OCR0=TIMER0_u8Preload;
	TIMER_PfunOVF=Copy_PfunCallBack;
	TIMER_PfunOVFArg=Copy_PvidArg;
	/* Enabling Compare Match Interrupt (OCIE0 bit) */
	SET_BIT(TIMSK,TIMSK_OCIE0);


#endif

	Local_enuErrorState=ES_OK;
	return Local_enuErrorState;

}


ES_t TIMER0_enuGeneratePWM(u8 Copy_u8DutyCycle)
{
	ES_t Local_enuErrorState=ES_NOK;
#if(WAVEFORM_GENERATION_MODE ==TIMER0_FAST_PWM_MODE)
	if((Copy_u8DutyCycle>0)||(Copy_u8DutyCycle<100))
	{
#if (COMPARE_MATCH_OUTPUT_MODE == OC0_NON_INVERTING_MODE)
	f32 Local_f32OVFTime=TIMER0_OVF_COUNTS*((f32)TIMER_CLOCK_SELECT/TIMER0_F_CPU);
	OCR0=(Copy_u8DutyCycle*TIMER0_OVF_COUNTS/TIMER0_PERCENTAGE_RATIO);

#elif (COMPARE_MATCH_OUTPUT_MODE == OC0_INVERTING_MODE)
	f32 Local_f32OVFTime=TIMER0_OVF_COUNTS*((f32)TIMER_CLOCK_SELECT/TIMER0_F_CPU);
	OCR0=Local_f32OVFTime-(Copy_u8DutyCycle*TIMER0_OVF_COUNTS/TIMER0_PERCENTAGE_RATIO);

#endif
	Local_enuErrorState=ES_OK;
	}
	else
	{
		Local_enuErrorState=ES_OUT_OF_RANGE;
	}

#elif(WAVEFORM_GENERATION_MODE ==TIMER0_PHASE_CORRECT_PWM_MODE)
	if((Copy_u8DutyCycle>0)||(Copy_u8DutyCycle<100))
	{
#if (COMPARE_MATCH_OUTPUT_MODE ==CLEAR_UP_COUNTING_SET_DOWN_COUNTING_OC0)
	f32 Local_f32OVFTime=TIMER0_OVF_COUNTS*((f32)TIMER_CLOCK_SELECT/TIMER0_F_CPU);
	OCR0=(Copy_u8DutyCycle*TIMER0_OVF_COUNTS/TIMER0_PERCENTAGE_RATIO);
#elif (COMPARE_MATCH_OUTPUT_MODE ==SET_UP_COUNTING_CLEAR_DOWN_COUNTING_OC0)
	f32 Local_f32OVFTime=TIMER0_OVF_COUNTS*((f32)TIMER_CLOCK_SELECT/TIMER0_F_CPU);
	OCR0=Local_f32OVFTime-(Copy_u8DutyCycle*TIMER0_OVF_COUNTS/TIMER0_PERCENTAGE_RATIO);
#endif
	Local_enuErrorState=ES_OK;
	}
	else
	{
		Local_enuErrorState=ES_OUT_OF_RANGE;
	}

#endif
	return Local_enuErrorState;
}




ISR(VECT_TIMER0_OVF)
{
	if((TIMER_PfunOVF != NULL))
	{
		ISR_u32Counter++;

		if(ISR_u32Counter==TIMER0_u8NumberOfOverflow)
		{
			TIMER_PfunOVF(TIMER_PfunOVFArg);
		}
	}
}


ISR(VECT_TIMER0_COMP)
{
	if((TIMER_PfunOVF != NULL))
	{
		TIMER_PfunOVF(TIMER_PfunOVFArg);
	}
}













