/*
 * LM35_prog.c
 *
 *  Created on: Feb 16, 2024
 *      Author: DELL
 */


#include "stdTypes.h"
#include "errorState.h"
#include "bit_math.h"


#include "LM35_priv.h"
#include "LM35_config.h"
#include "LM35_init.h"

#include "DIO_init.h"
#include "ADC_init.h"

//=============================================================================================



ES_t LM35_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	Local_enuErrorState=DIO_enuSetPinDirection(DIO_u8PORTA,POSITIVE_PIN,DIO_u8INPUT);
#if(NEGATIVE_PIN!=NOT_CONNECTED)
	Local_enuErrorState=DIO_enuSetPinDirection(DIO_u8PORTA,NEGATIVE_PIN,DIO_u8INPUT);
	return Local_enuErrorState;

#else
	return Local_enuErrorState;

#endif
}


//===============================================================================================================================================================================


ES_t LM35_enuGetTemp(LM35_config* Copy_pstrLM35, u16 * Copy_pu16Temperature )
{
	ES_t Local_enuErrorState = ES_NOK;

	if((Copy_pstrLM35 != NULL)&&(Copy_pu16Temperature !=NULL))
	{
		u16 Local_u16DigitalVal,Local_u16AnalogVal,Local_u16MilliVolt;

		//get the digital value of the conversion
		ADC_enuStartConversionSync(Copy_pstrLM35->Copy_u8LM35Channel,&Local_u16DigitalVal);

		//convert the voltage value from Volt to milliVolt
		Local_u16MilliVolt=Copy_pstrLM35->Copy_f32VoltageRefrence*1000;

		//get the analog value
		Local_u16AnalogVal=(((u32)Local_u16DigitalVal*Local_u16MilliVolt)/(Copy_pstrLM35->Copy_u16ADCResolution));

		//for every 10mV change there is 1 degree celsius
		*Copy_pu16Temperature = Local_u16AnalogVal/10;


		Local_enuErrorState=ES_OK;
	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}
	return Local_enuErrorState;
}
