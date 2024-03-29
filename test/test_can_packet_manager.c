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
	TEST_ASSERT_EQUAL_MESSAGE(0U, get_PID_length(0x0000), "PID length not as expected");
	for(uint16_t pid = 1; pid < 0xFF; pid++)
	{
		TEST_ASSERT_EQUAL_MESSAGE(1U, get_PID_length(pid), "PID length not as expected");
	}
	for(uint16_t pid = 0x100; pid < 0xFFFF; pid++)
	{
		TEST_ASSERT_EQUAL_MESSAGE(2U, get_PID_length(pid), "PID length not as expected");
	}
}

void test_populate_PID_array_length(void)
{
	static pid_request_t pidReq[3] = {
			{ .pid = 0x0C, .mode = 0x01 },
			{ .pid = 0x0D, .mode = 0x01 },
			{ .pid = 0x220D, .mode = 0x01 }
	};
	populate_PID_array_length(pidReq, 3);
	TEST_ASSERT_EQUAL_MESSAGE(1, pidReq[0].pid_len, "PID1 length not as expected");
	TEST_ASSERT_EQUAL_MESSAGE(1, pidReq[1].pid_len, "PID2 length not as expected");
	TEST_ASSERT_EQUAL_MESSAGE(2, pidReq[2].pid_len, "PID3 length not as expected");
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

/***************************************************************************************************
 *
 ***************************************************************************************************/

void test_can_pm_generate_single_packet_message(void)
{
	int NUM_TEST_PACKETS = 4;
	CAN_message_t testPacket[NUM_TEST_PACKETS];
	pid_request_t pidReq[3] = {
			{ .pid = 0x0C, .mode = 0x01 },
			{ .pid = 0x0D, .mode = 0x01 },
			{ .pid = 0x220D, .mode = 0x01 }
	};
	uint8_t numIds = 1;

	uint8_t testMode = 0x01;

	can_pm_generate_message(testPacket, NUM_TEST_PACKETS, testMode , pidReq, 3);

	TEST_ASSERT_EQUAL(NUM_TEST_PACKETS, sizeof(testPacket)/sizeof(testPacket[0]));

	TEST_ASSERT_EQUAL_MESSAGE(5, testPacket[0].buf[0], "Length was not populated");
	TEST_ASSERT_EQUAL_MESSAGE(testMode, testPacket[0].buf[1], "Mode was not populated");
	TEST_ASSERT_EQUAL_MESSAGE(pidReq[0].pid, testPacket[0].buf[2], "PID1 was not populated");
	TEST_ASSERT_EQUAL_MESSAGE(pidReq[1].pid, testPacket[0].buf[3], "PID2 was not populated");
	TEST_ASSERT_EQUAL_MESSAGE(0x22, testPacket[0].buf[4], "PID3 was not populated");
	TEST_ASSERT_EQUAL_MESSAGE(0x0D, testPacket[0].buf[5], "PID3 was not populated");
}

void test_can_pm_generate_multi_packet_message(void)
{
	int NUM_TEST_PACKETS = 4;
	CAN_message_t testPacket[NUM_TEST_PACKETS];
	pid_request_t pidReq[6] = {
			{ .pid = 0x0C, .mode = 0x01 },
			{ .pid = 0x0D, .mode = 0x01 },
			{ .pid = 0x220D, .mode = 0x01 },
			{ .pid = 0x0B, .mode = 0x01 },
			{ .pid = 0x5245, .mode = 0x01 },
			{ .pid = 0x6547, .mode = 0x01 }
	};
	uint8_t numIds = 1;

	uint8_t testMode = 0x01;

	can_pm_generate_message(testPacket, NUM_TEST_PACKETS, testMode , pidReq, 6);

	TEST_ASSERT_EQUAL(NUM_TEST_PACKETS, sizeof(testPacket)/sizeof(testPacket[0]));

	TEST_ASSERT_EQUAL_MESSAGE(0x10                   , testPacket[0].buf[0], "frame was not populated");
	TEST_ASSERT_EQUAL_MESSAGE(10                     , testPacket[0].buf[1], "Length was not populated");
	TEST_ASSERT_EQUAL_MESSAGE(testMode               , testPacket[0].buf[2], "Mode was not populated");
	TEST_ASSERT_EQUAL_MESSAGE(pidReq[0].pid          , testPacket[0].buf[3], "PID1 was not populated");
	TEST_ASSERT_EQUAL_MESSAGE(pidReq[1].pid          , testPacket[0].buf[4], "PID2 was not populated");
	TEST_ASSERT_EQUAL_MESSAGE((pidReq[2].pid >> 8)   , testPacket[0].buf[5], "PID3 was not populated");
	TEST_ASSERT_EQUAL_MESSAGE((pidReq[2].pid & 0xFF) , testPacket[0].buf[6], "PID3 was not populated");
	TEST_ASSERT_EQUAL_MESSAGE(pidReq[3].pid          , testPacket[0].buf[7], "PID4 was not populated");

	TEST_ASSERT_EQUAL_MESSAGE(0x21                   , testPacket[1].buf[0], "frame was not populated");
	TEST_ASSERT_EQUAL_MESSAGE((pidReq[4].pid >> 8)   , testPacket[1].buf[1], "PID5 was not populated");
	TEST_ASSERT_EQUAL_MESSAGE((pidReq[4].pid & 0xFF) , testPacket[1].buf[2], "PID5 was not populated");
	TEST_ASSERT_EQUAL_MESSAGE((pidReq[5].pid >> 8)   , testPacket[1].buf[3], "PID6 was not populated");
	TEST_ASSERT_EQUAL_MESSAGE((pidReq[5].pid & 0xFF) , testPacket[1].buf[4], "PID6 was not populated");
	TEST_ASSERT_EQUAL_MESSAGE(0                      , testPacket[1].buf[5], "Buffer was not cleared");
	TEST_ASSERT_EQUAL_MESSAGE(0                      , testPacket[1].buf[6], "Buffer was not cleared");
	TEST_ASSERT_EQUAL_MESSAGE(0                      , testPacket[1].buf[7], "Buffer was not cleared");
}

