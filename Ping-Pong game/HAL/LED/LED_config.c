/*
 * LED_config.c
 *
 *  Created on: Aug 23, 2023
 *      Author: DELL
 */

#include "stdTypes.h"
#include "errorState.h"

#include "DIO_init.h"

#include "LED_config.h"
#include "LED_priv.h"


LED_t LED_AstrConfiguration[LED_NUM]=
{
		{DIO_u8PORTA , DIO_u8PIN3 , LED_SINK , LED_ON},
		{DIO_u8PORTB , DIO_u8PIN1 , LED_SOURC , LED_OFF},
		{DIO_u8PORTC , DIO_u8PIN0 , LED_SOURC, LED_ON}
};

