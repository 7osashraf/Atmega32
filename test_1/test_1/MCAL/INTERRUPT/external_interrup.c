/*
 * external_interrup.c
 *
 * Created: 9/13/2023 4:19:25 PM
 *  Author: ENG HOSAM
 */ 

#include "external_interrupt.h"


/*  Pointer to function to hold the callbacks for INTx  */
static InterruptHandler INT0_InterruptHandler = NULL;
static InterruptHandler INT1_InterruptHandler = NULL;
static InterruptHandler INT2_InterruptHandler = NULL;

static EN_errorReturn_t Interrupt_INTx_Enable(const ST_interrupt_INTx_t *int_obj);
static EN_errorReturn_t Interrupt_INTx_Disable(const ST_interrupt_INTx_t *int_obj);
static EN_errorReturn_t Interrupt_INTx_Priority_Init(const ST_interrupt_INTx_t *int_obj);
static EN_errorReturn_t Interrupt_INTx_Edge_Init(const ST_interrupt_INTx_t *int_obj);
static EN_errorReturn_t Interrupt_INTx_Pin_Init(const ST_interrupt_INTx_t *int_obj);

static EN_errorReturn_t INT0_SetInterruptHandler(void (*InterruptHandler)(void));
static EN_errorReturn_t INT1_SetInterruptHandler(void (*InterruptHandler)(void));
static EN_errorReturn_t INT2_SetInterruptHandler(void (*InterruptHandler)(void));
static EN_errorReturn_t Interrupt_INTx_SetInterruptHandler(const ST_interrupt_INTx_t *int_obj);


EN_errorReturn_t EXIT_Interrupts_Init(const ST_interrupt_INTx_t *int_obj){
	EN_errorReturn_t ret = 0;
	if(NULL == int_obj){
		ret = E_NOT_OK;
	}
	else{
		/*  Disable The External interrupt  */
		ret = Interrupt_INTx_Disable(int_obj);
		/*  Configure External interrupt edge   */
		ret = Interrupt_INTx_Edge_Init(int_obj);
		/*  Configure External interrupt I/O pin    */
		ret = Interrupt_INTx_Pin_Init(int_obj);
		/*  Configure Default Interrupt CallBack    */
		ret = Interrupt_INTx_SetInterruptHandler(int_obj);
		/*  Enable The External interrupt  */
		ret = Interrupt_INTx_Enable(int_obj);
	}
	return ret;
}
EN_errorReturn_t Interrupt_INTx_DeInit(const ST_interrupt_INTx_t *int_obj){
	EN_errorReturn_t ret = E_NOT_OK;
	if(NULL == int_obj){
		ret = E_NOT_OK;
	}
	else{
		ret = Interrupt_INTx_Disable(int_obj);
	}
	return ret;
}

