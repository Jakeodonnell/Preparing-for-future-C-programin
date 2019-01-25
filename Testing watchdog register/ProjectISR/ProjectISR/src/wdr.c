/*
 * CFile1.c
 *
 * Created: 2018-10-03 12:54:32
 *  Author: jake och stefan
 */ 
#include <inttypes.h>	/* See http://en.wikipedia.org/wiki/C_data_types#Fixed-width_integer_types for more info */
#include <asf.h>
#include "Interrupt.h"
#include <stdlib.h>
#include <stdio.h>


int watchdogReload(void){
	WDT->WDT_CR |= ((0xA5 << 24) + 0x1);
	}