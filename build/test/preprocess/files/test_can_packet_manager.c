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

  UnityAssertEqualNumber((UNITY_INT)((1U)), (UNITY_INT)((get_PID_length(pid))), (("PID length not as expected")), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_INT);

 }

 for(uint16_t pid = 0x100; pid < 0xFFFF; pid++)

 {

  UnityAssertEqualNumber((UNITY_INT)((2U)), (UNITY_INT)((get_PID_length(pid))), (("PID length not as expected")), (UNITY_UINT)(28), UNITY_DISPLAY_STYLE_INT);

 }

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

  UnityAssertEqualNumber((UNITY_INT)((id)), (UNITY_INT)((can_pm_set_id_test_message.id)), (("ID is not as expected")), (UNITY_UINT)(51), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((can_pm_success)), (UNITY_INT)((status_test_var)), (("Status message is not as expected")), (UNITY_UINT)(52), UNITY_DISPLAY_STYLE_INT);

 }

}
