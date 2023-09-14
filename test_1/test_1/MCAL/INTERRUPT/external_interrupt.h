/*
 * external_interrupt.h
 *
 * Created: 9/13/2023 4:19:04 PM
 *  Author: ENG HOSAM
 */ 


#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_

/* ------------------Includes------------------*/
#include "../../utilites/types.h"
#include "../../utilites/MemoryMap.h"
#include "../../MCAL/DIO/dio.h"

/* ------------------Macro Declarations------------------*/



/* ------------------Macro Function Declarations------------------*/


/* ------------------Data Type Declarations------------------*/

typedef enum{
	INTERRUPT_LOW_PRIORITY = 0,
	INTERRUPT_HIGH_PRIORITY,
}interrupt_priority_cfg;


typedef void (*InterruptHandler)(void);

typedef enum{
	INTERRUPT_LOW_LEVEL = 0,
	INTERRUPT_HIGH_LEVEL,
	INTERRUPT_FALLING_EDGE,
	INTERRUPT_RAISING_EDGE,
}EN_interrupt_INTx_edge_t;

typedef enum{
	INTERRUPT_EXTERNAL_INT0 = 0,
	INTERRUPT_EXTERNAL_INT1,
	INTERRUPT_EXTERNAL_INT2
}EN_interrupt_INTx_src_t;

typedef struct{
	void(* EXT_InterruptHandler)(void);
	ST_Pin_Config_t mcu_pin;
	EN_interrupt_INTx_edge_t edge;
	EN_interrupt_INTx_src_t source;
	interrupt_priority_cfg priority;
}ST_interrupt_INTx_t;

/* ------------------Software Interface Declarations------------------*/
EN_errorReturn_t EXIT_Interrupts_Init(const ST_interrupt_INTx_t *int_obj);
EN_errorReturn_t EXIT_Interrupts_DeInit(const ST_interrupt_INTx_t *int_obj);


#endif /* EXTERNAL_INTERRUPT_H_ */