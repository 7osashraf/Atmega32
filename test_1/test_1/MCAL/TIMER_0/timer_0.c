/*
 * timer_0.c
 *
 * Created: 9/14/2023 12:13:06 AM
 *  Author: ENG HOSAM
 */ 

#include "timer_0.h"

static void (*tmr0_overFlow_interruptHandler)(void);
static void (*tmr0_OC_interruptHandler)(void);



EN_errorReturn_t  Timer0_Init(const ST_timer0_t *_timer){
	EN_errorReturn_t ret = E_OK;
	if(_timer == NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		switch(_timer->mode){
					case TIMER0_NOTMAL_MODE :
						CLEAR_BIT(TCCR0,WGM00);
						CLEAR_BIT(TCCR0,WGM01);
						break;
						
					case TIMER0_PHASS_CORRECT_MODE :
						SET_BIT(TCCR0,WGM00);
						CLEAR_BIT(TCCR0,WGM01);
						break;
					
					case TIMER0_CTC_MODE :
						CLEAR_BIT(TCCR0,WGM00);
						SET_BIT(TCCR0,WGM01);
						break;
					
					case TIMER0_FAST_PWM_MODE :
						SET_BIT(TCCR0,WGM00);
						SET_BIT(TCCR0,WGM01);
						break;
		}
		
		tmr0_overFlow_interruptHandler = _timer->TIMER0_OV_interruptHandler;
		tmr0_OC_interruptHandler = _timer->TIMER0_OC_interruptHandler;
		
		SET_PERSCALLEER(_timer->prescaler_value);
		
		SET_OCO_MODE(_timer->ocMode);
		
		if(_timer->ocMode != OCO_DISCONNECTED)
		{
			SET_BIT(DDRB,3);
		}
		
	}
}

EN_errorReturn_t  Timer0_Write_Value( uint16 _value){
	EN_errorReturn_t ret = E_OK;
	if(_value > 255)
	{
		ret = E_NOT_OK;
	}
	else
	{
		TCNT0 =  _value;
	}
	return ret;
}

EN_errorReturn_t  Timer0_Read_Value(const ST_timer0_t *_timer, uint16 *_value){
	EN_errorReturn_t ret = E_OK;
	if(_value == NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		*_value = TCNT0;
	}
	return ret;
}

EN_errorReturn_t TMR0_OverFlow_Iterrupt_Enable(const ST_timer0_t* timer_0){
	EN_errorReturn_t ret = E_OK;
	if(timer_0 == NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		tmr0_overFlow_interruptHandler = timer_0->TIMER0_OV_interruptHandler;
		TIMER0_OVERFLOW_INTERRUPT_ENABLE();
	}
	return ret;
}

EN_errorReturn_t TMR0_OverFlow_Iterrupt_Disable(const ST_timer0_t* timer_0){
	EN_errorReturn_t ret = E_OK;
	if(timer_0 == NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		tmr0_overFlow_interruptHandler = NULL;
		TIMER0_OVERFLOW_INTERRUPT_DISABLE();
	}
	return ret;
}

EN_errorReturn_t TMR0_OC_Iterrupt_Enable(const ST_timer0_t* timer_0){
	EN_errorReturn_t ret = E_OK;
	if(timer_0 == NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		tmr0_OC_interruptHandler = timer_0->TIMER0_OC_interruptHandler;
		TIMER0_OC_INTERRUPT_ENABLE();
	}
	return ret;
}

EN_errorReturn_t TMR0_OC_Iterrupt_Disnable(const ST_timer0_t* timer_0){
	EN_errorReturn_t ret = E_OK;
	if(timer_0 == NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		tmr0_OC_interruptHandler = NULL;
		TIMER0_OC_INTERRUPT_DISABLE();
	}
	return ret;
}

ISR(TIMER0_OVF_vect)
{
	if(tmr0_overFlow_interruptHandler != NULL)
	{
		tmr0_overFlow_interruptHandler();
	}
}

ISR(TIMER0_COMP_vect)
{
	if(tmr0_OC_interruptHandler != NULL)
	{
		tmr0_OC_interruptHandler();
	}
}