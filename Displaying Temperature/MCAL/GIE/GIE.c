/*
 * GIE.c
 *
 *  Created on: Sep 1, 2023
 *      Author: DELL
 */


#include "../../LIB/bit_math.h"
#include "../../LIB/stdTypes.h"

#include "GIE.h"

void EnableGlobalEnterrupt(void)
{
	SET_BIT(SREG,SREG_I);
}
void DisableGlobalEnterrupt(void)
{
	CLEAR_BIT(SREG,SREG_I);
}
