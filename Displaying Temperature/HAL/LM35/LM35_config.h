/*
 * LM35_config.h
 *
 *  Created on: Feb 16, 2024
 *      Author: DELL
 */

#ifndef LM35_CONFIG_H_
#define LM35_CONFIG_H_

/*
 * the positive & negative pins need to be on port A (ADC Pins)
 * if you are using single ended channel  -->assign it to POSITIVE_PIN and NEGATIVE_PIN will be NOT_CONNECTED
 */
#define POSITIVE_PIN			DIO_u8PIN0

#define NEGATIVE_PIN			DIO_u8PIN1


#endif /* LM35_CONFIG_H_ */
