/*
 * adcFunctions.c
 *
 * Created: 2015-09-10 12:00:39
 *  Author: Uek
 */ 

#include <inttypes.h>	/* See http://en.wikipedia.org/wiki/C_data_types#Fixed-width_integer_types for more info */
#include <asf.h>
#include "../unity/unity.h"
#include "../src/adcFunctions.h"
#include "test_adcFunctions.h"

uint32_t *const p_ADC_CHSR = (uint32_t *) (ADC_BASE_ADDRESS + 0x18U);
uint32_t *const p_PMC_PCSR1 = (uint32_t *) 0x400E0708U;


void test_ADConverterInitialisesProperly(void)
{
	analogInit(0);	/* Analog In 0 */
	TEST_ASSERT_BIT_HIGH_MESSAGE(5, *p_PMC_PCSR1, "PMC has not enabled the peripheral ADC clock");	/* Asserting the PMC manager has activated the ADC clock */
	TEST_ASSERT_BIT_HIGH_MESSAGE(7, *p_ADC_CHSR, "ADC channel 7 is not enabled");	/* Asserting that ADC channel 7 is enabled */
}

void test_ADConverterReadsValueWithNoButtonPressed(void)
{
  TEST_ASSERT_UINT32_WITHIN(400, 3800, analogRead(0));

}
