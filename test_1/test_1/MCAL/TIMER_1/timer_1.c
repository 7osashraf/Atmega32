/*
 * timer_1.c
 *
 * Created: 9/14/2023 1:01:27 AM
 *  Author: ENG HOSAM
 */ 

#include "timer_1.h"

static volatile uint16 Global_u16Time1;
static volatile uint16 Global_u16Time2;
static volatile uint16 Global_u16Time3;
static volatile uint16 Global_u16Flag = 0;
uint16 Local_u16TimeON, Local_u16TimeOFF;


static void Timer1ICU_InterruptAction(void);

static void (*(TMR1_InterriptOveFlow)) (void);
static void (*(TMR1_InterriptComA)) (void);
static void (*(TMR1_InterriptComB)) (void);
static void (*(TMR1_InterriptCAPT))(void);


EN_errorReturn_t TIMER1_Init(const ST_timer1_t* timer_1){
	EN_errorReturn_t ret = E_OK;
	if(timer_1 == NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		switch(timer_1->mode)
		{
			case TMR1_NORMAL_MODE :
				CLEAR_BIT(TCCR1A,WGM10);
				CLEAR_BIT(TCCR1A,WGM11);
				CLEAR_BIT(TCCR1B,WGM12);
				CLEAR_BIT(TCCR1B,WGM13);
				break;
			
			case TMR1_PWM_PASS_CORRECT_8BIT_MODE:
				SET_BIT(TCCR1A,WGM10);
				CLEAR_BIT(TCCR1A,WGM11);
				CLEAR_BIT(TCCR1B,WGM12);
				CLEAR_BIT(TCCR1B,WGM13);
				break;
			
			case TMR1_PWM_PASS_CORRECT_9BIT_MODE:
				CLEAR_BIT(TCCR1A,WGM10);
				SET_BIT(TCCR1A,WGM11);
				CLEAR_BIT(TCCR1B,WGM12);
				CLEAR_BIT(TCCR1B,WGM13);
				break;
			
			case TMR1_PWM_PASS_CORRECT_10BIT_MODE:
				SET_BIT(TCCR1A,WGM10);
				SET_BIT(TCCR1A,WGM11);
				CLEAR_BIT(TCCR1B,WGM12);
				CLEAR_BIT(TCCR1B,WGM13);
				break;
			
			case TMR1_CTC_OCR1A_MODE:
				CLEAR_BIT(TCCR1A,WGM10);
				CLEAR_BIT(TCCR1A,WGM11);
				SET_BIT(TCCR1B,WGM12);
				CLEAR_BIT(TCCR1B,WGM13);
				break;
			
			case TMR1_PWM_FAST_MODE_8BIT:
				SET_BIT(TCCR1A,WGM10);
				CLEAR_BIT(TCCR1A,WGM11);
				SET_BIT(TCCR1B,WGM12);
				CLEAR_BIT(TCCR1B,WGM13);
				break;
			
			case TMR1_PWM_FAST_MODE_9BIT:
				CLEAR_BIT(TCCR1A,WGM10);
				SET_BIT(TCCR1A,WGM11);
				SET_BIT(TCCR1B,WGM12);
				CLEAR_BIT(TCCR1B,WGM13);
				break;
			
			case TMR1_PWM_FAST_MODE_10BIT:
				SET_BIT(TCCR1A,WGM10);
				SET_BIT(TCCR1A,WGM11);
				SET_BIT(TCCR1B,WGM12);
				CLEAR_BIT(TCCR1B,WGM13);
				break;

			case TMR1_PWM_PASS_FRQ_ICR1_MODE:
				CLEAR_BIT(TCCR1A,WGM10);
				CLEAR_BIT(TCCR1A,WGM11);
				CLEAR_BIT(TCCR1B,WGM12);
				SET_BIT(TCCR1B,WGM13);
				break;
			
			case TMR1_PWM_PASS_FRQ_OCR1A_MODE:
				SET_BIT(TCCR1A,WGM10);
				CLEAR_BIT(TCCR1A,WGM11);
				CLEAR_BIT(TCCR1B,WGM12);
				SET_BIT(TCCR1B,WGM13);
				break;
			
			case TMR1_PWM_PASS_CORRECT_ICR1_MODE:
				CLEAR_BIT(TCCR1A,WGM10);
				SET_BIT(TCCR1A,WGM11);
				CLEAR_BIT(TCCR1B,WGM12);
				SET_BIT(TCCR1B,WGM13);
				break;
			
			case TMR1_PWM_PASS_CORRECT_OCR1A_MODE:
				SET_BIT(TCCR1A,WGM10);
				SET_BIT(TCCR1A,WGM11);
				CLEAR_BIT(TCCR1B,WGM12);
				SET_BIT(TCCR1B,WGM13);
				break;
			
			case TMR1_CTC_ICR1_MODE:
				CLEAR_BIT(TCCR1A,WGM10);
				CLEAR_BIT(TCCR1A,WGM11);
				SET_BIT(TCCR1B,WGM12);
				SET_BIT(TCCR1B,WGM13);
				break;
			
			case REVERSED:
				SET_BIT(TCCR1A,WGM10);
				CLEAR_BIT(TCCR1A,WGM11);
				SET_BIT(TCCR1B,WGM12);
				SET_BIT(TCCR1B,WGM13);
				break;
			
			case TMR1_PWM_FAST_MODE_ICR1:
				CLEAR_BIT(TCCR1A,WGM10);
				SET_BIT(TCCR1A,WGM11);
				SET_BIT(TCCR1B,WGM12);
				SET_BIT(TCCR1B,WGM13);
				break;
			
			case TMR1_PWM_FAST_MODE_OCR1A:
				SET_BIT(TCCR1A,WGM10);
				SET_BIT(TCCR1A,WGM11);
				SET_BIT(TCCR1B,WGM12);
				SET_BIT(TCCR1B,WGM13);
				break;
		}
		
		TMR1_SET_PRESCALER(timer_1->prescaler);
		TMR1_SELECT_CHANNLE(timer_1->channle);
		
		switch(timer_1->fast_pwm)
		{
			case OC1_DISCONNECTED:
				switch(timer_1->channle)
				{
					case TIMER1_OCR1A:
						CLEAR_BIT(TCCR1A,COM1A0);
						CLEAR_BIT(TCCR1A,COM1A1);
						break;

					case TIMER1_OCR1b:
						CLEAR_BIT(TCCR1A,COM1B0);
						CLEAR_BIT(TCCR1A,COM1B1);
						break;
				}
				break;
			case OC1_TOGGLE:
				switch(timer_1->channle)
				{
					case TIMER1_OCR1A:
						SET_BIT(TCCR1A,COM1A0);
						CLEAR_BIT(TCCR1A,COM1A1);
						DDRD =   0B00100000;
						break;
				
					case TIMER1_OCR1b:
						SET_BIT(TCCR1A,COM1B0);
						CLEAR_BIT(TCCR1A,COM1B1);
						DDRD =   0B00010000;
						break;
				}
				break;
			case OC1_NON_INVERTING:
				switch(timer_1->channle)
				{
					case TIMER1_OCR1A:
						CLEAR_BIT(TCCR1A,COM1A0);
						SET_BIT(TCCR1A,COM1A1);
						DDRD =   0B00110000;
						break;

					case TIMER1_OCR1b:
						CLEAR_BIT(TCCR1A,COM1B0);
						SET_BIT(TCCR1A,COM1B1);
						DDRD =   0B00110000;
						break;
				}
				break;
			case OC1_INVERTING:
				switch(timer_1->channle)
				{
					case TIMER1_OCR1A:
						SET_BIT(TCCR1A,COM1A0);
						SET_BIT(TCCR1A,COM1A1);
						DDRD =   0B00110000;
						break;

					case TIMER1_OCR1b:
						SET_BIT(TCCR1A,COM1B0);
						SET_BIT(TCCR1A,COM1B1);
						DDRD =   0B00110000;
						break;
				}
			break;
		}
	}
	return ret;
		
}
EN_errorReturn_t TIMER1_Interrupt_Over_Flow_enable(const ST_timer1_t* timer_1){
	EN_errorReturn_t ret = E_OK;
	if(timer_1 == NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		TMR1_INTERRUPT_OVER_FLOW_ENABLE();
		TMR1_InterriptOveFlow =timer_1->TMR1_InterriptOveFlow;
	}
	return ret;
}
EN_errorReturn_t TIMER1_Interrupt_Over_Flow_Disable(){
	EN_errorReturn_t ret = E_OK;
	TMR1_INTERRUPT_OVER_FLOW_DISABLE();
	return ret;
}

