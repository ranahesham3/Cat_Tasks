/*
 * KPD_config.h
 *
 *  Created on: Aug 27, 2023
 *      Author: DELL
 */

#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_


#define NOT_PRESSED		0xff
//because its application dependent so the user need to know this val

/*		ROWS		*/
#define R1_PORT		DIO_u8PORTD
#define R1_PIN		DIO_u8PIN0

#define R2_PORT		DIO_u8PORTD
#define R2_PIN		DIO_u8PIN1

#define R3_PORT		DIO_u8PORTD
#define R3_PIN		DIO_u8PIN2

#define R4_PORT		DIO_u8PORTD
#define R4_PIN		DIO_u8PIN3


/*		COLS		*/
#define C1_PORT		DIO_u8PORTD
#define C1_PIN		DIO_u8PIN4

#define C2_PORT		DIO_u8PORTD
#define C2_PIN		DIO_u8PIN5

#define C3_PORT		DIO_u8PORTD
#define C3_PIN		DIO_u8PIN6

#define C4_PORT		DIO_u8PORTD
#define C4_PIN		DIO_u8PIN7


/*			Keypad			*/
#define KEYS_VALUES				{\
								{'7', '8', '9', '+'},\
								{'4', '5', '6', '-'},\
								{'1', '2', '3', 'x'},\
								{'c', '0', '=', '/'}}



#endif /* KPD_CONFIG_H_ */















