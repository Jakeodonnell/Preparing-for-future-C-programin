/*
 * test_delayFunctions.c
 *
 * Created: 2015-06-09 10:37:43
 *  Author: Ulrik
 */ 

#include <inttypes.h>	/* See http://en.wikipedia.org/wiki/C_data_types#Fixed-width_integer_types for more info */
#include <asf.h>
#include "../unity/unity.h"

#include "../src/DelayFunctions.h"
#include "../test/test_delayFunctions.h"

/* setting up the memory addresses of the Timer counter */
#define TC0_BASE_ADDRESS 0x40080000U
uint32_t *const p_TC0_CMR0 = (uint32_t *) (TC0_BASE_ADDRESS + 0x00U+0*0x40U+0x04U);	/* defines the address for channel mode of the TC0 status register for timer channel 0  */
uint32_t *const p_TC0_CV0 = (uint32_t *) (TC0_BASE_ADDRESS + 0x00U+0*0x40U+0x10U);	/* defines the address for runnning counter value of the TC0 status register for timer channel 0  */
uint32_t *const p_TC0_SR0 = (uint32_t *) (TC0_BASE_ADDRESS + 0x00U+0*0x40U+0x20U);	/* defines the address for status the TC0 status register for timer channel 0  */

void test_delayTimerIsInitialisedProperly(void)
{
	delayInit();
	TEST_ASSERT_BITS(0x0111, 0x00U, *p_TC0_CMR0);	/* Check that the proper timer and channel is enabled */
}

void test_delayCountsProperly(void)
{
	/* Note that it is difficult to write good automated tests for the timer counter */
	//delayInit();	/* Checked in the previous test */
	
	delayMicroseconds(1);
	/* when the timer has stopped check that the counter has the right value 
	 * the timer resets when it starts, not when it stops */
	TEST_ASSERT_BIT_LOW(16, *p_TC0_SR0);				/* Check that the timer clock is stopped, unfortuantely we can't test that it is running */
	TEST_ASSERT_UINT32_WITHIN(40U, 42U, *p_TC0_CV0);	/* It takes appr. 20 clock cycles to read and compare the value */
		
	delayMicroseconds(200);
	TEST_ASSERT_BIT_LOW(16, *p_TC0_SR0);				/* Check that the timer clock is stopped */
	TEST_ASSERT_UINT32_WITHIN(40U, 8420U, *p_TC0_CV0);	/* It takes appr. 20 clock cycles to read and compare the value */
}