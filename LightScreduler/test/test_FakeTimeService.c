#include "unity.h"
#include "LightControllerSpy.h"
#include "TimeService.h"


//! @test   Initialization function
void setUp(void){
   
}


//! @test   Deinitialization function
void tearDown(void){

}

//! @test   
void test_create(void){
    Time time;
    TimeService_GetTime(&time);
    TEST_ASSERT_EQUAL_INT(TIME_UNKNOWN, time.minuteOfDay);
    TEST_ASSERT_EQUAL_INT(TIME_UNKNOWN, time.dayOfWeek);
}

//! @test   
void test_set(void){
    Time time;
    FakeTimeService_SetMinute(42);
    FakeTimeService_SetDay(SATURDAY);

    TimeService_GetTime(&time);

    TEST_ASSERT_EQUAL_INT(42, time.minuteOfDay);
    TEST_ASSERT_EQUAL_INT(SATURDAY, time.dayOfWeek);
}