#include "unity.h"
#include "envio.h"

static const char file_name[] = "/home/fedepacher/Desktop/MSystem0.xml";
static file_status_t file_status;

//! @test   Initialization function
void setUp(void){
    file_constructor(&file_status);
}

//! @test   Deinitialization function
void tearDown(void){

}

//! @test   Message fail function
/*void test_fail_function(void){
    TEST_FAIL_MESSAGE("Test inicial de prueba!!!");
}*/

//! @test   Open File test
void test_open_file(void){
    file_status = open_file((char*)file_name);
    TEST_ASSERT_EQUAL(OK, file_status);    
}
