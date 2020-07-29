#include "build/temp/_test_FormatOutputSpy.c"
#include "src/utils.h"
#include "src/FormatOutputSpy.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"


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

    UnityAssertEqualString((const char*)(("Hello, World\n")), (const char*)((FormatOutputSpy_GetOutput())), (

   ((void *)0)

   ), (UNITY_UINT)(20));

}





void test_PrintMultipleTimes(void){

    FormatOutputSpy_Create(25);

    FormatOutput("Hello");

    FormatOutput(", World\n");

    UnityAssertEqualString((const char*)(("Hello, World\n")), (const char*)((FormatOutputSpy_GetOutput())), (

   ((void *)0)

   ), (UNITY_UINT)(28));

}



void test_PrintMultipleOutputsPastFull(void){

    FormatOutputSpy_Create(12);

    FormatOutput("12345");

    FormatOutput("67890");

    FormatOutput("ABCDEF");

    UnityAssertEqualString((const char*)(("1234567890AB")), (const char*)((FormatOutputSpy_GetOutput())), (

   ((void *)0)

   ), (UNITY_UINT)(36));

}
