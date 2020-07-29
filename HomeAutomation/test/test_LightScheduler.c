#include "unity.h"
#include "LightControllerSpy.h"
#include "LightScheduler.h"
#include "TimeService.h"


void setTimeTo(int day, int minuteOfDay)
{
    FakeTimeService_SetDay(day);
    FakeTimeService_SetMinute(minuteOfDay);
}
void checkLightState(int id, int level)
{
    TEST_ASSERT_EQUAL_INT(id, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT(level, LightControllerSpy_GetLastState());
}


//! @test   Initialization function
void setUp(void){
    LightController_Create();
    LightScheduler_Create();
}


//! @test   Deinitialization function
void tearDown(void){
    LightController_Destroy();
    LightScheduler_Destroy();
}

//! @test   Initialize test
void test_LightControllerSpy_Create(void){
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

//! @test   Remember The Last Light Id Controlled test
void test_RememberTheLastLightIdControlled(void){
    LightController_On(10);
    TEST_ASSERT_EQUAL_INT(10, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT(LIGHT_ON, LightControllerSpy_GetLastState());

}


//! @test
void test_NoScheduleNothingHappens(void){
    setTimeTo(MONDAY, 100);
    
    LightScheduler_Wakeup();

    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);

}


//! @test   Schedule On Everyday Not Time Yet test
void test_ScheduleOnEverydayNotTimeYet(void){
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1190);
    LightScheduler_Wakeup();    
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

//! @test   Schedule On Everyday Not Time Yet test
void test_ScheduleOnEverydayItsTime(void){
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    TEST_ASSERT_EQUAL_INT(3, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT(LIGHT_ON, LightControllerSpy_GetLastState());
}

//! @test   Schedule On Everyday Not Time Yet test
void test_ScheduleOffEverydayItsTime(void){
    LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    TEST_ASSERT_EQUAL_INT(3, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT(LIGHT_OFF, LightControllerSpy_GetLastState());
}

//! @test   Schedule On Everyday Not Time Yet test
void test_ScheduleWeekEndItsMonday(void){
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

//! @test   Schedule On Everyday Not Time Yet test
void test_ScheduleTuesdayButItsMonday(void){
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

//! @test   Schedule On Everyday Not Time Yet test
void test_ScheduleTuesdayAndItsTuesday(void){
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(TUESDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}

//! @test   Schedule On Everyday Not Time Yet test
void test_ScheduleWeekEndItsFriday(void){
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(FRIDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

//! @test   Schedule On Everyday Not Time Yet test
void test_ScheduleWeekEndItsSaturday(void){
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SATURDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}

//! @test   Schedule On Everyday Not Time Yet test
void test_ScheduleWeekEndItsSunday(void){
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SUNDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}


