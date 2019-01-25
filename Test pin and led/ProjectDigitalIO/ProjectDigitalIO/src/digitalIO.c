/*
 * digitalIO.c
 *
 * Created: 2015-06-10 15:11:18
 *  Author: Ulrik
 */ 

#include <inttypes.h>	/* See http://en.wikipedia.org/wiki/C_data_types#Fixed-width_integer_types for more info */
#include <asf.h>		/* Only needed to get the definitions for HIGH and LOW */
#include "digitalIO.h"
#include <stdio.h>

#define PIOB_BASE_ADDRESS 0x400E1000U
void pinMode(int pinNumber, mode_definition mode)
{
	uint32_t *const p_PIOB_PER = (uint32_t *) (PIOB_BASE_ADDRESS+0x0000U);	/* defines the address for enabling the parallel Input/output B register */
	uint32_t *const p_PIOB_OER = (uint32_t *) (PIOB_BASE_ADDRESS+0x0010U);	/* defines the address for enabling the parallel output B register */

	if (mode == OUTPUT)	/* You only have to program a function that cares about OUTPUT, and does nothing for the other values 
	
	http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-11057-32-bit-Cortex-M3-Microcontroller-SAM3X-SAM3A_Datasheet.pdf sida 31 (minnes celler adress)
	https://www.arduino.cc/en/Hacking/PinMappingSAM3X (pin mapping due)
	*/
	{
		/* Write code here */
		if(pinNumber == 13){
			*p_PIOB_OER |= (1 << 27);
			*p_PIOB_PER |= (1 << 27);
		}
		
		else if(pinNumber == 22) {
			*p_PIOB_OER |= (1 << 26);
			*p_PIOB_PER |= (1 << 26);
		}
	}
	else
	{
		/* Do nothing */
	}
}

void digitalWrite(int pinNumber, int value)
{
	uint32_t *const p_PIOB_SODR = (uint32_t *) (PIOB_BASE_ADDRESS+0x0030U);	/* defines the address for setting the output pins of the B register */
	uint32_t *const p_PIOB_CODR = (uint32_t *) (PIOB_BASE_ADDRESS+0x0034U);	/* defines the address for clearing the output pins of the B register  */

	if (value == HIGH)
	{
		if(pinNumber == 13){
			*p_PIOB_SODR |= (1 << 27);
		}
		
		else if(pinNumber == 22){
			*p_PIOB_SODR |= (1 << 26);
		}
		
	
	}
	else if (value == LOW)
	{
		if(pinNumber == 13) {
			*p_PIOB_CODR |= (1 << 27);
		}
		
		else if(pinNumber == 22) {
			*p_PIOB_CODR |= (1 << 26);
		}
	}
	else
	{
		/* Something is wrong */
	}
}
