/*
 * adcFunctions.c
 *
 * Created: 2015-06-16 09:00:18
 *  Author: To Be Decided
 */ 

#include <inttypes.h>
#include <asf.h>
#include "adcFunctions.h"

int analogInit(int pinNumber)
{
	/* 
	 * The pin number is the analog input pin on the DUe board, see http://www.arduino.cc/en/Hacking/PinMappingSAM3X
	 * Obviously it starts at analog 0 which is equivalent to the analog input on PA16
	 * so you need to figure out which AD channel this corresponds to
	 *
	 * See code example http://asf.atmel.com/docs/latest/sam.drivers.adc.adc_example.arduino_due_x/html/sam_adc_quickstart.html
	 * It is assumed that the AD-converter is using 12 bits
	 */
	
	pmc_enable_periph_clk(ID_ADC);	/* power the clock for the ADC with pmc_enable_periph_clk(ID_ADC) */
	
	adc_init(ADC, sysclk_get_main_hz(), sysclk_get_main_hz()/4, 8);

	adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);

	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);

	adc_enable_channel(ADC, ADC_CHANNEL_7);

	adc_enable_interrupt(ADC, ADC_IER_DRDY);

	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);

	
	/* Write code here */
	
	adc_start(ADC);

	return 0;	/* if everything is ok */
}

uint32_t analogRead(int pinNumber)
{
	/* Write code here */
	uint32_t result = adc_get_latest_value(ADC);
	adc_start(ADC);
	
	
	return result;	/* Replace with actual value read from A/D input*/
}