EN_errorReturn_t TIMER1_voidSetOCR1A(uint16 Copy_u16Value){
	EN_errorReturn_t ret = E_OK;
	OCR1A = Copy_u16Value;
	return ret;
}
EN_errorReturn_t TIMER1_voidSetOCR1B(uint16 Copy_u16Value){
	EN_errorReturn_t ret = E_OK;
	OCR1B = Copy_u16Value;
	return ret;
}

EN_errorReturn_t TIMER1_voidSetICR1(uint16 Copy_u16Value){
	EN_errorReturn_t ret = E_OK;
	ICR1 = Copy_u16Value;
	return ret;
}
EN_errorReturn_t TIMER1_voidSetTCNT1(uint16 Copy_u16Value){
	EN_errorReturn_t ret = E_OK;
	TCNT1 = Copy_u16Value;
	return ret;
}

EN_errorReturn_t PWM_FreQ_KHz(uint16 _ferq){
	EN_errorReturn_t ret = E_OK;
	if(_ferq == 0 )
	{
		ret = E_NOT_OK;
	}
	else
	{
		uint16 ttotal = (uint32)1000/_ferq;
		if(ttotal >= 1)
		{
			ICR1 = ttotal-1;
		}
		else{ICR1 = 0 ;}
	}
	return ret;
}
EN_errorReturn_t PWM_FreQ_Hz(uint16 _ferq){
	EN_errorReturn_t ret = E_OK;
	if(_ferq == 0 )
	{
		ret = E_NOT_OK;
	}
	else
	{
		uint16 ttotal = (uint32)1000000/_ferq;
		if(ttotal >= 1)
		{
			ICR1 = ttotal-1;
		}
		else{ICR1 = 0 ;}
	}
	return ret;
}

