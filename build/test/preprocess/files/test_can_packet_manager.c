#include "build/temp/_test_can_packet_manager.c"
#include "can_packet_manager.h"
#include "mock_stm32f4xx_hal.h"
#include "unity.h"








void setUp( void )

{

}



void tearDown( void )

{

}











void test_get_PID_length(void)

{

 UnityAssertEqualNumber((UNITY_INT)((0U)), (UNITY_INT)((get_PID_length(0x0000))), (("PID length not as expected")), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_INT);

 for(uint16_t pid = 1; pid < 0xFF; pid++)

 {

  UnityAssertEqualNumber((UNITY_INT)((1U)), (UNITY_INT)((get_PID_length(pid))), (("PID length not as expected")), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_INT);

 }

 for(uint16_t pid = 0x100; pid < 0xFFFF; pid++)

 {

  UnityAssertEqualNumber((UNITY_INT)((2U)), (UNITY_INT)((get_PID_length(pid))), (("PID length not as expected")), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_INT);

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

 UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((pidReq[0].pid_len)), (("PID1 length not as expected")), (UNITY_UINT)(41), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((pidReq[1].pid_len)), (("PID2 length not as expected")), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)((2)), (UNITY_INT)((pidReq[2].pid_len)), (("PID3 length not as expected")), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_INT);

}











void test_can_pm_set_id(void)

{

 CAN_message_t can_pm_set_id_test_message;

 can_packet_manager_status status_test_var;

 uint32_t id_max_value;









 id_max_value= 0xFFFFFF;





 for(uint32_t id = 0; id < id_max_value; id++)

 {

  status_test_var = can_pm_set_id(&can_pm_set_id_test_message, id);

  UnityAssertEqualNumber((UNITY_INT)((id)), (UNITY_INT)((can_pm_set_id_test_message.id)), (("ID is not as expected")), (UNITY_UINT)(65), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((can_pm_success)), (UNITY_INT)((status_test_var)), (("Status message is not as expected")), (UNITY_UINT)(66), UNITY_DISPLAY_STYLE_INT);

 }

}











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



 UnityAssertEqualNumber((UNITY_INT)((NUM_TEST_PACKETS)), (UNITY_INT)((sizeof(testPacket)/sizeof(testPacket[0]))), (

((void *)0)

), (UNITY_UINT)(89), UNITY_DISPLAY_STYLE_INT);



 UnityAssertEqualNumber((UNITY_INT)((5)), (UNITY_INT)((testPacket[0].buf[0])), (("Length was not populated")), (UNITY_UINT)(91), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)((testMode)), (UNITY_INT)((testPacket[0].buf[1])), (("Mode was not populated")), (UNITY_UINT)(92), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)((pidReq[0].pid)), (UNITY_INT)((testPacket[0].buf[2])), (("PID1 was not populated")), (UNITY_UINT)(93), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)((pidReq[1].pid)), (UNITY_INT)((testPacket[0].buf[3])), (("PID2 was not populated")), (UNITY_UINT)(94), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)((0x22)), (UNITY_INT)((testPacket[0].buf[4])), (("PID3 was not populated")), (UNITY_UINT)(95), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)((0x0D)), (UNITY_INT)((testPacket[0].buf[5])), (("PID3 was not populated")), (UNITY_UINT)(96), UNITY_DISPLAY_STYLE_INT);

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



 UnityAssertEqualNumber((UNITY_INT)((NUM_TEST_PACKETS)), (UNITY_INT)((sizeof(testPacket)/sizeof(testPacket[0]))), (

((void *)0)

), (UNITY_UINT)(117), UNITY_DISPLAY_STYLE_INT);



 UnityAssertEqualNumber((UNITY_INT)((0x10)), (UNITY_INT)((testPacket[0].buf[0])), (("frame was not populated")), (UNITY_UINT)(119), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)((10)), (UNITY_INT)((testPacket[0].buf[1])), (("Length was not populated")), (UNITY_UINT)(120), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)((testMode)), (UNITY_INT)((testPacket[0].buf[2])), (("Mode was not populated")), (UNITY_UINT)(121), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)((pidReq[0].pid)), (UNITY_INT)((testPacket[0].buf[3])), (("PID1 was not populated")), (UNITY_UINT)(122), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)((pidReq[1].pid)), (UNITY_INT)((testPacket[0].buf[4])), (("PID2 was not populated")), (UNITY_UINT)(123), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)(((pidReq[2].pid >> 8))), (UNITY_INT)((testPacket[0].buf[5])), (("PID3 was not populated")), (UNITY_UINT)(124), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)(((pidReq[2].pid & 0xFF))), (UNITY_INT)((testPacket[0].buf[6])), (("PID3 was not populated")), (UNITY_UINT)(125), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)((pidReq[3].pid)), (UNITY_INT)((testPacket[0].buf[7])), (("PID4 was not populated")), (UNITY_UINT)(126), UNITY_DISPLAY_STYLE_INT);



 UnityAssertEqualNumber((UNITY_INT)((0x21)), (UNITY_INT)((testPacket[1].buf[0])), (("frame was not populated")), (UNITY_UINT)(128), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)(((pidReq[4].pid >> 8))), (UNITY_INT)((testPacket[1].buf[1])), (("PID5 was not populated")), (UNITY_UINT)(129), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)(((pidReq[4].pid & 0xFF))), (UNITY_INT)((testPacket[1].buf[2])), (("PID5 was not populated")), (UNITY_UINT)(130), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)(((pidReq[5].pid >> 8))), (UNITY_INT)((testPacket[1].buf[3])), (("PID6 was not populated")), (UNITY_UINT)(131), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)(((pidReq[5].pid & 0xFF))), (UNITY_INT)((testPacket[1].buf[4])), (("PID6 was not populated")), (UNITY_UINT)(132), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((testPacket[1].buf[5])), (("Buffer was not cleared")), (UNITY_UINT)(133), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((testPacket[1].buf[6])), (("Buffer was not cleared")), (UNITY_UINT)(134), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((testPacket[1].buf[7])), (("Buffer was not cleared")), (UNITY_UINT)(135), UNITY_DISPLAY_STYLE_INT);

}
