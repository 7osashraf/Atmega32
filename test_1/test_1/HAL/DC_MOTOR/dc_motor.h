/*
 * dc_motor.h
 *
 * Created: 9/12/2023 4:31:43 PM
 *  Author: ENG HOSAM
 */ 


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

/* ------------------Includes------------------*/
#include "../../MCAL/DIO/dio.h"

/* ------------------Macro Declarations------------------*/
#define DC_MOTOR_ON_STATUS	0x01U
#define DC_MOTOR_OFF_STATUS 0x00U

#define DC_MOTOR_PIN1		0x00U
#define DC_MOTOR_PIN2		0x01U

/* ------------------Macro Function Declarations------------------*/


/* ------------------Data Type Declarations------------------*/
typedef struct{
	ST_Pin_Config_t dc_motor_pin[2];
}ST_dc_motor_t;

/* ------------------Software Interface Declarations------------------*/
EN_errorReturn_t dc_motor_initialize(const ST_dc_motor_t *_dc_motor);
EN_errorReturn_t dc_motor_move_right(const ST_dc_motor_t *_dc_motor);
EN_errorReturn_t dc_motor_move_left(const ST_dc_motor_t *_dc_motor);
EN_errorReturn_t dc_motor_stop(const ST_dc_motor_t *_dc_motor);


#endif /* DC_MOTOR_H_ */