/*
 * button.c
 *
 * Created: 10/11/2022 8:04:20 AM
 *  Author: ENG HOSAM
 */ 

#include "button.h"

EN_errorReturn_t BUTTON_inti(const ST_button_t *btn){
	EN_errorReturn_t ret = E_OK;
	
	if(NULL == btn){
		ret = E_NOT_OK;
	}
	else{
		ret = DIO_pin_initialize(&(btn->button_pin));
	}
	return ret;
	
}


EN_errorReturn_t BUTTON_read(const ST_button_t *btn, EN_button_state_t *btn_state){
	EN_errorReturn_t ret = E_NOT_OK;
	EN_Logic_t Pin_Logic_Status = GPIO_LOW;
	if((NULL == btn) || (NULL == btn_state)){
		ret = E_NOT_OK;
	}
	else{
		DIO_read_logic(&(btn->button_pin), &Pin_Logic_Status);
		if(BUTTON_ACTIVE_HIGH == btn->button_connection){
			if(GPIO_HIGH == Pin_Logic_Status){
				*btn_state = BUTTON_PRESSED;
			}
			else{
				*btn_state = BUTTON_RELEASED;
			}
		}
		else if(BUTTON_ACTIVE_LOW == btn->button_connection){
			if(GPIO_HIGH == Pin_Logic_Status){
				*btn_state = BUTTON_RELEASED;
			}
			else{
				*btn_state = BUTTON_PRESSED;
			}
		}
		else { /*  NNOTHING  */ }
		ret  = E_OK;
	}
	return ret;
	
}
