#include "unity.h"
#include "FormatOutputSpy.h"
#include "utils.h"

int (*saveFormatOutput)(const char * format, ...);

void setUp(void){
    saveFormatOutput = FormatOutput;
    FormatOutput = FormatOutputSpy;
}

void tearDown(void){
    FormatOutput = saveFormatOutput;
    FormatOutputSpy_Destroy();
}

void test_FormatOtputSpy_printf(void){
    FormatOutputSpy_Create(20);
    FormatOutput("Hello, World\n");
    TEST_ASSERT_EQUAL_STRING("Hello, World\n", FormatOutputSpy_GetOutput());
}


void test_PrintMultipleTimes(void){
    FormatOutputSpy_Create(25);
    FormatOutput("Hello");
    FormatOutput(", World\n");
    TEST_ASSERT_EQUAL_STRING("Hello, World\n", FormatOutputSpy_GetOutput());
}

void test_PrintMultipleOutputsPastFull(void){
    FormatOutputSpy_Create(12);
    FormatOutput("12345");
    FormatOutput("67890");
    FormatOutput("ABCDEF");
    TEST_ASSERT_EQUAL_STRING("1234567890AB", FormatOutputSpy_GetOutput());
}