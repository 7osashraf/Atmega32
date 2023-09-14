/*
 * bit_maths.h
 *
 * Created: 10/11/2022 8:09:25 AM
 *  Author: ENG HOSAM
 */ 


#ifndef BIT_MATHS_H_
#define BIT_MATHS_H_

#define SET_BIT(VAR,BITNO)  VAR |= (1 << (BITNO))
#define CLR_BIT(VAR,BITNO)  VAR &= ~(1 << (BITNO))
#define TOG_BIT(VAR,BITNO)  VAR ^= (1 << (BITNO))
#define GET_BIT(VAR,BITNO)  (VAR >> (BITNO) & 0x01)

#include <stdio.h>
#include <stdlib.h>


#endif /* BIT_MATHS_H_ */