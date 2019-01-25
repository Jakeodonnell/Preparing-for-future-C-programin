/*
 * test_buttons.c
 *
 * Created: 2015-06-09 10:37:43
 *  Author: Ulrik
 */ 

#include <inttypes.h>	/* See http://en.wikipedia.org/wiki/C_data_types#Fixed-width_integer_types for more info */
#include <asf.h>
#include "../unity/unity.h"
#include "../src/buttons.h"
#include "test_buttons.h"

void test_noButtonIsPressed(void)
{
	TEST_ASSERT_TRUE(readLCDbutton() == btnNONE);
}
