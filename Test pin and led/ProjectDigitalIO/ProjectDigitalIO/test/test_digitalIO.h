/*
 * test_digitalIO.h
 *
 * Created: 2015-06-09 14:26:27
 *  Author: Ulrik
 */ 


#ifndef TEST_DIGITALIO_H_
#define TEST_DIGITALIO_H_

void setUp(void);
void tearDown(void);
void resetTest(void);

void test_digitalDuePin13InitialiseProperly(void);
void test_digitalDuePin13IsSet(void);
void test_digitalDuePin13IsCleared(void);

void test_digitalDuePin22InitialiseProperly(void);
void test_digitalDuePin22IsSet(void);
void test_digitalDuePin22IsCleared(void);

void test_digitalDuePin13And22InitialiseProperly(void);
void test_digitalDuePin13And22IsSet(void);
void test_digitalDuePin13isClearedAnd22IsSet(void);

#endif /* TEST_DIGITALIO_H_ */

