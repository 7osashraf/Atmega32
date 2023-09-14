/*
 * button.h
 *
 * Created: 10/11/2022 8:04:40 AM
 *  Author: ENG HOSAM
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

/* ------------------Includes------------------*/
#include "../../MCAL/DIO/dio.h"

/* ------------------Macro Declarations------------------*/

/* ------------------Macro Function Declarations------------------*/


/* ------------------Data Type Declarations------------------*/
typedef enum{
	BUTTON_PRESSED,
	BUTTON_RELEASED
}EN_button_state_t;

typedef enum{
	BUTTON_ACTIVE_HIGH,
	BUTTON_ACTIVE_LOW
}EN_button_active_t;

typedef struct{
	ST_Pin_Config_t button_pin;
	EN_button_state_t button_state;
	EN_button_active_t button_connection;
}ST_button_t;

/* ------------------Software Interface Declarations------------------*/
EN_errorReturn_t BUTTON_inti(const ST_button_t *btn);
EN_errorReturn_t BUTTON_read(const ST_button_t *btn, EN_button_state_t *btn_state);




#endif /* BUTTON_H_ */