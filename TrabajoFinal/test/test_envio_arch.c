#include "unity.h"
#include "envio.h"

static const char file_name[] = "/home/fedepacher/CESE/Testing Soft/PracticaGit/Testing-Software/TrabajoFinal/MSystem0.xml";
static const char output_file_format[] = "xml";
static tx_status_t file_status;
static FILE file;// = NULL;
static char buffer[BUFFER_SIZE];

//! @test   Initialization function
void setUp(void){
    tx_constructor(buffer, strlen((char*)buffer), &file_status);
}

//! @test   Deinitialization function
void tearDown(void){
    //close_file(&file);
}

//! @test   Message fail function
/*void test_fail_function(void){
    TEST_FAIL_MESSAGE("Test inicial de prueba!!!");
}*/

//! @test   Open File test
void test_open_file(void){
    file_status = open_file(file_name);
    TEST_ASSERT_EQUAL(OK, file_status);   
}


//! @test   Create start of frame test
void test_create_start_of_frame(void){
    file_status = create_start_of_frame(file_name, &buffer[0]);
    printf("%s", buffer);
    TEST_ASSERT_EQUAL(OK, file_status);
    TEST_ASSERT_EQUAL_STRING("$SOTX:1669*5E", buffer);
}

//! @test   Create data frame test
void test_create_data_frame(void){
    file_status = create_data_frame(file_name, &buffer[0]);
    TEST_ASSERT_EQUAL(OK, file_status);
}

//! @test   Create end of frame test
void test_create_end_of_frame(void){
    file_status = create_end_of_frame(file_name, &buffer[0]);
    printf("%s", buffer);
    TEST_ASSERT_EQUAL(OK, file_status);
    TEST_ASSERT_EQUAL_STRING("$EOTX:1669*50", buffer);
}

