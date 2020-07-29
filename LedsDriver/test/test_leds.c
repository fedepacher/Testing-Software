#include "unity.h"
#include "LedsDriver.h"
#include "RuntimeErrorStub.h"
    

static uint16_t virtualLeds;

//! @test   Initialization function
void setUp(void){
    LedsDriver_Constructor(&virtualLeds);
}

//! @test   Deinitialization function
void tearDown(void){

}

//! @test   Message fail function
/*void test_fail_function(void){
    TEST_FAIL_MESSAGE("HOLA MUNDO");
}*/

//! @test   Check leds initial values
void test_check_init_values(void){
    TEST_ASSERT_EQUAL_HEX16(0X0000, virtualLeds);
}

//! @test   Turn led on
void test_turn_led_on(void){
    LedsDriver_On(1);
    TEST_ASSERT_EQUAL_HEX16(0X0001, virtualLeds);
}

//! @test   Turn led off
void test_turn_led_off(void){
    LedsDriver_On(1);
    LedsDriver_Off(1);
    TEST_ASSERT_EQUAL_HEX16(0X0000, virtualLeds);
}

//! @test   Turn on multiple leds
void test_turn_multiple_leds_on(void){
    LedsDriver_On(9);
    LedsDriver_On(8);
    TEST_ASSERT_EQUAL_HEX16(0X0180, virtualLeds);
}

//! @test   Turn on all leds
void test_turn_all_leds(void){
    LedsDriver_AllOn();
    TEST_ASSERT_EQUAL_HEX16(0XFFFF, virtualLeds);
}


//! @test   Turn off any leds
void test_turn_any_leds_off(void){
    LedsDriver_AllOn();
    LedsDriver_Off(8);
    TEST_ASSERT_EQUAL_HEX16(0XFF7F, virtualLeds);
}

//! @test   Read led state
void test_read_leds_state(void){
    virtualLeds = 0xFFFF;
    LedsDriver_On(8);
    TEST_ASSERT_EQUAL_HEX16(0X0080, virtualLeds);
}

//! @test   Check boundary
void test_upper_lower_bounds(void){
    LedsDriver_On(1);
    LedsDriver_On(16);
    TEST_ASSERT_EQUAL_HEX16(0X8001, virtualLeds);
}

//! @test   Check out of bounds turning on leds
void test_out_of_bounds_turn_on(void){
    LedsDriver_On(-1);
    LedsDriver_On(0);
    LedsDriver_On(17);
    LedsDriver_On(241);
    TEST_ASSERT_EQUAL_HEX16(0X0000, virtualLeds);
}

//! @test   Check out of bounds turning off leds
void test_out_of_bounds_turn_off(void){
    LedsDriver_AllOn();

    LedsDriver_Off(-1);
    LedsDriver_Off(0);
    LedsDriver_Off(17);
    LedsDriver_Off(241);
    TEST_ASSERT_EQUAL_HEX16(0XFFFF, virtualLeds);
}

//! @test   Runtime error produced by out of bound
void test_out_of_bounds_produces_runtime_error(void){
    LedsDriver_Off(-1);
    RUNTIME_ERROR("LED Driver: out of bounds LED", -1);
    TEST_ASSERT_EQUAL_STRING("LED Driver: out of bounds LED", 
        RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}

//! @test   Read if a led is on
void test_led_isOn(void){
   TEST_ASSERT_FALSE(LedsDriver_IsOn(11));
   LedsDriver_On(11);
   TEST_ASSERT_TRUE(LedsDriver_IsOn(11));
}

//! @test   Check if a led out of bound is on 
void test_out_of_bounds_leds_are_always_off(void){
   TEST_ASSERT_TRUE(LedsDriver_IsOff(0));
   TEST_ASSERT_TRUE(LedsDriver_IsOff(17));
   TEST_ASSERT_FALSE(LedsDriver_IsOn(0));
   TEST_ASSERT_FALSE(LedsDriver_IsOn(17));
}

//! @test   Read if a led is off
void test_led_isOff(void){
   TEST_ASSERT_TRUE(LedsDriver_IsOff(11));
   LedsDriver_On(11);
   TEST_ASSERT_FALSE(LedsDriver_IsOff(11));
}

//! @test Test turn off multiple leds
void test_turn_off_multiple_leds(void){
    LedsDriver_AllOn();
    LedsDriver_Off(9);
    LedsDriver_Off(8);
    TEST_ASSERT_EQUAL_HEX16((~0x180)&0xFFFF, virtualLeds);
    
}

//! @test Test turn off all leds
void test_turn_off_all_leds(void){
    LedsDriver_AllOn();
    LedsDriver_AllOff();
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}