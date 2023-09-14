/*
 * led.h
 *
 * Created: 10/11/2022 8:06:03 AM
 *  Author: ENG HOSAM
 */ 


#ifndef LED_H_
#define LED_H_

/* ------------------Includes------------------*/
#include "../../MCAL/DIO/dio.h"

/* ------------------Macro Declarations------------------*/

/* ------------------Macro Function Declarations------------------*/


/* ------------------Data Type Declarations------------------*/
typedef enum{
	LED_OFF,
	LED_ON
}EN_led_status;

typedef struct{
	uint8 port_name : 4;
	uint8 pin : 3;
	uint8 led_status : 1;
}ST_led_t;

/* ------------------Software Interface Declarations------------------*/

EN_errorReturn_t LED_inti(const ST_led_t *led);
EN_errorReturn_t LED_turn_on(const ST_led_t *led);
EN_errorReturn_t LED_turn_off(const ST_led_t *led);
EN_errorReturn_t LED_toggle(const ST_led_t *led);




#endif /* LED_H_ */