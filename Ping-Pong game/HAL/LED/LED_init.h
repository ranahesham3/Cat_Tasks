/*
 * LED_init.h

 *
 *  Created on: Aug 23, 2023
 *      Author: DELL
 */

#ifndef LED_INT_H_
#define LED_INT_H_

ES_t LED_enuInit(LED_t * Copy_pstrLedConfig);

ES_t LED_enuTurnON(LED_t * Copy_pstrLedID);

ES_t LED_enuTurnOFF(LED_t * Copy_pstrLedID);


#endif
