/*
 * adc.h
 *
 * Created: 9/14/2023 2:01:45 AM
 *  Author: ENG HOSAM
 */ 


#ifndef ADC_H_
#define ADC_H_

/* ------------------Includes------------------*/
#include "avr/io.h"
#include "../../utilites/types.h"
#include "../../utilites/MemoryMap.h"
#include "../../MCAL/DIO/dio.h"

/* ------------------Macro Declarations------------------*/
#define ADC_INTERNAL_VOLTAGE_REV_OFF     0X00
#define ADC_VCC_VOLTAGE_REV              0X01
#define ADC_25_INTERNAL_VOLTAGE_REV      0X03

#define ADC_FREE_RUNNING_MODE            0X00
#define ADC_ANALOG_COMPARTOR             0X01
#define ADC_EXTERNAL_INTERRUPT_REQ       0X02
#define ADC_TMR0_COUNTER_COMPARE_MATCH   0X03
#define ADC_TMR0_COUNTER_OVERFLOW        0X04
#define ADC_TMR_COUNTER_COMPARE_MATCH    0X05
#define ADC_TMR1_COUNTER_OVERFLOW        0X06
#define ADC_TMR1_COUNTER_CAPTURE_EVENT   0X07

#define ADC_AUTO_START_DISABLE			 0
#define ADC_AUTO_START_ENABLE            1

#define ADC_READ_RIGHT_ADJUST            0X00
#define ADC_READ_LEFT_ADJUST             0X01


/* ------------------Macro Function Declarations------------------*/
#define ADC_SET_VOLTAGE_REV(REV)			(ADMUX = (ADMUX & 0xC0) | (REF << 6))
#define ADC_SET_PRESCALER(PRESCALER)		(ADCSRA = (ADCSRA & 0xF8) | (PRESCALER))
#define ADC_SET_READ_ADJUST(ADJUST)        (ADMUX = (ADMUX & 0xDF) | (ADJUST << 5))
#define ADC_SELECT_AUTO_TRIGGER(TRIGGER)   (ADCSRA = (ADCSRA & 0xDF) | (TRIGGER << 5))

/* ------------------Data Type Declarations------------------*/
typedef enum
{
	ADC_CHANNLE_0 = 0,
	ADC_CHANNLE_1,
	ADC_CHANNLE_2,
	ADC_CHANNLE_3,
	ADC_CHANNLE_4,
	ADC_CHANNLE_5,
	ADC_CHANNLE_6,
	ADC_CHANNLE_7
}EN_adcChannel_t;


typedef enum {
	ADC_PRESCALER_2 = 0x01,
	ADC_PRESCALER_4 = 0x02,
	ADC_PRESCALER_8 = 0x03,
	ADC_PRESCALER_16 = 0x04,
	ADC_PRESCALER_32 = 0x05,
	ADC_PRESCALER_64 = 0x06,
	ADC_PRESCALER_128 = 0x07
} EN_adcPrescaler_t;

typedef enum {
	ADC_LEFT_ADJUST = 0x01,
	ADC_RIGHT_ADJUST = 0x00
} EN_adcDataAdjust_t;

typedef enum {
	ADC_DISABLE_AUTO_TRIGGER = 0x00,
	ADC_ENABLE_AUTO_TRIGGER = 0x01
} EN_adcAutoTrigger_t;

typedef struct {
	uint8_t voltageRef;
	uint8_t dataAdjust;
	uint8_t autoTrigger;
	uint8_t autoTriggerSource;
	uint8_t channel;
	uint8_t prescaler;
} ST_adcConfig_t;

/* ------------------Software Interface Declarations------------------*/
EN_errorReturn_t ADC_Init(const ST_adcConfig_t *adc);
EN_errorReturn_t ADC_Read(uint16* value_conversion);
EN_errorReturn_t ADC_Interrupt_Enable(void);
EN_errorReturn_t ADC_Interrupt_Disable(void);
#endif /* ADC_H_ */