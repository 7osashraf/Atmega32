/*
 * dio.c
 *
 * Created: 10/11/2022 8:07:12 AM
 *  Author: ENG HOSAM
 */ 

#include "dio.h"

/* Reference to the Data Direction Control Registers */
volatile uint8 *ddr_registers[] = {&DDRA, &DDRB, &DDRC, &DDRD};
/* Reference to the Data Latch  Registers (Read and Write to Data Latch) */
volatile uint8 *pin_registers[] = {&PINA, &PINB, &PINC, &PIND};
/* Reference to the Port Status Register */
volatile uint8 *port_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD};

EN_errorReturn_t DIO_pin_direction_init(const ST_Pin_Config_t *_pin_config){
	EN_errorReturn_t ret = E_OK;
	
	if(NULL == _pin_config || (_pin_config->pin > (PORT_PIN_MAX_NUMBER - 1))){
		ret = E_NOT_OK;
	}
	else{
		switch(_pin_config->direction){
			case GPIO_DIRECTION_OUTPUT :
			CLEAR_BIT(*ddr_registers[_pin_config->port], _pin_config->pin);
			break;
			case GPIO_DIRECTION_INPUT :
			SET_BIT(*ddr_registers[_pin_config->port], _pin_config->pin);
			break;
			default : ret = E_NOT_OK;
		}
	}
	return ret;
	
}

EN_errorReturn_t DIO_pin_get_direction_statues(const ST_Pin_Config_t *_pin_config, EN_Direction_t *direction_statues){
	EN_errorReturn_t ret = E_OK;
	
	if(NULL == _pin_config || NULL == direction_statues || (_pin_config->pin > (PORT_PIN_MAX_NUMBER - 1))){
		ret = E_NOT_OK;
	}
	else{
		*direction_statues = READ_BIT(*ddr_registers[_pin_config->port], _pin_config->pin);
	}
	
	return ret;
	
}

EN_errorReturn_t DIO_pin_write_logic(const ST_Pin_Config_t *_pin_config, EN_Logic_t logic){
	EN_errorReturn_t ret = E_OK;
	if((NULL == _pin_config) || (_pin_config->pin > (PORT_PIN_MAX_NUMBER - 1))){
		ret = E_NOT_OK;
	}
	else{
		switch(logic){
			case GPIO_LOW :
			CLEAR_BIT(*pin_registers[_pin_config->port], _pin_config->pin);
			break;
			case GPIO_HIGH :
			SET_BIT(*pin_registers[_pin_config->port], _pin_config->pin);
			break;
			default :
			ret = E_NOT_OK;
		}
	}
	return ret;
	
}

EN_errorReturn_t DIO_pin_read_logic(const ST_Pin_Config_t *_pin_config, EN_Logic_t *logic){
	EN_errorReturn_t ret = E_OK;
	if(NULL == _pin_config || NULL == logic  || (_pin_config->pin > (PORT_PIN_MAX_NUMBER - 1))){
		ret = E_NOT_OK;
	}
	else{
		*logic = READ_BIT(*port_registers[_pin_config->port], _pin_config->pin);
	}
	return ret;
	
}

EN_errorReturn_t DIO_pin_toggle_logic(const ST_Pin_Config_t *_pin_config){
	EN_errorReturn_t ret = E_OK;
	if(NULL == _pin_config  || (_pin_config->pin > (PORT_PIN_MAX_NUMBER - 1))){
		ret = E_NOT_OK;
	}
	else{
		
		TOGGLE_BIT(*pin_registers[_pin_config->port], _pin_config->pin);
		
	}
	return ret;
	
}

EN_errorReturn_t DIO_pin_initialize(const ST_Pin_Config_t *_pin_config){
	EN_errorReturn_t ret = E_OK;
	if(NULL == _pin_config  || (_pin_config->pin > (PORT_PIN_MAX_NUMBER - 1))){
		ret = E_NOT_OK;
	}
	else{
		ret = DIO_pin_direction_init(_pin_config);
		ret = DIO_write_logic(_pin_config, _pin_config->logic);
	}
	return ret;
}


EN_errorReturn_t DIO_port_direction_initialize(EN_Port_Index_t port,uint8 direction){
	EN_errorReturn_t ret = E_OK;
	if(port  >  PORT_MAX_NUMBER-1){
		ret = E_NOT_OK;
	}
	else{
		*ddr_registers[port] = direction;
	}
	return ret;
}

EN_errorReturn_t DIO_port_get_direction_status(EN_Port_Index_t port,uint8 *direction_status){
	EN_errorReturn_t ret = E_OK;
	if((NULL == direction_status) && (port > PORT_MAX_NUMBER-1)){
		ret = E_NOT_OK;
	}
	else{
		*direction_status = *ddr_registers[port];
	}
	return ret;
	
}

EN_errorReturn_t DIO_port_write_logic(EN_Port_Index_t port,uint8 logic){
	EN_errorReturn_t ret = E_OK;
	if(port > PORT_MAX_NUMBER-1){
		ret = E_NOT_OK;
	}
	else{
		*pin_registers[port] = logic;
	}
	return ret;
}

EN_errorReturn_t DIO_port_read_logic(EN_Port_Index_t port,uint8 *logic){
	EN_errorReturn_t ret = E_OK;
	if((NULL == logic) && (port > PORT_MAX_NUMBER-1)){
		ret = E_NOT_OK;
	}
	else{
		*logic = *pin_registers[port];
	}
	return ret;
}

EN_errorReturn_t DIO_port_toggle_logic(EN_Port_Index_t port){
	EN_errorReturn_t ret = E_OK;
	if(port > PORT_MAX_NUMBER-1){
		ret = E_NOT_OK;
	}
	else{
		*pin_registers[port] ^= PORTC_MASK;
	}
	return ret;
}
