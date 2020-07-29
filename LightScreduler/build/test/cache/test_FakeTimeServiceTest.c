#include "build/temp/_test_FakeTimeServiceTest.c"
#include "src/LightScheduler.h"
#include "src/FakeTimeService.h"




static int callBackCalled;





void setUp(void){

    callBackCalled = 0;

    TimeService_Create();

}







void tearDown(void){

    TimeService_Destroy();

}





static void TestCallback()

{

    callBackCalled = 1;

}





void test_SimulateATic(void)

{

    TimeService_SetPeriodicAlarmInSeconds(60, TestCallback);



    FakeTimeService_SetMinute(42);

    FakeTimeService_SetDay(SUNDAY);

    FakeTimeService_MinuteIsUp();



    LONGS_EQUAL(1, callBackCalled);

}









void test_Create(void)

{

    Time time;

    TimeService_GetTime(&time);

    LONGS_EQUAL(TIME_UNKNOWN, time.minuteOfDay);

    LONGS_EQUAL(TIME_UNKNOWN, time.dayOfWeek);

}



void test_Set(void)

{

    Time time;

    FakeTimeService_SetMinute(42);

    FakeTimeService_SetDay(SATURDAY);

    TimeService_GetTime(&time);

    LONGS_EQUAL(42, time.minuteOfDay);

    LONGS_EQUAL(SATURDAY, time.dayOfWeek);

}
