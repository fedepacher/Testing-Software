#include "unity.h"
#include "LightControllerSpy.h"
#include "LightScheduler.h"


//! @test   Initialization function
void setUp(void){
    LightController_Create();
    //LightScheduler_Create();
}


//! @test   Deinitialization function
void tearDown(void){
    LightController_Destroy();
    //LightScheduler_Destroy();
}

//! @test   Initialize test
void test_LightControllerSpy_Create(void){
    TEST_ASSERT_EQUAL_INT(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

//! @test   Remember The Last Light Id Controlled test
void test_RememberTheLastLightIdControlled(void){
    LightController_On(10);
    TEST_ASSERT_EQUAL_INT(10, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT(LIGHT_ON, LightControllerSpy_GetLastState());
}


//! @test
void test_NoScheduleNothingHappens(void){

    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(100);
    
    LightScheduler_WakeUp();

    TEST_ASSERT_EQUAL_INT(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}


//! @test   Schedule On Everyday Not Time Yet test
/*void test_ScheduleOnEverydayNotTimeYet(void){
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1199);

    LightScheduler_Wakeup();
    
    TEST_ASSERT_EQUAL_INT(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}*/

//! @test   Schedule On Everyday Not Time Yet test
/*void test_ScheduleOnEverydayItsTime(void){
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_Wakeup();
    TEST_ASSERT_EQUAL_INT(3, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT(LIGHT_ON, LightControllerSpy_GetLastState());
}*/

//! @test   Schedule On Everyday Not Time Yet test
/*void test_ScheduleOffEverydayItsTime(void){
{
    LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_Wakeup();
    TEST_ASSERT_EQUAL_INT(3, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT(LIGHT_OFF, LightControllerSpy_GetLastState());
}*/