static EN_errorReturn_t Interrupt_INTx_Enable(const ST_interrupt_INTx_t *int_obj){
	EN_errorReturn_t ret = E_NOT_OK;
	if(NULL == int_obj){
		ret = E_NOT_OK;
	}
	else{
		switch(int_obj->source){
			case INTERRUPT_EXTERNAL_INT0 :
				SET_BIT(GICR,INT0);
				ret = E_OK;
				break;
			case INTERRUPT_EXTERNAL_INT1 :
				SET_BIT(GICR,INT1);

				ret = E_OK;
				break;
			case INTERRUPT_EXTERNAL_INT2 :
				SET_BIT(GICR,INT2);
				ret = E_OK;
				break;
			default : ret = E_NOT_OK;
		}
	}
	return ret;
}
static EN_errorReturn_t Interrupt_INTx_Disable(const ST_interrupt_INTx_t *int_obj){
	EN_errorReturn_t ret = E_NOT_OK;
	if(NULL == int_obj){
		ret = E_NOT_OK;
	}
	else{
		switch(int_obj->source){
			case INTERRUPT_EXTERNAL_INT0 :
				CLEAR_BIT(GICR,INT0);    /* Disable the INT0 external interrupt */
				ret = E_OK;
				break;
			case INTERRUPT_EXTERNAL_INT1 :
				CLEAR_BIT(GICR,INT1);    /* Disable the INT1 external interrupt */
				ret = E_OK;
				break;
			case INTERRUPT_EXTERNAL_INT2 :
				CLEAR_BIT(GICR,INT2);    /* Disable the INT2 external interrupt */
				ret = E_OK;
				break;
			default : ret = E_NOT_OK;
		}
	}
	return ret;
}
static EN_errorReturn_t Interrupt_INTx_Edge_Init(const ST_interrupt_INTx_t *int_obj){
	EN_errorReturn_t ret = E_NOT_OK;
	if(NULL == int_obj){
		ret = E_NOT_OK;
	}
	else{
		switch(int_obj->source){
			case INTERRUPT_EXTERNAL_INT0 :
					if(INTERRUPT_LOW_LEVEL == int_obj->edge){
						CLEAR_BIT(MCUCR,ISC00);
						CLEAR_BIT(MCUCR,ISC01);
					}
					else if (INTERRUPT_HIGH_LEVEL == int_obj->edge){
						SET_BIT(MCUCR,ISC00);
						CLEAR_BIT(MCUCR,ISC01);
					}
					else if (INTERRUPT_FALLING_EDGE == int_obj->edge){
						CLEAR_BIT(MCUCR,ISC00);
						SET_BIT(MCUCR,ISC01);
					}
					else if(INTERRUPT_RAISING_EDGE == int_obj->edge){
						SET_BIT(MCUCR,ISC00);
						SET_BIT(MCUCR,ISC01);
					}
					else {  /*      Nothing     */}
					ret = E_OK;
					break;
			case INTERRUPT_EXTERNAL_INT1 :
					if(INTERRUPT_LOW_LEVEL == int_obj->edge){
						CLEAR_BIT(MCUCR,ISC10);
						CLEAR_BIT(MCUCR,ISC11);
					}
					else if (INTERRUPT_HIGH_LEVEL == int_obj->edge){
						SET_BIT(MCUCR,ISC10);
						CLEAR_BIT(MCUCR,ISC11);
					}
					else if (INTERRUPT_FALLING_EDGE == int_obj->edge){
						CLEAR_BIT(MCUCR,ISC10);
						SET_BIT(MCUCR,ISC11);
					}
					else if(INTERRUPT_RAISING_EDGE == int_obj->edge){
						SET_BIT(MCUCR,ISC10);
						SET_BIT(MCUCR,ISC11);
					}
					else {  /*      Nothing     */}
					ret = E_OK;
					break;
			case INTERRUPT_EXTERNAL_INT2 :
					if(INTERRUPT_FALLING_EDGE == int_obj->edge){
						SET_BIT(MCUCSR,ISC2);
					}
					else if(INTERRUPT_RAISING_EDGE == int_obj->edge){
						CLEAR_BIT(MCUCSR,ISC2);
					}
					else {  /*      Nothing     */}
					ret = E_OK;
					break;
			default : ret = E_NOT_OK;
		}
	}
	return ret;
}
static EN_errorReturn_t Interrupt_INTx_Pin_Init(const ST_interrupt_INTx_t *int_obj){
	EN_errorReturn_t ret = E_NOT_OK;
	if(NULL == int_obj){
		ret = E_NOT_OK;
	}
	else{
		ret = DIO_pin_direction_init(&(int_obj->mcu_pin));
	}
	return ret;
}

static EN_errorReturn_t INT0_SetInterruptHandler(void (*InterruptHandler)(void)){
	EN_errorReturn_t ret = E_NOT_OK;
	if(NULL == InterruptHandler){
		ret = E_NOT_OK;
	}
	else{
		INT0_InterruptHandler = InterruptHandler;
		ret = E_OK;
	}
	return ret;
}
static EN_errorReturn_t INT1_SetInterruptHandler(void (*InterruptHandler)(void)){
	EN_errorReturn_t ret = E_NOT_OK;
	if(NULL == InterruptHandler){
		ret = E_NOT_OK;
	}
	else{
		INT1_InterruptHandler = InterruptHandler;
		ret = E_OK;
	}
	return ret;
}
static EN_errorReturn_t INT2_SetInterruptHandler(void (*InterruptHandler)(void)){
	EN_errorReturn_t ret = E_NOT_OK;
	if(NULL == InterruptHandler){
		ret = E_NOT_OK;
	}
	else{
		INT2_InterruptHandler = InterruptHandler;
		ret = E_OK;
	}
	return ret;
}
static EN_errorReturn_t Interrupt_INTx_SetInterruptHandler(const ST_interrupt_INTx_t *int_obj){
	EN_errorReturn_t ret = E_NOT_OK;
	if(NULL == int_obj){
		ret = E_NOT_OK;
	}
	else{
		switch(int_obj->source){
			case INTERRUPT_EXTERNAL_INT0 :
			/*  Set Default Interrupt Handler for INT0 External Interrupt   : Application ISR   */
			ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
			break;
			case INTERRUPT_EXTERNAL_INT1 :
			/*  Set Default Interrupt Handler for INT1 External Interrupt   : Application ISR   */
			ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
			break;
			case INTERRUPT_EXTERNAL_INT2 :
			/*  Set Default Interrupt Handler for INT2 External Interrupt   : Application ISR   */
			ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
			break;
			default : ret = E_NOT_OK;
		}
	}
	return ret;
}

ISR(INT0_vect){
	
	/*  Callback function gets called every time this ISR executes  */
	if(INT0_InterruptHandler){INT0_InterruptHandler();}
}

ISR(INT1_vect){
	
	/*  Callback function gets called every time this ISR executes  */
	if(INT1_InterruptHandler){INT1_InterruptHandler();}
}

ISR(INT2_vect){
	
	/*  Callback function gets called every time this ISR executes  */
	if(INT2_InterruptHandler){INT2_InterruptHandler();}
}