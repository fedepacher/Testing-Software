#include "build/temp/_test_FakeTimeService.c"
#include "src/TimeService.h"
#include "src/LightControllerSpy.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"






void setUp(void){



}







void tearDown(void){



}





void test_create(void){

    Time time;

    TimeService_GetTime(&time);

    UnityAssertEqualNumber((UNITY_INT)((TIME_UNKNOWN)), (UNITY_INT)((time.minuteOfDay)), (

   ((void *)0)

   ), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((TIME_UNKNOWN)), (UNITY_INT)((time.dayOfWeek)), (

   ((void *)0)

   ), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_INT);

}





void test_set(void){

    Time time;

    FakeTimeService_SetMinute(42);

    FakeTimeService_SetDay(SATURDAY);



    TimeService_GetTime(&time);



    UnityAssertEqualNumber((UNITY_INT)((42)), (UNITY_INT)((time.minuteOfDay)), (

   ((void *)0)

   ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((SATURDAY)), (UNITY_INT)((time.dayOfWeek)), (

   ((void *)0)

   ), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_INT);

}
