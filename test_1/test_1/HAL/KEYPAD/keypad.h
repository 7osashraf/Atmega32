/*
 * keypad.h
 *
 * Created: 9/13/2023 2:31:18 AM
 *  Author: ENG HOSAM
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
/* ------------------Includes------------------*/
#include "../../MCAL/DIO/dio.h"

/* ------------------Macro Declarations------------------*/
#define ECU_KEYBAD_ROW      4
#define ECU_KEYBAD_COLUMNS  4

/* ------------------Macro Function Declarations------------------*/


/* ------------------Data Type Declarations------------------*/
typedef struct{
	ST_Pin_Config_t keypad_row_pins[ECU_KEYBAD_ROW];
	ST_Pin_Config_t keypad_columns_pins[ECU_KEYBAD_COLUMNS];
}ST_keypad_t;
/* ------------------Software Interface Declarations------------------*/
EN_errorReturn_t keypad_initialize(const ST_keypad_t *_keypad_obj);
EN_errorReturn_t keypad_get_value(const ST_keypad_t *_keypad_obj, uint8 *value);



#endif /* KEYPAD_H_ */