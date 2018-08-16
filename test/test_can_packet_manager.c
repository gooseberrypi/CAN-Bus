//#define FULL_TEST

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

/***************************************************************************************************
 * Run through 0x0000 to 0xFFFF as ID options and verify that it will correctly report the status
 * and set the ID.
 ***************************************************************************************************/
void test_can_pm_set_id(void)
{
	CAN_message_t can_pm_set_id_test_message;
	can_packet_manager_status status_test_var;
	uint32_t id_max_value;

#ifdef FULL_TEST
	id_max_value= 0xFFFFFFFF;
#else
	id_max_value= 0xFFFFFF;
#endif

	for(uint32_t id = 0; id < id_max_value; id++)
	{
		status_test_var = can_pm_set_id(&can_pm_set_id_test_message, id);
		TEST_ASSERT_EQUAL_MESSAGE(id, can_pm_set_id_test_message.id, "ID is not as expected");
		TEST_ASSERT_EQUAL_MESSAGE(can_pm_success, status_test_var, "Status message is not as expected");
	}
}

