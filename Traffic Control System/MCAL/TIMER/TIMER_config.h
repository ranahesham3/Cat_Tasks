/*
 * TIMER_config.h
 *
 *  Created on: Feb 22, 2024
 *      Author: DELL
 */

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_


/* Clock Select used by the counter
 * Choose between:
 * TIMER_NO_CLOCK
 * TIMER_NO_Prescaler
 * TIMER_Prescaler8
 * TIMER_Prescaler64
 * TIMER_Prescaler256
 * TIMER_Prescaler1024
 * TIMER_EXTERNAL_CLOCK_SOURCE_FALING
 * TIMER_EXTERNAL_CLOCK_SOURCE_RISING
 */
#define TIMER_CLOCK_SELECT					TIMER_Prescaler1024



/* Compare Match Output Mode
 * Choose between:
 *
 * OC0_DISCONNECTED
 *
 * (NON PWM MODE)
 * OC0_TOGGLE
 * OC0_CLEAR
 * OC0_SET
 *
 * (FAST PWM MODE)
 * OC0_NON_INVERTING_MODE
 * OC0_INVERTING_MODE
 */
#define COMPARE_MATCH_OUTPUT_MODE			OC0_DISCONNECTED



/* Waveform Generation Mode
 * Choose between:
 * TIMER0_NORMAL_MODE
 * TIMER0_PHASE_CORRECT_PWM_MODE
 * TIMER0_CTC_MODE
 * TIMER0_FAST_PWM_MODE
 */

#define WAVEFORM_GENERATION_MODE			TIMER0_NORMAL_MODE








#endif /* TIMER_CONFIG_H_ */
