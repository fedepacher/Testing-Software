#include "unity.h"
#include "envio.h"

static const char file_name[] = "/home/fedepacher/Desktop/Pruebas/MSystem0.xml";
static const char output_file_name[] = "/home/fedepacher/Desktop/Pruebas/output_split_";
static const char output_file_format[] = "xml";
static file_status_t file_status;
static FILE file;// = NULL;
static char buffer[FIRST_CHAR_SIZE + HEADER_SIZE + BUFFER_SIZE + ASTERISCO_SIZE + CRC_SIZE];

//! @test   Initialization function
void setUp(void){
    file_constructor(buffer, strlen((char*)buffer), &file_status);
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
    TEST_ASSERT_EQUAL_STRING("$SOTX:150*1E", buffer);
}

//! @test   Create data frame test
void test_create_data_frame(void){
    file_status = create_data_frame(file_name, &buffer[0]);
    //printf("%s", buffer);
    TEST_ASSERT_EQUAL(OK, file_status);
    //TEST_ASSERT_EQUAL_STRING("$SOTX:150*30", buffer);
}

//! @test   Make a file with data frame in order to debug de the receive.c
void test_split_file(void){
    file_status = split_file(file_name, output_file_name, output_file_format, buffer, 2000); //2000 max size of new files
    TEST_ASSERT_EQUAL(OK, file_status);   
}

//! @test   Create end of frame test
void test_create_end_of_frame(void){
    file_status = create_end_of_frame(file_name, &buffer[0]);
    printf("%s", buffer);
    TEST_ASSERT_EQUAL(OK, file_status);
    TEST_ASSERT_EQUAL_STRING("$EOTX:150*10", buffer);
}

