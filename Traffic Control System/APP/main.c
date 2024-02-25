/*
 * main.c
 *
 *  Created on: Feb 21, 2024
 *      Author: DELL
 */


#include "../LIB/stdTypes.h"
#include "../LIB/bit_math.h"
#include "../LIB/errorState.h"

#include "../MCAL/DIO/DIO_init.h"
#include "../MCAL/TIMER/Timer_init.h"
#include "../MCAL/EXTI/EXTI_init.h"
#include "../MCAL/GIE/GIE.h"
//======================================================================================================
#define CAR_PORT			DIO_u8PORTA
#define Pedestrain_PORT		DIO_u8PORTB


typedef enum
{
	Car_RED,
	Car_YELLOW,
	Car_GREEN

}Car_Light_Status;


typedef struct
{
	u8 RED;
	u8 YELLOW;
	u8 GREEN;

}Traffic_Lights ;


Traffic_Lights Car={0,0,0};

//======================================================================================================

void Pedestrain_TrafficLight(void*Copy_pvoidArg);

void Setting_RED_Light(u8 Copy_u8PortID);
void Setting_GREEN_Light(u8 Copy_u8PortID);
void TOGGLING_1YELLOW_Light(u8 Copy_u8PortID);
void TOGGLING_2YELLOW_Light(u8 Copy_u8PortID_1,u8 Copy_u8PortID_2);

int main()
{
	DIO_enuInit();
	EXTI_enuInit();
	TIMER_enuInit();


	EXTI_enuCallBack(INT0,Pedestrain_TrafficLight,NULL);
	EXTI_enuEnableINT(INT0);

	EnableGlobalEnterrupt();

	while(1)
	{
		Setting_GREEN_Light(CAR_PORT);
		TIMER0_enuDelayMilliSecondSynch(5000);
		TOGGLING_1YELLOW_Light(CAR_PORT);
		Setting_RED_Light(CAR_PORT);
		TIMER0_enuDelayMilliSecondSynch(5000);
		TOGGLING_1YELLOW_Light(CAR_PORT);
	}
}





void Pedestrain_TrafficLight(void*Copy_pvoidArg)
{
	if(Car.RED==1)
	{
		Setting_RED_Light(CAR_PORT);
		Setting_GREEN_Light(Pedestrain_PORT);
		TIMER0_enuDelayMilliSecondSynch(5000);

		DIO_enuSetPinValue(CAR_PORT,Car_GREEN,DIO_u8LOW);
		TOGGLING_2YELLOW_Light(CAR_PORT,Pedestrain_PORT);

		Setting_GREEN_Light(CAR_PORT);
		Setting_RED_Light(Pedestrain_PORT);
		TIMER0_enuDelayMilliSecondSynch(5000);
		/* to continue in the place the ISR started at */
		TOGGLING_1YELLOW_Light(CAR_PORT);

		Setting_RED_Light(CAR_PORT);
		TIMER0_enuDelayMilliSecondSynch(2500);

	}

	else if(Car.GREEN==1)
	{
		Setting_RED_Light(Pedestrain_PORT);
		Setting_GREEN_Light(CAR_PORT);
		TIMER0_enuDelayMilliSecondSynch(5000);

		DIO_enuSetPinValue(CAR_PORT,Car_GREEN,DIO_u8LOW);
		TOGGLING_2YELLOW_Light(CAR_PORT,Pedestrain_PORT);

		Setting_RED_Light(CAR_PORT);
		Setting_GREEN_Light(Pedestrain_PORT);
		TIMER0_enuDelayMilliSecondSynch(5000);

		Setting_GREEN_Light(Pedestrain_PORT);

		TOGGLING_2YELLOW_Light(CAR_PORT,Pedestrain_PORT);

		Setting_RED_Light(Pedestrain_PORT);
		Setting_GREEN_Light(CAR_PORT);
		TIMER0_enuDelayMilliSecondSynch(2500);
	}

	else if(Car.YELLOW==1)
	{
		TOGGLING_2YELLOW_Light(CAR_PORT,Pedestrain_PORT);

		Setting_RED_Light(CAR_PORT);
		Setting_GREEN_Light(Pedestrain_PORT);
		TIMER0_enuDelayMilliSecondSynch(5000);

		Setting_GREEN_Light(Pedestrain_PORT);

		TOGGLING_2YELLOW_Light(CAR_PORT,Pedestrain_PORT);
		/* to continue in the place the ISR started at */
		Setting_RED_Light(Pedestrain_PORT);
		Setting_GREEN_Light(CAR_PORT);
		TIMER0_enuDelayMilliSecondSynch(5000);
	}
}




void Setting_RED_Light(u8 Copy_u8PortID)
{
	Car.RED=1;	Car.YELLOW=0;		Car.GREEN=0;
	/* Clearing Yellow & Green Leds and setting Red Led */
	DIO_enuSetPinValue(Copy_u8PortID,Car_YELLOW,DIO_u8LOW);
	DIO_enuSetPinValue(Copy_u8PortID,Car_GREEN,DIO_u8LOW);
	DIO_enuSetPinValue(Copy_u8PortID,Car_RED,DIO_u8HIGH);
}
void Setting_GREEN_Light(u8 Copy_u8PortID)
{
	Car.GREEN=1;	Car.RED=0;		Car.YELLOW=0;
	/* Clearing Yellow & Red Leds and setting Green Led */
	DIO_enuSetPinValue(Copy_u8PortID,Car_RED,DIO_u8LOW);
	DIO_enuSetPinValue(Copy_u8PortID,Car_YELLOW,DIO_u8LOW);
	DIO_enuSetPinValue(Copy_u8PortID,Car_GREEN,DIO_u8HIGH);
}
void TOGGLING_1YELLOW_Light(u8 Copy_u8PortID)
{
	Car.YELLOW=1;	Car.GREEN=0; 	Car.RED=0;
	u8 Local_u8Counter;
	for(Local_u8Counter=0;Local_u8Counter<10;Local_u8Counter++)
	{
		/* Clearing Red & Green Leds */
		DIO_enuSetPinValue(Copy_u8PortID,Car_RED,DIO_u8LOW);
		DIO_enuSetPinValue(Copy_u8PortID,Car_GREEN,DIO_u8LOW);
		/* Toggling the yellow led every 0.5s */
		DIO_enuTogPinValue(Copy_u8PortID,Car_YELLOW);
		TIMER0_enuDelayMilliSecondSynch(500);
	}
}

void TOGGLING_2YELLOW_Light(u8 Copy_u8PortID_1,u8 Copy_u8PortID_2)
{
	Car.YELLOW=1;	Car.GREEN=0;	Car.RED=0;
	/* Clearing Red Leds */
	DIO_enuSetPinValue(Copy_u8PortID_1,Car_RED,DIO_u8LOW);
	DIO_enuSetPinValue(Copy_u8PortID_2,Car_RED,DIO_u8LOW);
	u8 Local_u8Counter;
	for(Local_u8Counter=0;Local_u8Counter<10;Local_u8Counter++)
	{
		/* Toggling the yellow leds every 0.5s */
		DIO_enuTogPinValue(Copy_u8PortID_1,Car_YELLOW);
		DIO_enuTogPinValue(Copy_u8PortID_2,Car_YELLOW);
		TIMER0_enuDelayMilliSecondSynch(500);
	}
}