EN_errorReturn_t PWM_SetDuty_Cycle(uint8 _duty){
	EN_errorReturn_t ret = E_OK;
	if(_duty >= 100 )
	{
		ret = E_NOT_OK;
	}
	else
	{
		uint16 ton =((uint32)_duty*(ICR1+1))/100;
		if(ton >= 1)
		{
			OCR1A = ton - 1;
		}
		else {OCR1A = 0 ;}
	}
	return ret;
}
EN_errorReturn_t TIMER1_Set_CaptureEdge(uint8 _edge){
	EN_errorReturn_t ret = E_OK;
	switch(_edge)
	{
		case ICU_RISING_EDGE:
		SET_BIT(TCCR1B,ICES1);
		break;
		
		case ICU_FALLING_EDGE:
		CLEAR_BIT(TCCR1B,ICES1);
		break;
	}
	return ret;
}

EN_errorReturn_t TIMER1_Interrupt_COMPA_enable(const ST_timer1_t* timer_1){
	EN_errorReturn_t ret = E_OK;
	if(timer_1 == NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		TMR1_INTERRUPT_COMPA_ENABLE();
		TMR1_InterriptComA = timer_1->TMR1_InterriptComA;
	}
	return ret;
}
EN_errorReturn_t TIMER1_Interrupt_COMPA_Disable(){
	EN_errorReturn_t ret = E_OK;
	TMR1_INTERRUPT_COMPA_DISABLE();
	return ret;
}

EN_errorReturn_t TMR1_Interrupt_COMPB_enable(const ST_timer1_t* timer_1){
	EN_errorReturn_t ret = E_OK;
	if(NULL == timer_1)
	{
		ret = E_NOT_OK;
	}
	else
	{
		TMR1_INTERRUPT_COMPA_ENABLE();
		TMR1_InterriptComB = timer_1->TMR1_InterriptComB;
	}
	return ret;
}
EN_errorReturn_t TMR1_Interrupt_COMPB_Disable(){
	EN_errorReturn_t ret = E_OK;
	TMR1_INTERRUPT_COMPB_DISABLE();
	return ret;
}

EN_errorReturn_t TIMER1_Interrupt_CAPT_enable(void (*fun)(void)){
	EN_errorReturn_t ret = E_OK;
	TMR1_INTERRUPT_CAPT_ENABLE();
	TMR1_InterriptCAPT = fun;
	return ret;
}
EN_errorReturn_t TIMER1_Interrupt_CAPT_Disable(){
	EN_errorReturn_t ret = E_OK;
	TMR1_INTERRUPT_CAPT_DISABLE();
	return ret;
}

EN_errorReturn_t PWM1_voidRead(uint32 *ReturnFreq, uint8 *ReturnDuty){
	EN_errorReturn_t ret = E_OK;
	TCNT1 = 0;

	TIMER1_Set_CaptureEdge(ICU_RISING_EDGE);
	TIMER1_Interrupt_CAPT_enable(Timer1ICU_InterruptAction);

	
	Global_u16Flag = 0;
	while(Global_u16Flag < 3);
	
	Local_u16TimeON = Global_u16Time2 - Global_u16Time1;

	Local_u16TimeOFF = Global_u16Time3 - Global_u16Time2;

	*ReturnDuty = ((uint32) Local_u16TimeON * 100) / ((uint32)Local_u16TimeON + Local_u16TimeOFF);

	*ReturnFreq = ((uint32)1000000) / ((uint32)Local_u16TimeON + Local_u16TimeOFF);
	
	return ret;
}

static void Timer1ICU_InterruptAction(void)
{

	if(Global_u16Flag == 0)
	{

		Global_u16Time1 = ICR1;
		TIMER1_Set_CaptureEdge(ICU_FALLING_EDGE);
		Global_u16Flag = 1;

	}
	else if(Global_u16Flag == 1)
	{

		Global_u16Time2 = ICR1;
		TIMER1_Set_CaptureEdge(ICU_RISING_EDGE);
		Global_u16Flag = 2;

	}
	else if(Global_u16Flag == 2)
	{

		Global_u16Time3 = ICR1;
		TIMER1_Interrupt_CAPT_Disable();
		Global_u16Flag = 3;

	}
	
}


ISR(TIMER1_OVF_vect)
{
	if(TMR1_InterriptOveFlow)
	TMR1_InterriptOveFlow();
}


ISR(TIMER1_COMPA_vect)
{
	if(TMR1_InterriptComA)
	TMR1_InterriptComA();
}


ISR(TIMER1_COMPB_vect)
{
	if(TMR1_InterriptComB)
	TMR1_InterriptComB();
}


ISR(TIMER1_CAPT_vect)
{
	if(TMR1_InterriptCAPT)
	TMR1_InterriptCAPT();
}