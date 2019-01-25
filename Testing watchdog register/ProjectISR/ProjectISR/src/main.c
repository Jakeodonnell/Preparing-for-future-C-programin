/**
 * @file main.c
 *
 * @brief main file initiating all necessary hardware and then blinking LED
 *
 * @author Uek
 *
 * @date 2015-12-17
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#include "asf.h"

#include "digitalIO.h" /* Functions developed in Task1501a */
#include "DelayFunctions.h"
#include "wdr.h"
#include "daccinit.h"
#include "timercounter.h"

#define CONF_BOARD_KEEP_WATCHDOG_AT_INIT 1		//to keep watchdog activated at board_init

int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).
	sysclk_init();
	board_init();
	delayInit();
	daccInit();
	configure_tc();
	pinMode(13, OUTPUT);
	// Insert application code here, after the board has been initialized.
	while(1)	/* repeat blink to infinity */
	{
		watchdogReload();
		 ioport_set_pin_level(PIO_PB27_IDX, HIGH);
	
		//digitalWrite(13, 1); /* sets a bit of I/O port B to high */
		// printf("1");
		delayMicroseconds(750000);
		 ioport_set_pin_level(PIO_PB27_IDX, LOW);
		//digitalWrite(13, 0); /* clears a bit of I/O port B */
		// printf("0");
		delayMicroseconds(750000);
	}
}
