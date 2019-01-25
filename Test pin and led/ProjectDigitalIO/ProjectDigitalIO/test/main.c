 
	 /**
	 * /file testDigitalIO_runner.c
	 * /author Ulrik Eklund
	 * /date 2015-06-09
	 * /brief Test runner program for test of the digital outputs on an Arduino Due board.
	 *
	 * This project provides a basic set of tests for functions controlling the digital outputs on
	 * Arduino Due board, using Unity as the test framework (https://github.com/ThrowTheSwitch/Unity).
	 *
	 * This file is the main() function tha calls all the relvant tests, which in turn calls the
	 * functions to be developed.
	 *
	 * This program does not rely on the hardware API (ASF) provided by Atmel for the I/O drivers,
	 * but it relies on ASF Atmel Software Framework (ASF) for communication to the terminal via USB.
	 */

	 #include <inttypes.h>	/* See http://en.wikipedia.org/wiki/C_data_types#Fixed-width_integer_types for more info */
	 #include <setjmp.h>
	 // #include <stdio.h>
	 #include <stdio_serial.h>
	 #include <asf.h>
	 #include "conf_board.h"
	 #include "../unity/unity.h"	/* Contains declarations of all functions that Unity provides */
	 #include "../test/test_digitalIO.h" /* Contains declarations of the six tests for this exercise */
	 #include "digitalIO.h"

	 static void configure_console(void)
	 /* Enables feedback through the USB-cable back to terminal within Atmel Studio */
	 {
		 const usart_serial_options_t uart_serial_options = {
			 .baudrate = CONF_UART_BAUDRATE,
			 .paritytype = CONF_UART_PARITY
		 };

		 /* Configure console UART. */
		 sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
		 stdio_serial_init(CONF_UART, &uart_serial_options);
		 
		 printf("Console ready\n");
		 printf("=============\n");
	 }


	 int main(void)
	 {
		 /* Insert system clock initialization code here (sysclk_init()). */
		 sysclk_init();
		 board_init();

		 /* Initialize the console UART used from within Atmel Studio*/
		 configure_console();
		 
		 /* From here on the program uses the Unity testing framework */
		 UnityBegin("../test/testDigitalIO.c");
		 
		 /* Run the tests from the test-file */
		 RUN_TEST(test_digitalDuePin13InitialiseProperly, 10);
		 
		 /* Uncomment the rest of the tests, one at a time, when you have written or modified code so that you pass the previous test */
		 RUN_TEST(test_digitalDuePin13IsSet, 15);
		 RUN_TEST(test_digitalDuePin13IsCleared, 18);
		 //
		 RUN_TEST(test_digitalDuePin22InitialiseProperly, 20);
		 RUN_TEST(test_digitalDuePin22IsSet, 25);
		 RUN_TEST(test_digitalDuePin22IsCleared, 28);
		 //
		 RUN_TEST(test_digitalDuePin13And22InitialiseProperly, 30);
		 RUN_TEST(test_digitalDuePin13And22IsSet, 35);
		 RUN_TEST(test_digitalDuePin13isClearedAnd22IsSet, 38);

		 UnityEnd();
		 
		 pinMode(13, OUTPUT);
		 int i; /* loop counter for the delay */ 
		
		 volatile int j; /* Dummy volatile to prevent compiler optimising the variable a way */ 
		// int delay_length = 400000; /* variable determining the length of a delay */
		 while(1)  {
			 j=0;    
			 digitalWrite(13, 1); 
			// for (i=0; i<delay_length; i++)  {
			// j++;       }
			 digitalWrite(13, 0); 
			 //for (i=0; i<delay_length; i++)    {
			 //j++;    }
		 } 
		 /* ioport_enable_pin(PIO_PB27_IDX);
		  ioport_set_pin_dir(PIO_PB27_IDX, IOPORT_DIR_OUTPUT);
		  ioport_init();
		 while(1) {
			 ioport_set_pin_level(PIO_PB27_IDX, HIGH);
			 ioport_set_pin_level(PIO_PB27_IDX, LOW);
		 }*/
		 return 0;
		}
