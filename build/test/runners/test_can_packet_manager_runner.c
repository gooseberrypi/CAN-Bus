/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Test Runner Used To Run Each Test Below=====*/
#define RUN_TEST(TestFunc, TestLineNum) \
{ \
  Unity.CurrentTestName = #TestFunc; \
  Unity.CurrentTestLineNumber = TestLineNum; \
  Unity.NumberOfTests++; \
  CMock_Init(); \
  UNITY_CLR_DETAILS(); \
  if (TEST_PROTECT()) \
  { \
      setUp(); \
      TestFunc(); \
  } \
  if (TEST_PROTECT()) \
  { \
    tearDown(); \
    CMock_Verify(); \
  } \
  CMock_Destroy(); \
  UnityConcludeTest(); \
}

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"
#include "cmock.h"
#include <setjmp.h>
#include <stdio.h>
#include "mock_stm32f4xx_hal.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_get_PID_length(void);
extern void test_populate_PID_array_length(void);
extern void test_can_pm_set_id(void);
extern void test_can_pm_generate_message(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  mock_stm32f4xx_hal_Init();
}
static void CMock_Verify(void)
{
  mock_stm32f4xx_hal_Verify();
}
static void CMock_Destroy(void)
{
  mock_stm32f4xx_hal_Destroy();
}

/*=======Test Reset Option=====*/
void resetTest(void);
void resetTest(void)
{
  CMock_Verify();
  CMock_Destroy();
  tearDown();
  CMock_Init();
  setUp();
}


/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test_can_packet_manager.c");
  RUN_TEST(test_get_PID_length, 20);
  RUN_TEST(test_populate_PID_array_length, 33);
  RUN_TEST(test_can_pm_set_id, 50);
  RUN_TEST(test_can_pm_generate_message, 74);

  CMock_Guts_MemFreeFinal();
  return (UnityEnd());
}
