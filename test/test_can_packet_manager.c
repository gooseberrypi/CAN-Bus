#include "unity.h"
#include "mock_stm32f4xx_hal.h"
#include "can_packet_manager.h"


void setUp( void )
{
}

void tearDown( void )
{
}

/***************************************************************************************************
 * Run through every PID option and verify that it will correctly report if the PID is 1 byte or
 * 2 bytes.
 ***************************************************************************************************/
void test_get_PID_length(void)
{
	for(uint16_t pid = 0; pid < 0xFF; pid++)
	{
		TEST_ASSERT_EQUAL_MESSAGE(1U, get_PID_length(pid), "PID length not as expected");
	}
	for(uint16_t pid = 0x100; pid < 0xFFFF; pid++)
	{
		TEST_ASSERT_EQUAL_MESSAGE(2U, get_PID_length(pid), "PID length not as expected");
	}
}

