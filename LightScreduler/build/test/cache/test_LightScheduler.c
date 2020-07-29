#include "build/temp/_test_LightScheduler.c"
#include "src/LightScheduler.h"
#include "src/LightControllerSpy.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"






void setUp(void){

    LightController_Create();



}







void tearDown(void){

    LightController_Destroy();



}





void test_LightControllerSpy_Create(void){

    UnityAssertEqualNumber((UNITY_INT)((LIGHT_ID_UNKNOWN)), (UNITY_INT)((LightControllerSpy_GetLastId())), (

   ((void *)0)

   ), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((LIGHT_STATE_UNKNOWN)), (UNITY_INT)((LightControllerSpy_GetLastState())), (

   ((void *)0)

   ), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_INT);

}





void test_RememberTheLastLightIdControlled(void){

    LightController_On(10);

    UnityAssertEqualNumber((UNITY_INT)((10)), (UNITY_INT)((LightControllerSpy_GetLastId())), (

   ((void *)0)

   ), (UNITY_UINT)(28), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((LIGHT_ON)), (UNITY_INT)((LightControllerSpy_GetLastState())), (

   ((void *)0)

   ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_INT);

}







void test_NoScheduleNothingHappens(void){



    FakeTimeService_SetDay(MONDAY);

    FakeTimeService_SetMinute(100);



    LightScheduler_WakeUp();



    UnityAssertEqualNumber((UNITY_INT)((LIGHT_ID_UNKNOWN)), (UNITY_INT)((LightControllerSpy_GetLastId())), (

   ((void *)0)

   ), (UNITY_UINT)(41), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((LIGHT_STATE_UNKNOWN)), (UNITY_INT)((LightControllerSpy_GetLastState())), (

   ((void *)0)

   ), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_INT);

}
