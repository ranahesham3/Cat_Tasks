/*
 * EXTI_priv.h
 *
 *  Created on: Aug 30, 2023
 *      Author: DELL
 */

#ifndef EXTI_PRIV_H_
#define EXTI_PRIV_H_

#define PINS_NUM		3

#define ACTIVE			1
#define DEACTIVE		2

#define LOW_LEVEL		1
#define LOGICAL_CHANGE	2
#define FALLING_EDGE	3
#define RISING_EDGE		4

#define INT0			1
#define INT1			2
#define INT2			3

/**************************************************/
//MCU Control Register
//Set sense level for INT0,INT1
#define MCUCR				*((volatile u8*)0x55)
#define MCUCR_ISC00				0
#define MCUCR_ISC01				1
#define MCUCR_ISC10				2
#define MCUCR_ISC11				3

//MCU Control and Status Register
//Set sense level for INT2
#define MCUCSR				*((volatile u8*)0x54)
#define MCUCSR_ISC2				6

//General Interrupt Control Register
//enable and disable SIE(Specific Interrupt Enable)
#define GICR				*((volatile u8*)0x5B)
#define GICR_INT0				6
#define GICR_INT1				5
#define GICR_INT2				7

//General Interrupt Flag Register
#define GIFR				*((volatile u8*)0x5A)
#define GIFR_INTF0			0
#define GIFR_INTF1			1
#define GIFR_INTF2			2



#endif /* EXTI_PRIV_H_ */
