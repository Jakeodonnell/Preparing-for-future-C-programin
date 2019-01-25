/*
 * buttons.c
 *
 * Created: 2015-06-12 16:28:53
 * Author: To Be Decided
 */ 

#include "buttons.h"
#include "adcFunctions.h"	/* Must use the value from the ADC to figure out which button */
buttonType readLCDbutton(void)
{
	/* Write code here */
	
	volatile int adcValue = (int)analogRead(0);
	if (adcValue <1700 && adcValue > 1500){return btnDOWN;}
	if (adcValue > 2000 && adcValue < 2300){return btnLEFT;}
	if (adcValue > 3500 && adcValue < 3800){return btnNONE;}
	if (adcValue > 2900 && adcValue < 3400){return btnSELECT;}
	if (adcValue > 500 && adcValue<900){return btnUP;}
	
	return btnRIGHT;/* Change to actual value */
}