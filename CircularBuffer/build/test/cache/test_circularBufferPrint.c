#include "build/temp/_test_circularBufferPrint.c"
#include "src/CircularBuffer.h"
#include "src/utils.h"
#include "src/FormatOutputSpy.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"


CircularBuffer buffer;

const char * expectedOutput;

const char * actualOutput;

int (*saveFormatOutput)(const char * format, ...);



void setUp(void){

    saveFormatOutput = FormatOutput;

    FormatOutput = FormatOutputSpy;

    FormatOutputSpy_Create(100);

    actualOutput = FormatOutputSpy_GetOutput();

    buffer = CircularBuffer_Create(10);

}



void tearDown(void){

    CircularBuffer_Destroy(buffer);

    FormatOutput = saveFormatOutput;

    FormatOutputSpy_Destroy();

}



void test_printEmpty(void){

    expectedOutput = "Circular buffer content:\n<>\n";

    CircularBuffer_Print(buffer);

    UnityAssertEqualString((const char*)((expectedOutput)), (const char*)((actualOutput)), (

   ((void *)0)

   ), (UNITY_UINT)(28));

}





void test_PrintAfterOneIsPut(void){

    expectedOutput = "Circular buffer content:\n<17>\n";

    CircularBuffer_Put(buffer, 17);

    CircularBuffer_Print(buffer);

    UnityAssertEqualString((const char*)((expectedOutput)), (const char*)((actualOutput)), (

   ((void *)0)

   ), (UNITY_UINT)(36));

}



void test_PrintNotYetWrappedOrFull(void){

    expectedOutput = "Circular buffer content:\n<10, 20, 30>\n";

    CircularBuffer_Put(buffer, 10);

    CircularBuffer_Put(buffer, 20);

    CircularBuffer_Put(buffer, 30);

    CircularBuffer_Print(buffer);

    UnityAssertEqualString((const char*)((expectedOutput)), (const char*)((actualOutput)), (

   ((void *)0)

   ), (UNITY_UINT)(45));

}





void test_PrintNotYetWrappedAndIsFull(void){

    expectedOutput = "Circular buffer content:\n"

    "<31, 41, 59, 26, 53>\n";

    CircularBuffer b = CircularBuffer_Create(5);

    CircularBuffer_Put(b, 31);

    CircularBuffer_Put(b, 41);

    CircularBuffer_Put(b, 59);

    CircularBuffer_Put(b, 26);

    CircularBuffer_Put(b, 53);

    CircularBuffer_Print(b);

    UnityAssertEqualString((const char*)((expectedOutput)), (const char*)((actualOutput)), (

   ((void *)0)

   ), (UNITY_UINT)(59));

    CircularBuffer_Destroy(b);

}





void test_PrintOldToNewWhenWrappedAndFull(void){

    expectedOutput = "Circular buffer content:\n"

    "<201, 202, 203, 204, 999>\n";

    CircularBuffer b = CircularBuffer_Create(5);

    CircularBuffer_Put(b, 200);

    CircularBuffer_Put(b, 201);

    CircularBuffer_Put(b, 202);

    CircularBuffer_Put(b, 203);

    CircularBuffer_Put(b, 204);

    CircularBuffer_Get(b);

    CircularBuffer_Put(b, 999);

    CircularBuffer_Print(b);

    UnityAssertEqualString((const char*)((expectedOutput)), (const char*)((actualOutput)), (

   ((void *)0)

   ), (UNITY_UINT)(76));

    CircularBuffer_Destroy(b);

}
