/*
 * ADC_priv.h
 *
 *  Created on: Sep 18, 2023
 *      Author: DELL
 */

#ifndef ADC_PRIV_H_
#define ADC_PRIV_H_

/*ADC Multiplexer Selection Register*/
#define ADMUX							*((volatile u8*)0x27)

#define ADMUX_REFS0						6		//reference selection bit1
#define ADMUX_REFS1						7		//reference selection bit0
#define ADMUX_ADLAR					    5		//ADCLeft adjust result


/*ADC Control and Status Register A*/
#define ADCSRA							*((volatile u8*)0x26)

#define ADCSRA_ADEN						7		//ADC Enable
#define ADCSRA_ADSC			        	6		//start conversion
#define ADCSRA_ADATE				    5		//auto trigger enable
#define ADCSRA_ADIF						4		//interrupt flag
#define ADCSRA_ADIE						3		//interrupt enable


/*ADC Data Registers*/
#define ADC_U16							*((volatile u16*)0x24)
#define ADCH							*((volatile u8*)0x25)
#define ADCL						    *((volatile u8*)0x24)

#define REGISTER_SHIFT					8
#define SIX_BIT_SHIFT					6
#define TWO_BIT_SHIFT					2


/*Special function I/O Register */
#define SFIOR							*((volatile u8*)0x26)
#define SFIOR_ADTS_0					5
#define SFIOR_ADTS_1					6
#define SFIOR_ADTS_2				    7


//voltage reference selection
#define ADC_AREF						0
#define ADC_AVCC				        1
#define	ADC_INTERNL_REF					3


//Analog channel&gain selection bits
#define SingleEnded_ADC0					0
#define SingleEnded_ADC1					1
#define SingleEnded_ADC2					2
#define SingleEnded_ADC3					3
#define SingleEnded_ADC4					4
#define SingleEnded_ADC5					5
#define SingleEnded_ADC6					6
#define SingleEnded_ADC7					7

#define Differential_ADC0_ADC0_10x			8
#define Differential_ADC1_ADC0_10x			9
#define Differential_ADC0_ADC0_200x			10
#define Differential_ADC1_ADC0_200x			11
#define Differential_ADC2_ADC2_10x			12
#define Differential_ADC3_ADC2_10x			13
#define Differential_ADC2_ADC2_200x			14
#define Differential_ADC3_ADC2_200x			15
#define Differential_ADC0_ADC1_1x			16
#define Differential_ADC1_ADC1_1x			17
#define Differential_ADC2_ADC1_1x			18
#define Differential_ADC3_ADC1_1x			19
#define Differential_ADC4_ADC1_1x			20
#define Differential_ADC5_ADC1_1x			21
#define Differential_ADC6_ADC1_1x			22
#define Differential_ADC7_ADC1_1x			23
#define Differential_ADC0_ADC2_1x			24
#define Differential_ADC1_ADC2_1x			25
#define Differential_ADC2_ADC2_1x			26
#define Differential_ADC3_ADC2_1x			27
#define Differential_ADC4_ADC2_1x			28
#define Differential_ADC5_ADC2_1x			29

#define VOLTAGE_1_22						30
#define GND									31

#define channel_Masking						0x1F


///division factors
#define Division_Factor_2					1		//1 or 0 both work (the same)
#define Division_Factor_4					2
#define Division_Factor_8					3
#define Division_Factor_16					4
#define Division_Factor_32					5
#define Division_Factor_64					6
#define Division_Factor_128					7

#define Prescaller_Masking					7


//ADC Auto Trigger Source Selections
#define ADC_FREE_RUNNING_MODE				0
#define ADC_ANALOG_COMPARATOR				1
#define ADC_EXTERNAL_INTERRUPT_REQUIST0		2
#define ADC_TIMER0_COPMPARE_MATCH			3
#define ADC_TIMER0_OVERFLOW					4
#define ADC_TIMER1_COPMPARE_MATCH_B			5
#define ADC_TIMER1_OVERFLOW					6
#define ADC_TIMER1_CAPTURE_EVENT			7

//adjustment
#define ADC_LEFT_ADJUST						1
#define ADC_RIGHT_ADJUST					0


//reading resolution
#define ADC_8BIT_RESOLUTION					8
#define ADC_10BIT_RESOLUTION				10

#define ADC_DISABLE							0
#define ADC_ENABLE							1


#define ADC_AUTO_TRIGGER_DISABLE			0
#define ADC_AUTO_TRIGGER_ENABLE				1



#define IDLE								0
#define BUSY								1


#define ADC_SINGLE_CHANNEL_ASYNCH			0
#define ADC_CHAIN_CHANNEL_ASYNCH			1




#endif /* ADC_PRIV_H_ */
