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

 for(uint16_t pid = 0; pid < 0xFF; pid++)

 {

  UnityAssertEqualNumber((UNITY_INT)((1U)), (UNITY_INT)((get_PID_length(pid))), (("PID length not as expected")), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_INT);

 }

 for(uint16_t pid = 0x100; pid < 0xFFFF; pid++)

 {

  UnityAssertEqualNumber((UNITY_INT)((2U)), (UNITY_INT)((get_PID_length(pid))), (("PID length not as expected")), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_INT);

 }

}
