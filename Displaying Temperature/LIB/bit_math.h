/*
 * bit_math.h
 *
 *  Created on: Sep 1, 2023
 *      Author: DELL
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_REG(Reg) 					Reg=0xFF
#define CLEAR_REG(Reg) 					Reg=0x00
#define TOOGLE_REG(Reg) 				Reg^=0xFF
//#define TOOGLE_REG(Reg) 				Reg=~Reg
#define ASSIGN_REG(Reg,Value)	    	Reg=Value

#define SET_BITS_REG(Reg,Mask) 			Reg|=(Mask)
#define CLEAR_BITS_REG(Reg,Mask) 		Reg&=~(Mask)

#define SET_BIT(Reg,bit) 				Reg|=(1<<bit)
#define CLEAR_BIT(Reg,bit) 				Reg&=~(1<<bit)
#define TOOGLE_BIT(Reg,bit) 			Reg^=(1<<bit)
#define CHECK_BIT(Reg,bit) 				((Reg>>bit)&1)


#endif /* BIT_MATH_H_ */
