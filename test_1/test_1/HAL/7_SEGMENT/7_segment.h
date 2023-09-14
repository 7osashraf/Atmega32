/*
 * _7_segment.h
 *
 * Created: 9/13/2023 12:00:19 AM
 *  Author: ENG HOSAM
 */ 


#ifndef _7_SEGMENT_H_
#define _7_SEGMENT_H_

/* ------------------Includes------------------*/
#include "../../MCAL/DIO/dio.h"

/* ------------------Macro Declarations------------------*/
#define SEGMENT_PINO 0
#define SEGMENT_PIN1 1
#define SEGMENT_PIN2 2
#define SEGMENT_PIN3 3


/* ------------------Macro Function Declarations------------------*/


/* ------------------Data Type Declarations------------------*/
typedef enum{
	SEGMENT_COMMON_ANODE,
	SEGMENT_COMMON_CATHODE,
}EN_segment_type_t;

typedef struct{
	ST_Pin_Config_t segment_pins[4];
	EN_segment_type_t segment_type;
}ST_segment_t;

/* ------------------Software Interface Declarations------------------*/
EN_errorReturn_t seven_segment_initialize(const ST_segment_t *seg);
EN_errorReturn_t seven_segment_write_number(const ST_segment_t *seg, uint8 number);



#endif /* _7_SEGMENT_H_ */