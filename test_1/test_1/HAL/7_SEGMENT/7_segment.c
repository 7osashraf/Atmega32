/*
 * _7_segment.c
 *
 * Created: 9/12/2023 11:58:11 PM
 *  Author: ENG HOSAM
 */ 

#include "7_segment.h"

EN_errorReturn_t seven_segment_initialize(const ST_segment_t *seg){
	EN_errorReturn_t ret = E_OK;
	if(NULL == seg){
		ret = E_NOT_OK;
	}
	else{
		ret = DIO_pin_initialize(&(seg->segment_pins[SEGMENT_PINO]));
		ret = DIO_pin_initialize(&(seg->segment_pins[SEGMENT_PIN1]));
		ret = DIO_pin_initialize(&(seg->segment_pins[SEGMENT_PIN2]));
		ret = DIO_pin_initialize(&(seg->segment_pins[SEGMENT_PIN3]));
	}
	return ret;
}

EN_errorReturn_t seven_segment_write_number(const ST_segment_t *seg, uint8 number){
	EN_errorReturn_t ret = E_OK;
	if((NULL == seg) && (number > 9)){
		ret = E_NOT_OK;
	}
	else{
		ret = DIO_pin_write_logic(&(seg->segment_pins[SEGMENT_PINO]), (number & 0x01));
		ret = DIO_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN1]), ((number >> 1) & 0x01));
		ret = DIO_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN2]), ((number >> 2) & 0x01));
		ret = DIO_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN3]), ((number >> 3) & 0x01));
	}
	return ret;
}

