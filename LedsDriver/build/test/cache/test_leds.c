#include "build/temp/_test_leds.c"
#include "src/RuntimeErrorStub.h"
#include "src/LedsDriver.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"




static uint16_t virtualLeds;





void setUp(void){

    LedsDriver_Constructor(&virtualLeds);

}





void tearDown(void){



}















void test_check_init_values(void){

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0X0000)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_HEX16);

}





void test_turn_led_on(void){

    LedsDriver_On(1);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0X0001)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_HEX16);

}





void test_turn_led_off(void){

    LedsDriver_On(1);

    LedsDriver_Off(1);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0X0000)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_HEX16);

}





void test_turn_multiple_leds_on(void){

    LedsDriver_On(9);

    LedsDriver_On(8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0X0180)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(45), UNITY_DISPLAY_STYLE_HEX16);

}





void test_turn_all_leds(void){

    LedsDriver_AllOn();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0XFFFF)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(51), UNITY_DISPLAY_STYLE_HEX16);

}







void test_turn_any_leds_off(void){

    LedsDriver_AllOn();

    LedsDriver_Off(8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0XFF7F)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(59), UNITY_DISPLAY_STYLE_HEX16);

}





void test_read_leds_state(void){

    virtualLeds = 0xFFFF;

    LedsDriver_On(8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0X0080)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(66), UNITY_DISPLAY_STYLE_HEX16);

}





void test_upper_lower_bounds(void){

    LedsDriver_On(1);

    LedsDriver_On(16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0X8001)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(73), UNITY_DISPLAY_STYLE_HEX16);

}





void test_out_of_bounds_turn_on(void){

    LedsDriver_On(-1);

    LedsDriver_On(0);

    LedsDriver_On(17);

    LedsDriver_On(241);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0X0000)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(82), UNITY_DISPLAY_STYLE_HEX16);

}





void test_out_of_bounds_turn_off(void){

    LedsDriver_AllOn();



    LedsDriver_Off(-1);

    LedsDriver_Off(0);

    LedsDriver_Off(17);

    LedsDriver_Off(241);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0XFFFF)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(93), UNITY_DISPLAY_STYLE_HEX16);

}





void test_out_of_bounds_produces_runtime_error(void){

    LedsDriver_Off(-1);

    RuntimeError("LED Driver: out of bounds LED", -1, "test/test_leds.c", 99);

    UnityAssertEqualString((const char*)(("LED Driver: out of bounds LED")), (const char*)((RuntimeErrorStub_GetLastError())), (

   ((void *)0)

   ), (UNITY_UINT)(101))

                                        ;

    UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((RuntimeErrorStub_GetLastParameter())), (

   ((void *)0)

   ), (UNITY_UINT)(102), UNITY_DISPLAY_STYLE_INT);

}





void test_led_isOn(void){

   do {if (!(LedsDriver_IsOn(11))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(107)));}} while(0);

   LedsDriver_On(11);

   do {if ((LedsDriver_IsOn(11))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(109)));}} while(0);

}





void test_out_of_bounds_leds_are_always_off(void){

   do {if ((LedsDriver_IsOff(0))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(114)));}} while(0);

   do {if ((LedsDriver_IsOff(17))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(115)));}} while(0);

   do {if (!(LedsDriver_IsOn(0))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(116)));}} while(0);

   do {if (!(LedsDriver_IsOn(17))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(117)));}} while(0);

}





void test_led_isOff(void){

   do {if ((LedsDriver_IsOff(11))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(122)));}} while(0);

   LedsDriver_On(11);

   do {if (!(LedsDriver_IsOff(11))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(124)));}} while(0);

}





void test_turn_off_multiple_leds(void){

    LedsDriver_AllOn();

    LedsDriver_Off(9);

    LedsDriver_Off(8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)(((~0x180)&0xFFFF)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(132), UNITY_DISPLAY_STYLE_HEX16);



}





void test_turn_off_all_leds(void){

    LedsDriver_AllOn();

    LedsDriver_AllOff();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(140), UNITY_DISPLAY_STYLE_HEX16);

}
