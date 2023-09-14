/*
 * led.c
 *
 * Created: 10/11/2022 8:05:43 AM
 *  Author: ENG HOSAM
 */ 

#include "led.h"

EN_errorReturn_t LED_inti(const ST_led_t *led){
	EN_errorReturn_t ret = E_OK;
	if(NULL == led){
		ret = E_NOT_OK;
	}
	else{
		ST_Pin_Config_t pin_obj = { .port = led->port_name, .pin = led->pin,
			.direction = GPIO_DIRECTION_OUTPUT,.logic = led->led_status
		};
		DIO_pin_initialize(&pin_obj);
	}
	return ret;
}

EN_errorReturn_t LED_turn_on(const ST_led_t *led){
	EN_errorReturn_t ret = E_OK;
	if(NULL == led){
		ret = E_NOT_OK;
	}
	else{
		ST_Pin_Config_t pin_obj = { .port = led->port_name,.pin = led->pin,
			.direction = GPIO_DIRECTION_OUTPUT,.logic = led->led_status
		};
		DIO_pin_write_logic(&pin_obj, GPIO_HIGH);
	}
	return ret;
}

EN_errorReturn_t LED_turn_off(const ST_led_t *led){
	EN_errorReturn_t ret = E_OK;
	if(NULL == led){
		ret = E_NOT_OK;
	}
	else{
		ST_Pin_Config_t pin_obj = { .port = led->port_name,.pin = led->pin,
			.direction = GPIO_DIRECTION_OUTPUT,.logic = led->led_status
		};
		DIO_pin_write_logic(&pin_obj, GPIO_LOW);
	}
	return ret;
}

EN_errorReturn_t LED_toggle(const ST_led_t *led){
	EN_errorReturn_t ret = E_OK;
	if(NULL == led){
		ret = E_NOT_OK;
	}
	else{
		ST_Pin_Config_t pin_obj = { .port = led->port_name,.pin = led->pin,
			.direction = GPIO_DIRECTION_OUTPUT,.logic = led->led_status
		};
		DIO_pin_toggle_logic(&pin_obj);
	}
	return ret;
}



/*
void dely_5s_2LED(uint8_t pinNumber_1,uint8_t pinNumber_2,uint8_t portNumber_1,uint8_t portNumber_2)
{
	CLR_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);
	
	//SET PRESCALLER
	startTimer(T0,8);
	
	//initial value
	TCNT0 = 56;
	
	for (uint16_t i=0;  i <25000; i++)
	{
		while(TCNT0);
		if((i % 2500) == 0) 
		{
			LED_toggle(portNumber_1,pinNumber_1);
			LED_toggle(portNumber_2,pinNumber_2);	
		}
		TCNT0 = 56;
	}
	
}
*/