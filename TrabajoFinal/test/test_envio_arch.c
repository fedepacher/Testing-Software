#include "unity.h"
#include "envio.h"

static file_status_t file_status;

//! @test   Initialization function
void setUp(void){
    file_constructor(&file_status);
}

//! @test   Deinitialization function
void tearDown(void){

}

//! @test   Message fail function
void test_fail_function(void){
    TEST_FAIL_MESSAGE("Test inicial de prueba!!!");
}

