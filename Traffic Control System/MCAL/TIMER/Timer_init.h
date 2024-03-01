/*
 * Timer_init.h
 *
 *  Created on: Feb 22, 2024
 *      Author: DELL
 */


#ifndef TIMER_INIT_H_
#define TIMER_INIT_H_


ES_t TIMER_enuInit(void);

ES_t TIMER0_enuDelayMilliSecondSynch(u32 Copy_u32Time );

ES_t TIMER0_enuDelayMilliSecondAsynch(u32 Copy_u32Time , void (*Copy_PfunCallBack)(void*) , void * Copy_PvidArg);

ES_t TIMER0_enuGeneratePWM(u8 Copy_u8DutyCycle);

#endif /* TIMER_INIT_H_ */
