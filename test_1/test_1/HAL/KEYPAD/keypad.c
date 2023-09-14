/*
 * keypad.c
 *
 * Created: 9/13/2023 2:31:08 AM
 *  Author: ENG HOSAM
 */ 

#include "keypad.h"

static const uint8 btn_value[ECU_KEYBAD_ROW][ECU_KEYBAD_COLUMNS]={
																	{'7', '8', '9', '/'},
																	{'4', '5', '6', '*'},
																	{'1', '2', '3', '-'},
																	{'#', '0', '=', '+'},
																};


EN_errorReturn_t keypad_initialize(const ST_keypad_t *_keypad_obj){
	EN_errorReturn_t ret = E_OK;
	uint8 rows_counter = 0, columns_counter = 0;
	if(NULL == _keypad_obj){
		ret = E_NOT_OK;
	}
	else{
		for(rows_counter = 0; rows_counter < ECU_KEYBAD_ROW; rows_counter++){
			ret = DIO_pin_initialize(&(_keypad_obj->keypad_row_pins[rows_counter]));
		}
		for(columns_counter = 0; columns_counter < ECU_KEYBAD_COLUMNS; columns_counter++){
			ret = DIO_pin_direction_init(&(_keypad_obj->keypad_columns_pins[columns_counter]));
		}
	}
	return ret;
}

EN_errorReturn_t keypad_get_value(const ST_keypad_t *_keypad_obj, uint8 *value){
	EN_errorReturn_t ret = E_OK;
	uint8 l_rows_counter = 0, l_columns_counter = 0, l_counter = 0;
	uint8 column_logic = 0;
	if((NULL == _keypad_obj) || (NULL == value)){
		ret = E_NOT_OK;
	}
	else{
		for(l_rows_counter = 0; l_rows_counter < ECU_KEYBAD_ROW; l_rows_counter++){
			for(l_counter = 0; l_counter < ECU_KEYBAD_ROW; l_counter++){
				ret = DIO_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_counter]), GPIO_LOW);
			}
			DIO_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_rows_counter]), GPIO_HIGH);
			for(l_columns_counter = 0; l_columns_counter < ECU_KEYBAD_COLUMNS; l_columns_counter++){
				ret = DIO_pin_read_logic(&(_keypad_obj->keypad_columns_pins[l_columns_counter]), &column_logic);
				if(GPIO_HIGH == column_logic){
					*value = btn_value[l_rows_counter][l_columns_counter];
				}
			}
		}
	}
	return ret;
}
