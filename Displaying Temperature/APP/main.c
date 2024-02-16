#include "stdTypes.h"
#include "errorState.h"


#include "DIO_init.h"
#include "ADC_init.h"
#include "LCD_init.h"
#include "LM35_init.h"


void Display_Temp(u16 Temperature);


int main()
{
	DIO_enuInit();
	ADC_enuInit();
	LCD_enuInit();
	LM35_enuInit();


	u16 Temperature , prev_temp;
	//LM35_config Local_strLMData={ Differential_ADC0_ADC1_1x , ADC_10BIT_RESOLUTION , 5.0};
	LM35_config Local_strLMData={ SingleEnded_ADC1, ADC_10BIT_RESOLUTION , 5.0};

	//Getting & Displaying the first temperature
	LM35_enuGetTemp(&Local_strLMData ,&Temperature);
	Display_Temp(Temperature);

	//assigning the current temperature so we can know when the temperature need to be updated on LCD
	prev_temp=Temperature;

	while(1)
	{
		LM35_enuGetTemp(&Local_strLMData ,&Temperature );

		//comparing the previous temperature & the current temperature
		if(prev_temp!=Temperature)
		{
			Display_Temp(Temperature);

			//updating the previous temperature
			prev_temp=Temperature;
		}
	}
	return 0;
}

void Display_Temp(u16 Temperature)
{
	LCD_enuClearLCD();
	LCD_enuSendString("Temperature=");
	LCD_enuWriteNum(Temperature);
	LCD_enuSendString("C");

}
