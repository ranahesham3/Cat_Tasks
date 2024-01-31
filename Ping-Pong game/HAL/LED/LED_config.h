/*
 * LED_config.h
 *
 *  Created on: Aug 23, 2023
 *      Author: DELL
 */

#ifndef LED_CONFIG_H_
#define LED_CONFIG_H_

#define LED_NUM		3

typedef struct
{
	u8 LED_PortID;
	u8 LED_PinID;
	u8 LED_Connection;
	u8 LED_start;
}LED_t;

#endif
