/*
 * test_LCDFunctions.c
 *
 * Created: 2015-06-09 10:37:43
 *  Author: Ulrik
 */ 

#include <inttypes.h>	/* See http://en.wikipedia.org/wiki/C_data_types#Fixed-width_integer_types for more info */
#include <asf.h>
#include "../unity/unity.h"
#include "../src/LCDFunctions.h"
#include "../src/DelayFunctions.h"
#include "test_lcdFunctions.h"

uint32_t *const p_PIOC_ODSR = (uint32_t *) (PIOC_BASE_ADDRESS+0x0038U);	/* defines the address for status (values) of the output pins of the B register  */

void test_initialisatinOfTheLCD(void)
{
	TEST_ASSERT_FALSE(lcdInit());
	TEST_ASSERT_BIT_LOW(22, *p_PIOC_ODSR);	/* The RS bit on the LCD should be set to low since it is an initiation */
	TEST_ASSERT_BIT_LOW(21, *p_PIOC_ODSR);	/* The Enable bit on the LCD should be set to low to indicate that all data has been written  */
	/* We cannot test the actual value of the last character shown on the LCD, 
	   but we can test that the output to the LCD on PC23-PC26 is what we expect */
	TEST_ASSERT_BITS(LCD_mask_D4_D7, 0b00000111100000000000000000000000, *p_PIOC_ODSR);	/* Display on, cursor on, blinking on */
}

void test_writingCharactersToTheLCD(void)
{
	/* Write a number of consecutive characters on the LCD display to show that the program works */
	/* We cannot test the actual value of the last character shown on the LCD, 
	   but we can test that the output to the LCD on PC23-PC26 is what we expect for each character */

	TEST_ASSERT_FALSE(lcdWrite(0x68, HIGH));	/* 0x68 is hex for ASCII symbol 'h' */
	TEST_ASSERT_BIT_HIGH(22, *p_PIOC_ODSR);		/* The RS bit on the LCD should be set to high since it is writing a character to the display */
	TEST_ASSERT_BIT_LOW(21, *p_PIOC_ODSR);		/* The Enable bit on the LCD should be set to low to indicate that all data has been written  */
	TEST_ASSERT_BITS(LCD_mask_D4_D7, (0b0001<<23), *p_PIOC_ODSR);	/* Last 4 bits in reverse order */

	TEST_ASSERT_FALSE(lcdWrite((uint8_t) 101, HIGH));	/* 101 is decimal and needs to have an explicit cast to a single byte */
	TEST_ASSERT_BIT_HIGH(22, *p_PIOC_ODSR);
	TEST_ASSERT_BIT_LOW(21, *p_PIOC_ODSR);
	//TEST_ASSERT_BITS(LCD_mask_D4_D7, 0b00000101000000000000000000000000, *p_PIOC_ODSR);
	TEST_ASSERT_BITS(LCD_mask_D4_D7, (0b1010<<23), *p_PIOC_ODSR);

	TEST_ASSERT_FALSE(lcdWrite(0x6C, HIGH));
	TEST_ASSERT_BIT_HIGH(22, *p_PIOC_ODSR);
	TEST_ASSERT_BIT_LOW(21, *p_PIOC_ODSR);
	TEST_ASSERT_BITS(LCD_mask_D4_D7, (0b0011<<23), *p_PIOC_ODSR);

	TEST_ASSERT_FALSE(lcdWrite(0x6C, HIGH));
	TEST_ASSERT_BIT_HIGH(22, *p_PIOC_ODSR);
	TEST_ASSERT_BIT_LOW(21, *p_PIOC_ODSR);
	TEST_ASSERT_BITS(LCD_mask_D4_D7, (0b0011<<23), *p_PIOC_ODSR);

	TEST_ASSERT_FALSE(lcdWrite(0x6F, HIGH));
	TEST_ASSERT_BIT_HIGH(22, *p_PIOC_ODSR);
	TEST_ASSERT_BIT_LOW(21, *p_PIOC_ODSR);	
	TEST_ASSERT_BITS(LCD_mask_D4_D7, (0b1111<<23), *p_PIOC_ODSR);

	TEST_ASSERT_FALSE(lcdWrite(0x2C, HIGH));
	TEST_ASSERT_BIT_HIGH(22, *p_PIOC_ODSR);
	TEST_ASSERT_BIT_LOW(21, *p_PIOC_ODSR);
	TEST_ASSERT_BITS(LCD_mask_D4_D7, (0b0011<<23), *p_PIOC_ODSR);

	TEST_ASSERT_FALSE(lcdWrite(0x20, HIGH));
	TEST_ASSERT_BIT_HIGH(22, *p_PIOC_ODSR);
	TEST_ASSERT_BIT_LOW(21, *p_PIOC_ODSR);
	TEST_ASSERT_BITS(LCD_mask_D4_D7, (0b0000<<23), *p_PIOC_ODSR);

	lcdWrite('w', HIGH);
	TEST_ASSERT_BIT_HIGH(22, *p_PIOC_ODSR);
	TEST_ASSERT_BIT_LOW(21, *p_PIOC_ODSR);
	TEST_ASSERT_BITS(LCD_mask_D4_D7, (0b1110<<23), *p_PIOC_ODSR);

	TEST_ASSERT_FALSE(lcdWrite('o', HIGH));
	TEST_ASSERT_BIT_HIGH(22, *p_PIOC_ODSR);
	TEST_ASSERT_BIT_LOW(21, *p_PIOC_ODSR);
	TEST_ASSERT_BITS(LCD_mask_D4_D7, (0b1111<<23), *p_PIOC_ODSR);

	TEST_ASSERT_FALSE(lcdWrite('r', HIGH));
	TEST_ASSERT_BIT_HIGH(22, *p_PIOC_ODSR);
	TEST_ASSERT_BIT_LOW(21, *p_PIOC_ODSR);
	TEST_ASSERT_BITS(LCD_mask_D4_D7, (0b0100<<23), *p_PIOC_ODSR);

	TEST_ASSERT_FALSE(lcdWrite('l', HIGH));
	TEST_ASSERT_BIT_HIGH(22, *p_PIOC_ODSR);
	TEST_ASSERT_BIT_LOW(21, *p_PIOC_ODSR);
	TEST_ASSERT_BITS(LCD_mask_D4_D7, (0b0011<<23), *p_PIOC_ODSR);

	TEST_ASSERT_FALSE(lcdWrite('d', HIGH));
	TEST_ASSERT_BIT_HIGH(22, *p_PIOC_ODSR);
	TEST_ASSERT_BIT_LOW(21, *p_PIOC_ODSR);
	TEST_ASSERT_BITS(LCD_mask_D4_D7, (0b0010<<23), *p_PIOC_ODSR);
	
}

void test_clearingTheLCDDisplay(void)
{
	//delayMicroseconds(1000000);	/* Just to make sure that the previous message on the LCD can be read */
	
	/* Assert that the last bits written are correct */
	TEST_ASSERT_FALSE(lcdClearDisplay());
	TEST_ASSERT_BIT_LOW(22, *p_PIOC_ODSR);	/* The RS bit on the LCD should be set to low since it is an initiation */
	TEST_ASSERT_BIT_LOW(21, *p_PIOC_ODSR);	/* The Enable bit on the LCD should be set to low to indicate that all data has been written  */
	/* We cannot test the actual value of the last character shown on the LCD, 
	   but we can test that the output to the LCD on PC23-PC26 is what we expect */
	TEST_ASSERT_BITS(LCD_mask_D4_D7, (0b1000<<23), *p_PIOC_ODSR);
}

