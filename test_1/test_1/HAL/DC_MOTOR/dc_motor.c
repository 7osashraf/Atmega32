/*
 * dc_motor.c
 *
 * Created: 9/12/2023 4:31:21 PM
 *  Author: ENG HOSAM
 */ 

#include "dc_motor.h"

EN_errorReturn_t dc_motor_initialize(const ST_dc_motor_t *_dc_motor){
	EN_errorReturn_t ret = E_OK;
	if(NULL == _dc_motor){
		ret = E_NOT_OK;
	}
	else{
		DIO_pin_initialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]));
		DIO_pin_initialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]));
	}
	return ret;
}

EN_errorReturn_t dc_motor_move_right(const ST_dc_motor_t *_dc_motor){
	EN_errorReturn_t ret = E_OK;
	if(NULL == _dc_motor){
		ret = E_NOT_OK;
	}
	else{
		DIO_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_HIGH);
		DIO_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);
	}
	return ret;
}

EN_errorReturn_t dc_motor_move_left(const ST_dc_motor_t *_dc_motor){
	EN_errorReturn_t ret = E_OK;
	if(NULL == _dc_motor){
		ret = E_NOT_OK;
	}
	else{
		DIO_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);
		DIO_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_HIGH);
	}
	
	return ret;
}

EN_errorReturn_t dc_motor_stop(const ST_dc_motor_t *_dc_motor){
	EN_errorReturn_t ret = E_OK;
	if(NULL == _dc_motor){
		ret = E_NOT_OK;
	}
	else{
		DIO_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);
		DIO_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);
	}
	return ret;
}