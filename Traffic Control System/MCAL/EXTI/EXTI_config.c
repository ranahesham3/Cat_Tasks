/*
 * EXTI_config.c
 *
 *  Created on: Aug 30, 2023
 *      Author: DELL
 */


#include "../../LIB/stdTypes.h"

#include "EXTI_priv.h"
#include "EXTI_config.h"

EXTI_t EXTI_AstrEXTIConfig [3] =
{
		{ACTIVE, FALLING_EDGE},
		{ACTIVE, FALLING_EDGE},
		{ACTIVE, FALLING_EDGE}
};




