/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_Create(void);
extern void test_EmptyAfterCreation(void);
extern void test_NotFullAfterCreation(void);
extern void test_NotEmpty(void);
extern void test_NotEmptyThenEmpty(void);
extern void test_GetPutOneValue(void);
extern void test_GetPutAFew(void);
extern void test_Capacity(void);
extern void test_IsFull(void);
extern void test_EmptyToFullToEmpty(void);
extern void test_WrapAround(void);
extern void test_PutToFullThrows(void);
extern void test_PutToFullDoesNotDamageContents(void);
extern void test_GetFromEmptyReturns0(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
}
static void CMock_Verify(void)
{
}
static void CMock_Destroy(void)
{
}

/*=======Test Reset Options=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  CMock_Verify();
  CMock_Destroy();
  CMock_Init();
  setUp();
}
void verifyTest(void);
void verifyTest(void)
{
  CMock_Verify();
}

/*=======Test Runner Used To Run Each Test=====*/
static void run_test(UnityTestFunction func, const char* name, int line_num)
{
    Unity.CurrentTestName = name;
    Unity.CurrentTestLineNumber = line_num;
#ifdef UNITY_USE_COMMAND_LINE_ARGS
    if (!UnityTestMatches())
        return;
#endif
    Unity.NumberOfTests++;
    UNITY_CLR_DETAILS();
    UNITY_EXEC_TIME_START();
    CMock_Init();
    if (TEST_PROTECT())
    {
        setUp();
        func();
    }
    if (TEST_PROTECT())
    {
        tearDown();
        CMock_Verify();
    }
    CMock_Destroy();
    UNITY_EXEC_TIME_STOP();
    UnityConcludeTest();
}

/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test_circularBuffer.c");
  run_test(test_Create, "test_Create", 23);
  run_test(test_EmptyAfterCreation, "test_EmptyAfterCreation", 28);
  run_test(test_NotFullAfterCreation, "test_NotFullAfterCreation", 33);
  run_test(test_NotEmpty, "test_NotEmpty", 38);
  run_test(test_NotEmptyThenEmpty, "test_NotEmptyThenEmpty", 44);
  run_test(test_GetPutOneValue, "test_GetPutOneValue", 52);
  run_test(test_GetPutAFew, "test_GetPutAFew", 58);
  run_test(test_Capacity, "test_Capacity", 68);
  run_test(test_IsFull, "test_IsFull", 75);
  run_test(test_EmptyToFullToEmpty, "test_EmptyToFullToEmpty", 83);
  run_test(test_WrapAround, "test_WrapAround", 97);
  run_test(test_PutToFullThrows, "test_PutToFullThrows", 116);
  run_test(test_PutToFullDoesNotDamageContents, "test_PutToFullDoesNotDamageContents", 122);
  run_test(test_GetFromEmptyReturns0, "test_GetFromEmptyReturns0", 134);

  return UnityEnd();
}
