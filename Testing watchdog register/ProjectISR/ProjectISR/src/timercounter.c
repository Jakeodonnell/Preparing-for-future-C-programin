/*
 * tc.c
 *
 * Created: 2018-10-03 14:27:43
 *  Author: jake och stefan
 */ 
#include <asf.h>
#include "timercounter.h"
/*USING: TC:TC1 CHAN:0 NVIC irq: TC3_IRQn PMC id: ID_TC3 */
#define p22		IOPORT_CREATE_PIN(PIOB, 26)
volatile uint8_t next = 0;
int value[] = {1700, 2021, 2293, 2476, 2690, 2476, 2293, 2021, 1700, 1378, 1105, 923, 860, 920, 1105, 1378};
int freq = 970205 % 1999 + 991;

void configure_tc(void)
{
	uint32_t ul_div;
	uint32_t ul_tcclks;
	uint32_t ul_sysclk = sysclk_get_cpu_hz();
	/* Configure power management of timer clocks */
	pmc_enable_periph_clk(ID_TC3);
	/* Configure TC for a 44,1kHz frequency and trigger
	on RC compare. */
	tc_find_mck_divisor(1681, ul_sysclk, &ul_div,
	&ul_tcclks, ul_sysclk);
	tc_init(TC1, 0, ul_tcclks | TC_CMR_CPCTRG);
	tc_write_rc(TC1, 0, (ul_sysclk / ul_div) / 1681);
	/* Configure and enable interrupt on RC compare */
	NVIC_EnableIRQ(TC3_IRQn);
	tc_enable_interrupt(TC1, 0, TC_IER_CPCS);
	tc_start(TC1, 0);
	ioport_init();
	ioport_set_pin_dir(p22, IOPORT_DIR_OUTPUT);
}

uint32_t nextval(){
	next = ++next % 16;
	return(uint32_t)value[next];
}

void TC3_Handler() {
	ioport_set_pin_level(p22, true);
	tc_get_status(TC1, 0);
	uint32_t value = nextval();
	dacc_write_conversion_data(DACC, value);
	ioport_set_pin_level(p22, false);
}