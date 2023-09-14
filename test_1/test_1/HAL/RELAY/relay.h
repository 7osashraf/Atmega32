/*
 * relay.h
 *
 * Created: 9/12/2023 4:59:47 PM
 *  Author: ENG HOSAM
 */ 


#ifndef RELAY_H_
#define RELAY_H_

/* ------------------Includes------------------*/
#include "../../MCAL/DIO/dio.h"

/* ------------------Macro Declarations------------------*/
#define RELAY_ON_STATUS		0x01U
#define RELAY_OFF_STATUS	0x00U

/* ------------------Macro Function Declarations------------------*/


/* ------------------Data Type Declarations------------------*/
typedef struct{
	uint8 relay_port   : 4;
	uint8 relay_pin    : 3;
	uint8 relay_status : 1;
}ST_relay_t;


/* ------------------Software Interface Declarations------------------*/
EN_errorReturn_t relay_initialize(const ST_relay_t *_relay);
EN_errorReturn_t relay_turn_on(const ST_relay_t *_relay);
EN_errorReturn_t relay_turn_off(const ST_relay_t *_relay);


#endif /* RELAY_H_ */