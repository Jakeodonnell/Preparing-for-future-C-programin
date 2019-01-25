/*
 * DACINIT.c
 *
 * Created: 2018-10-03 13:59:34
 *  Author: jake och stefan
 */ 
#include <asf.h>
#include "daccinit.h"


int daccInit()
{
	int allOK = 1;
	pmc_enable_periph_clk(ID_DACC); /* DACC clock should
	be enabled before using it. */
	dacc_reset(DACC); /* Reset DACC */
	dacc_set_transfer_mode(DACC, 0); /* Configure FIFO
	transfer mode */
	dacc_set_timing(DACC,1,1,0); /* 1 is shortest refresh
	period, 1 max. speed, 0 startup time */
	dacc_set_channel_selection(DACC,1); /* Disable
	flexible (TAG) mode and select channel 0 for DAC
	output */
	allOK = dacc_enable_channel(DACC, 1); /* Enable DAC
	channel 0 */
	return allOK;
}