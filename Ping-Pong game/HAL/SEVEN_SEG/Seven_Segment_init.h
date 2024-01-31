/*
 * Seven_Segment_init.h
 *
 *  Created on: Aug 24, 2023
 *      Author: DELL
 */


#ifndef SEVEN_SEGMENT_INT_H_
#define SEVEN_SEGMENT_INT_H_


ES_t Seven_Segment_enuInit(void);

ES_t Seven_Segment_enuDisplayNum(u8 Copy_u8DisplayNum,u8 Copy_u8SEGNum);

ES_t Seven_Segment_enuEnableCommon(u8 Copy_u8SEGNum);

ES_t Seven_Segment_enuDisableCommon(u8 Copy_u8SEGNum);

ES_t Seven_Segment_enuEnableDot(u8 Copy_u8SEGNum);

ES_t Seven_Segment_enuDisableDot(u8 Copy_u8SEGNum);

ES_t Seven_Segment_enuClearDisplay(u8 Copy_u8SEGNum);


#endif
