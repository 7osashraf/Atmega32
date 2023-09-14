/*
 * adc.c
 *
 * Created: 9/14/2023 2:01:54 AM
 *  Author: ENG HOSAM
 */ 

#include "adc.h"

static void (*(ADC_InterruptCallBack))(void);


EN_errorReturn_t ADC_Init(const ST_adcConfig_t *adc)
{
	EN_errorReturn_t ret = E_OK;
	if(NULL == adc)
	{
		ret = E_NOT_OK;
	}
	else
	{
		// Configure the voltage reference and left/right adjust
		ADMUX = (adc->voltageRef << 6) | (adc->dataAdjust << 5);

		// Set the auto-triggering mode and source
		if (adc->autoTrigger == ADC_ENABLE_AUTO_TRIGGER) {
			SFIOR |= (1 << ADTS2) | (adc->autoTriggerSource << 5);
			} else {
			SFIOR &= ~((1 << ADTS0) | (1 << ADTS1) | (1 << ADTS2));
		}

		// Set the channel and prescaler
		ADMUX |= adc->channel;
		ADCSRA = (ADCSRA & 0xF8) | (adc->prescaler);

		// Enable ADC and disable ADC interrupt
		SET_BIT(ADCSRA,ADEN);
		CLEAR_BIT(ADCSRA,ADIE);
	}
	return ret;
}


EN_errorReturn_t ADC_Read(uint16* value_conversion)
{
	EN_errorReturn_t ret=E_OK;
	// Start the conversion
	ADCSRA |= (1 << ADSC);

	// Wait for the conversion to complete
	while (ADCSRA & (1 << ADSC));

	// Read the result (right-adjusted)
	*value_conversion = ADC;

	return ret;
}


EN_errorReturn_t ADC_Interrupt_Enable(){
	// Enable ADC interrupt
	SET_BIT(ADCSRA, ADIE);
	return E_OK;
}
EN_errorReturn_t ADC_Interrupt_Disable(){
	// Disable ADC interrupt
	CLEAR_BIT(ADCSRA, ADIE);
	return E_OK;
}