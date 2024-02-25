/*
 * EXTI_config.h
 *
 *  Created on: Aug 30, 2023
 *      Author: DELL
 */

#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

#include "../../LIB/stdTypes.h"

typedef struct{
	u8 EXTI_u8State;
	u8 EXTI_u8SenseLevel;
}EXTI_t;

#endif /* EXTI_CONFIG_H_ */
