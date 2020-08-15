#include "unity.h"
#include "recibir.h"

static const char file_name[] = "/home/fedepacher/CESE/Testing Soft/PracticaGit/Testing-Software/TrabajoFinal/output_file_test.xml";
static rx_status_t file_status;
static char buffera[BUFFER_SIZE];

//! @test   Initialization function
void setUp(void){
   rx_constructor(buffera, strlen((char*)buffera), &file_status);
}

//! @test   Deinitialization function
void tearDown(void){
    //close_file(&file);
}

//! @test   Message fail function
/*void test_fail_function(void){
    TEST_FAIL_MESSAGE("Test inicial de prueba!!!");
}*/

//! @test   Get data frame from file function
void test_get_data_frame(void){
    file_status = get_data_frame(file_name);
    TEST_ASSERT_EQUAL(OK, file_status);
}