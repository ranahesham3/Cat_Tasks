/*
 * LCD_init.h
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */



#ifndef LCD_INIT_H_
#define LCD_INIT_H_

ES_t LCD_enuInit(void);

ES_t LCD_enuDisplayChar(u8 Copy_u8Data);

ES_t LCD_enuSendCommand(u8 Copy_u8Command);

ES_t LCD_enuSendString(const char* Copy_pcString);
//constant to know that i wont change the string that you pass

ES_t LCD_enuGoToXY(u8 Copy_u8X , u8 Copy_u8Y);

ES_t LCD_enuSaveSpecialChar(u8 * Copy_pu8Arr,u8 Copy_u8Pattern_num);

ES_t LCD_enuDisplaySpecialChar(u8 Copy_u8Pattern_num, u8 Copy_u8X , u8 Copy_u8Y);

ES_t LCD_enuWriteNum(s32 Copy_s32Num);

ES_t LCD_enuClearLCD();
#endif
