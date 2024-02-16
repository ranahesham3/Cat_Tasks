/*
 * EXTI_init.h
 *
 *  Created on: Aug 30, 2023
 *      Author: DELL
 */

#ifndef EXTI_INIT_H_
#define EXTI_INIT_H_


/*For choosing the sense level*/
#define LOW_LEVEL		1
#define LOGICAL_CHANGE	2
#define FALLING_EDGE	3
#define RISING_EDGE		4

/*For choosing EXTI_ID*/
#define INT0			1
#define INT1			2
#define INT2			3

ES_t EXTI_enuInit (void);

ES_t EXTI_enuSetSenceMode(u8 Copy_u8EXTI_ID , u8 Copy_u8SenseLevel);

ES_t EXTI_enuEnableINT(u8 Copy_u8EXTI_ID);

ES_t EXTI_enuDisableINT(u8 Copy_u8EXTI_ID);

ES_t EXTI_enuCallBack(u8 Copy_u8EXTI_ID , void (*Copy_PtrFunc)(void));

#endif /* EXTI_INIT_H_ */
