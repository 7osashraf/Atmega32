/*
 * timer_0.h
 *
 * Created: 9/14/2023 12:12:53 AM
 *  Author: ENG HOSAM
 */ 


#ifndef TIMER_0_H_
#define TIMER_0_H_

/* ------------------Includes------------------*/
#include "avr/io.h"
#include "../../utilites/types.h"
#include "../../MCAL/DIO/dio.h"
#include "../../utilites/MemoryMap.h"

/* ------------------Macro Declarations------------------*/



/* ------------------Macro Function Declarations------------------*/

#define SET_PERSCALLEER(PRESCALER)					(TCCR0 = TCCR0 | PRESCALER)
#define SET_OCO_MODE(MODE)							(TCCR0 = TCCR0 | (MODE<<4))

#define TIMER0_OVERFLOW_INTERRUPT_ENABLE()          (TIMSK |=  (1<<TOIE0))
#define TIMER0_OVERFLOW_INTERRUPT_DISABLE()         (TIMSK &= ~(1<<TOIE0))

#define TIMER0_OC_INTERRUPT_ENABLE()				(TIMSK |=  (1<<OCIE0))
#define TIMER0_OC_INTERRUPT_DISABLE()				(TIMSK &= ~(1<<OCIE0))

/* ------------------Data Type Declarations------------------*/

typedef enum{
	TIMER0_DISABLE = 0,
	TIMER0_PRESCALER_DIV_BY_1,
	TIMER0_PRESCALER_DIV_BY_8,
	TIMER0_PRESCALER_DIV_BY_64,
	TIMER0_PRESCALER_DIV_BY_256,
	TIMER0_PRESCALER_DIV_BY_1024,
	TIMER0_EXTERNAL_FALLING,
	TIMER0_EXTERNAL_RISING,
}timer0_prescaler_select_t;

typedef enum
{
	TIMER0_NOTMAL_MODE = 0,
	TIMER0_PHASS_CORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FAST_PWM_MODE
}EN_timer0Modes_t;

typedef enum
{
	OCO_DISCONNECTED = 0,
	OCO_TOGGLE,
	OCO_NON_INVERTING,
	OCO_INVERTING
}EN_OCOMode_t;

typedef struct
{
	timer0_prescaler_select_t prescaler_value;
	EN_timer0Modes_t mode;
	EN_OCOMode_t ocMode;
	void (*TIMER0_OV_interruptHandler) (void);
	void (*TIMER0_OC_interruptHandler) (void);
}ST_timer0_t;

/* ------------------Software Interface Declarations ------------------*/
EN_errorReturn_t  Timer0_Init(const ST_timer0_t *_timer);
EN_errorReturn_t  Timer0_Write_Value(uint16 _value);
EN_errorReturn_t  Timer0_Read_Value(const ST_timer0_t *_timer, uint16 *_value);
EN_errorReturn_t TMR0_OverFlow_Iterrupt_Enable(const ST_timer0_t* timer_0);
EN_errorReturn_t TMR0_OverFlow_Iterrupt_Disable(const ST_timer0_t* timer_0);
EN_errorReturn_t TMR0_OC_Iterrupt_Enable(const ST_timer0_t* timer_0);
EN_errorReturn_t TMR0_OC_Iterrupt_Disnable(const ST_timer0_t* timer_0);

#endif /* TIMER_0_H_ */