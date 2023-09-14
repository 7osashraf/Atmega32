/*
 * dio.h
 *
 * Created: 10/11/2022 8:07:00 AM
 *  Author: ENG HOSAM
 */ 


#ifndef DIO_H_
#define DIO_H_

/* ------------------Includes------------------*/
#include "avr/io.h"
#include "../../utilites/bit_maths.h"
#include "../../utilites/returnError.h"
#include "../../utilites/types.h"

/* ------------------Macro Declarations------------------*/
//CPU freq
#define F_CPU 8000000UL

#define BIT_MASK				(uint8)1
#define PORT_PIN_MAX_NUMBER     8
#define PORT_MAX_NUMBER         5

#define PORTC_MASK              0xFF

/* ------------------Macro Function Declarations------------------*/
#define HWREG8(_X)      (*((volatile uint8 *)(_X)))

#define SET_BIT(REG, BIT_POSN)       (REG |= (BIT_MASK << BIT_POSN))
#define CLEAR_BIT(REG, BIT_POSN)     (REG &= ~(BIT_MASK << BIT_POSN))
#define TOGGLE_BIT(REG, BIT_POSN)    (REG ^= (BIT_MASK << BIT_POSN))
#define READ_BIT(REG, BIT_POSN)      ((REG >> BIT_POSN) & BIT_MASK)

/* ------------------Data Type Declarations------------------*/
typedef enum{
	GPIO_LOW = 0,
	GPIO_HIGH
}EN_Logic_t;

typedef enum{
	GPIO_DIRECTION_OUTPUT = 0,
	GPIO_DIRECTION_INPUT
}EN_Direction_t;

typedef enum{
	GPIO_PIN0 = 0,
	GPIO_PIN1,
	GPIO_PIN2,
	GPIO_PIN3,
	GPIO_PIN4,
	GPIO_PIN5,
	GPIO_PIN6,
	GPIO_PIN7,
}EN_Pin_Index_t;

typedef enum{
	PORTA_INDEX = 0,
	PORTB_INDEX,
	PORTC_INDEX,
	PORTD_INDEX
}EN_Port_Index_t;

typedef struct{
	uint8 port		: 3;          /* @ref port_index_t */
	uint8 pin		: 3;           /* @ref pin_index_t */
	uint8 direction : 1;     /* @ref direction_t */
	uint8 logic		: 1;         /* @ref logic_t */
}ST_Pin_Config_t;

/* ------------------Software Interface Declarations------------------*/

EN_errorReturn_t DIO_pin_direction_init(const ST_Pin_Config_t *_pin_config);
EN_errorReturn_t DIO_pin_get_direction_statues(const ST_Pin_Config_t *_pin_config, EN_Direction_t *direction_statues);
EN_errorReturn_t DIO_pin_write_logic(const ST_Pin_Config_t *_pin_config, EN_Logic_t logic);
EN_errorReturn_t DIO_pin_read_logic(const ST_Pin_Config_t *_pin_config, EN_Logic_t *logic);
EN_errorReturn_t DIO_pin_toggle_logic(const ST_Pin_Config_t *_pin_config);
EN_errorReturn_t DIO_pin_initialize(const ST_Pin_Config_t *_pin_config);

EN_errorReturn_t DIO_port_direction_initialize(EN_Port_Index_t port,uint8 direction);
EN_errorReturn_t DIO_port_get_direction_status(EN_Port_Index_t port,uint8 *direction_status);
EN_errorReturn_t DIO_port_write_logic(EN_Port_Index_t port,uint8 logic);
EN_errorReturn_t DIO_port_read_logic(EN_Port_Index_t port,uint8 *logic);
EN_errorReturn_t DIO_port_toggle_logic(EN_Port_Index_t port);





#endif /* DIO_H_ */