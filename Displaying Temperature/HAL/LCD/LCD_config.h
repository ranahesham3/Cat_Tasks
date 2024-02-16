/*
 * LCD_config.h
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_


/*				 CONTROL PINS			*/

#define LCD_MODE 	EIGHT_BIT_MODE


/*				 CONTROL PINS			*/
#define RS_PORT		DIO_u8PORTB
#define RS_PIN		DIO_u8PIN0

#define RW_PORT		DIO_u8PORTB
#define RW_PIN		DIO_u8PIN1

#define EN_PORT		DIO_u8PORTB
#define EN_PIN		DIO_u8PIN2


/*				 DATA PINS				*/
#define D0_PORT		DIO_u8PORTA
#define D0_PIN		DIO_u8PIN0

#define D1_PORT		DIO_u8PORTA
#define D1_PIN		DIO_u8PIN1

#define D2_PORT		DIO_u8PORTA
#define D2_PIN		DIO_u8PIN2

#define D3_PORT		DIO_u8PORTA
#define D3_PIN		DIO_u8PIN3

#define D4_PORT		DIO_u8PORTA
#define D4_PIN		DIO_u8PIN4

#define D5_PORT		DIO_u8PORTA
#define D5_PIN		DIO_u8PIN5

#define D6_PORT		DIO_u8PORTA
#define D6_PIN		DIO_u8PIN6

#define D7_PORT		DIO_u8PORTA
#define D7_PIN		DIO_u8PIN7

/* 			Pattern_num in write special_char			*/
#define	Pattern0	0
#define	Pattern1	1
#define	Pattern2	2
#define	Pattern3	3
#define	Pattern4	4
#define	Pattern5	5
#define	Pattern6	6
#define	Pattern7	7


#endif
