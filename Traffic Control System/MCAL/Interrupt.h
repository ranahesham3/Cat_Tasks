/*
 * Interrupt.h
 *
 *  Created on: Sep 1, 2023
 *      Author: DELL
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_


#define ISR(VECT_NUM,...)		void VECT_NUM (void) __attribute__ ((signal))__VA_ARGS__;\
								void VECT_NUM (void)


//if its written in ISR() ->enable the interrupt before the context switch
#define ISR_NOBLOCK				__attribute__((interrupt))
//if its written in ISR() ->the func doesn't have automatic setup & clean up
//used to allow the programmer to have complete control over the func assembly
#define ISR_NAKED				__attribute__((naked))



#define VECT_INT0				__vector_1
#define VECT_INT1				__vector_2
#define VECT_INT2				__vector_3

#define VECT_ADC				__vector_16

#define VECT_TIMER0_COMP		__vector_10
#define VECT_TIMER0_OVF 		__vector_11


#endif /* INTERRUPT_H_ */
