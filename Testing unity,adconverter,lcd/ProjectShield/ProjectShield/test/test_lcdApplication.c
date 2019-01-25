/*
 * test_lcdApplication.c
 *
 * Created: 2015-09-10 08:55:18
 *  Author: Uek
 */ 

#include <inttypes.h>	/* See http://en.wikipedia.org/wiki/C_data_types#Fixed-width_integer_types for more info */
#include <asf.h>
#include "../unity/unity.h"
#include "../src/lcdApplication.h"
#include "../src/buttons.h"	/* Just to get the buttonType defintion as an argument to lcdWriteButtonValue() */
#include "../src/LCDFunctions.h"	/* To get the definitions of the masking bits etc. */
#include "test_lcdApplication.h"

extern uint32_t *const p_PIOC_ODSR;	/* The pointer to the status (values) of the output pins of the B register, address is defined in test_lcdfunctions.c  */

void test_writing4DigitNumberOnTheLCDDisplay(void)
{
	lcdClearDisplay();	/* Can be used since lcdClearDisplay() is already developed and tested */
	TEST_ASSERT_FALSE(lcdWrite4DigitNumber(1357));
	TEST_ASSERT_BIT_HIGH(22, *p_PIOC_ODSR);	/* The RS bit on the LCD should be set to high since it is writing a character to the display */
	TEST_ASSERT_BIT_LOW(21, *p_PIOC_ODSR);	/* The Enable bit on the LCD should be set to low to indicate that all data has been written  */
	/* We cannot test the actual value of the last character shown on the LCD, 
	   but we can test that the output to the LCD on PC23-PC26 is what we expect */
	TEST_ASSERT_BITS(LCD_mask_D4_D7, (0b1110<<23), *p_PIOC_ODSR);
}

void test_writingAsciiStringOnTheLCDDisplay(void)
{
	lcdClearDisplay();
	TEST_ASSERT_FALSE(lcdWriteAsciiString("Test everything!"));
	TEST_ASSERT_BIT_HIGH(22, *p_PIOC_ODSR);	/* The RS bit on the LCD should be set to high since it is writing a character to the display */
	TEST_ASSERT_BIT_LOW(21, *p_PIOC_ODSR);	/* The Enable bit on the LCD should be set to low to indicate that all data has been written  */
	/* We cannot test the actual value of the last character shown on the LCD, 
	   but we can test that the output to the LCD on PC23-PC26 is what we expect */
	TEST_ASSERT_BITS(LCD_mask_D4_D7, (0b1000<<23), *p_PIOC_ODSR); /* last character shown should be a "!" */
}

void test_writingButtonOnTheLCDDisplay(void)
{
	lcdClearDisplay();
	TEST_ASSERT_FALSE(lcdWriteButtonValue(btnSELECT));
	TEST_ASSERT_BIT_HIGH(22, *p_PIOC_ODSR);	/* The RS bit on the LCD should be set to high since it is writing a character to the display */
	TEST_ASSERT_BIT_LOW(21, *p_PIOC_ODSR);	/* The Enable bit on the LCD should be set to low to indicate that all data has been written  */
	/* We cannot test the actual value of the last character shown on the LCD, 
	   but we can test that the output to the LCD on PC23-PC26 is what we expect */
	TEST_ASSERT_BITS(LCD_mask_D4_D7, (0b0010<<23), *p_PIOC_ODSR);	/* last character shown should be a "T" as in SELECT */
}