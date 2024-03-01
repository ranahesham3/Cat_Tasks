/*
 * TIMER_priv.h
 *
 *  Created on: Feb 22, 2024
 *      Author: DELL
 */

#ifndef TIMER_PRIV_H_
#define TIMER_PRIV_H_

/* Timer/Counter Control Register */
#define TCCR0							*((volatile u8*)0x53)

#define TCCR0_CS00						0
#define TCCR0_CS01						1
#define TCCR0_CS10						2
#define TCCR0_WGM01						3			/* Wave generation mode bits */
#define TCCR0_WGM00						6			/* Wave generation mode bits */
#define TCCR0_COM00						4			/* compare match o/p mode bits */
#define TCCR0_COM01						5			/* compare match o/p mode bits */
#define TCCR0_FOC0						7			/* Force output compare */


/* Timer /Counter Register */
#define TCNT0							*((volatile u8*)0x52)


/* Output compare register */
#define OCR0							*((volatile u8*)0x5C)


/* Timer /Counter Interrupt Mask Register */
#define TIMSK							*((volatile u8*)0x59)

#define TIMSK_TOIE0						0		 	/* Timer/Counter0 Overflow Interrupt Enable */
#define TIMSK_OCIE0						1		 	/* Timer/Counter0 O/p Compare Match Interrupt Enable */


/* Timer /Counter Interrupt Flag Register */
#define TIFR							*((volatile u8*)0x58)

#define TIFR_TOV0						0			/* Timer/Counter0 Overflow Flag */
#define TIFR_OCF0						1			/* Output Compare Flag 0 */

//==================================================================================================================

/* Clock Select used by the counter */
#define TIMER_NO_CLOCK								0
#define TIMER_NO_Prescaler			           	 	1
#define TIMER_Prescaler8							8
#define TIMER_Prescaler64					    	64
#define TIMER_Prescaler256					    	256
#define TIMER_Prescaler1024					    	1024UL
#define TIMER_EXTERNAL_CLOCK_SOURCE_FALING	    	6
#define TIMER_EXTERNAL_CLOCK_SOURCE_RISING			7

#define TIMER_Prescaller_Mask						0x07



/* Waveform Generation Mode */
#define TIMER0_NORMAL_MODE							0
#define TIMER0_PHASE_CORRECT_PWM_MODE				1
#define TIMER0_CTC_MODE								2
#define TIMER0_FAST_PWM_MODE						3



/* Compare Match Output Mode */
#define OC0_DISCONNECTED							0
#define OC0_TOGGLE									1
#define OC0_CLEAR									2
#define OC0_SET										3

#define OC0_NON_INVERTING_MODE						2
#define OC0_INVERTING_MODE							3

#define CLEAR_UP_COUNTING_SET_DOWN_COUNTING_OC0		2
#define SET_UP_COUNTING_CLEAR_DOWN_COUNTING_OC0		3

#define TIMER0_F_CPU								1000UL
#define TIMER0_OVF_COUNTS							256
#define TIMER0_PERCENTAGE_RATIO						100.0


#endif /* TIMER_PRIV_H_ */
