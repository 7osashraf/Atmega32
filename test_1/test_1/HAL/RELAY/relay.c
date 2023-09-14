/*
 * relay.c
 *
 * Created: 9/12/2023 4:59:35 PM
 *  Author: ENG HOSAM
 */ 

#include "relay.h"

EN_errorReturn_t relay_initialize(const ST_relay_t *_relay){
	EN_errorReturn_t ret = E_OK;
	
	if(NULL == _relay){
		ret = E_NOT_OK;
	}
	else{
		ST_Pin_Config_t pin_obj = {.port = _relay->relay_port, .pin = _relay->relay_pin,
		.direction = GPIO_DIRECTION_OUTPUT, .logic = _relay->relay_status};
		DIO_pin_write_logic(&pin_obj, GPIO_HIGH);
	}
	return ret;
}

EN_errorReturn_t relay_turn_on(const ST_relay_t *_relay){
	EN_errorReturn_t ret = E_OK;
	
	if(NULL == _relay){
		ret = E_NOT_OK;
	}
	else{
		ST_Pin_Config_t pin_obj = {.port = _relay->relay_port, .pin = _relay->relay_pin,
		.direction = GPIO_DIRECTION_OUTPUT, .logic = _relay->relay_status};
		DIO_pin_write_logic(&pin_obj, GPIO_HIGH);
	}
	return ret;
}

EN_errorReturn_t relay_turn_off(const ST_relay_t *_relay){
	EN_errorReturn_t ret = E_OK;
	
	if(NULL == _relay){
		ret = E_NOT_OK;
	}
	else{
		ST_Pin_Config_t pin_obj = {.port = _relay->relay_port, .pin = _relay->relay_pin,
		.direction = GPIO_DIRECTION_OUTPUT, .logic = _relay->relay_status};
		DIO_pin_write_logic(&pin_obj, GPIO_LOW);
	}
	return ret;
}