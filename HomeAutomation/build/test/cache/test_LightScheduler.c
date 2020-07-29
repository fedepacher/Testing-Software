#include "build/temp/_test_LightScheduler.c"
#include "src/TimeService.h"
#include "src/LightScheduler.h"
#include "src/LightControllerSpy.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"




void setTimeTo(int day, int minuteOfDay)

{

    FakeTimeService_SetDay(day);

    FakeTimeService_SetMinute(minuteOfDay);

}

void checkLightState(int id, int level)

{

    UnityAssertEqualNumber((UNITY_INT)((id)), (UNITY_INT)((LightControllerSpy_GetLastId())), (

   ((void *)0)

   ), (UNITY_UINT)(14), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((level)), (UNITY_INT)((LightControllerSpy_GetLastState())), (

   ((void *)0)

   ), (UNITY_UINT)(15), UNITY_DISPLAY_STYLE_INT);

}







void setUp(void){

    LightController_Create();

    LightScheduler_Create();

}







void tearDown(void){

    LightController_Destroy();

    LightScheduler_Destroy();

}





void test_LightControllerSpy_Create(void){

    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);

}





void test_RememberTheLastLightIdControlled(void){

    LightController_On(10);

    UnityAssertEqualNumber((UNITY_INT)((10)), (UNITY_INT)((LightControllerSpy_GetLastId())), (

   ((void *)0)

   ), (UNITY_UINT)(40), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((LIGHT_ON)), (UNITY_INT)((LightControllerSpy_GetLastState())), (

   ((void *)0)

   ), (UNITY_UINT)(41), UNITY_DISPLAY_STYLE_INT);



}







void test_NoScheduleNothingHappens(void){

    setTimeTo(MONDAY, 100);



    LightScheduler_Wakeup();



    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);



}







void test_ScheduleOnEverydayNotTimeYet(void){

    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);

    setTimeTo(MONDAY, 1190);

    LightScheduler_Wakeup();

    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);

}





void test_ScheduleOnEverydayItsTime(void){

    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);

    setTimeTo(MONDAY, 1200);

    LightScheduler_Wakeup();

    UnityAssertEqualNumber((UNITY_INT)((3)), (UNITY_INT)((LightControllerSpy_GetLastId())), (

   ((void *)0)

   ), (UNITY_UINT)(70), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((LIGHT_ON)), (UNITY_INT)((LightControllerSpy_GetLastState())), (

   ((void *)0)

   ), (UNITY_UINT)(71), UNITY_DISPLAY_STYLE_INT);

}





void test_ScheduleOffEverydayItsTime(void){

    LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);

    setTimeTo(MONDAY, 1200);

    LightScheduler_Wakeup();

    UnityAssertEqualNumber((UNITY_INT)((3)), (UNITY_INT)((LightControllerSpy_GetLastId())), (

   ((void *)0)

   ), (UNITY_UINT)(79), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((LIGHT_OFF)), (UNITY_INT)((LightControllerSpy_GetLastState())), (

   ((void *)0)

   ), (UNITY_UINT)(80), UNITY_DISPLAY_STYLE_INT);

}





void test_ScheduleWeekEndItsMonday(void){

    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);

    setTimeTo(MONDAY, 1200);

    LightScheduler_Wakeup();

    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);

}





void test_ScheduleTuesdayButItsMonday(void){

    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);

    setTimeTo(MONDAY, 1200);

    LightScheduler_Wakeup();

    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);

}





void test_ScheduleTuesdayAndItsTuesday(void){

    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);

    setTimeTo(TUESDAY, 1200);

    LightScheduler_Wakeup();

    checkLightState(3, LIGHT_ON);

}





void test_ScheduleWeekEndItsFriday(void){

    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);

    setTimeTo(FRIDAY, 1200);

    LightScheduler_Wakeup();

    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);

}





void test_ScheduleWeekEndItsSaturday(void){

    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);

    setTimeTo(SATURDAY, 1200);

    LightScheduler_Wakeup();

    checkLightState(3, LIGHT_ON);

}





void test_ScheduleWeekEndItsSunday(void){

    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);

    setTimeTo(SUNDAY, 1200);

    LightScheduler_Wakeup();

    checkLightState(3, LIGHT_ON);

}
