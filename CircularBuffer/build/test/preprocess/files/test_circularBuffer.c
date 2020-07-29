#include "build/temp/_test_circularBuffer.c"
#include "src/CircularBuffer.h"
#include "src/FormatOutputSpy.h"
#include "src/utils.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"


CircularBuffer buffer;



void setUp(void){

    buffer = CircularBuffer_Create(10);

}



void tearDown(void){

    do {if ((CircularBuffer_VerifyIntegrity(buffer))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(13)));}} while(0);

    CircularBuffer_Destroy(buffer);

}



void putManyInTheBuffer(int seed, int howMany)

{

   for (int i = 0; i < howMany; i++)

        CircularBuffer_Put(buffer, i+seed);

}



void test_Create(void)

{



}



void test_EmptyAfterCreation(void)

{

    do {if ((CircularBuffer_IsEmpty(buffer))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(30)));}} while(0);

}



void test_NotFullAfterCreation(void)

{

    do {if (!(CircularBuffer_IsFull(buffer))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(35)));}} while(0);

}



void test_NotEmpty(void)

{

    CircularBuffer_Put(buffer, 10046);

    do {if (!(CircularBuffer_IsEmpty(buffer))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(41)));}} while(0);

}



void test_NotEmptyThenEmpty(void)

{

    CircularBuffer_Put(buffer, 4567);

    do {if (!(CircularBuffer_IsEmpty(buffer))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(47)));}} while(0);

    CircularBuffer_Get(buffer);

    do {if ((CircularBuffer_IsEmpty(buffer))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(49)));}} while(0);

}



void test_GetPutOneValue(void)

{

    CircularBuffer_Put(buffer, 4567);

    UnityAssertEqualNumber((UNITY_INT)((4567)), (UNITY_INT)((CircularBuffer_Get(buffer))), (

   ((void *)0)

   ), (UNITY_UINT)(55), UNITY_DISPLAY_STYLE_INT);

}



void test_GetPutAFew(void)

{

    CircularBuffer_Put(buffer, 1);

    CircularBuffer_Put(buffer, 2);

    CircularBuffer_Put(buffer, 3);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((CircularBuffer_Get(buffer))), (

   ((void *)0)

   ), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((2)), (UNITY_INT)((CircularBuffer_Get(buffer))), (

   ((void *)0)

   ), (UNITY_UINT)(64), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((3)), (UNITY_INT)((CircularBuffer_Get(buffer))), (

   ((void *)0)

   ), (UNITY_UINT)(65), UNITY_DISPLAY_STYLE_INT);

}



void test_Capacity(void)

{

    CircularBuffer b = CircularBuffer_Create(2);

    UnityAssertEqualNumber((UNITY_INT)((2)), (UNITY_INT)((CircularBuffer_Capacity(b))), (

   ((void *)0)

   ), (UNITY_UINT)(71), UNITY_DISPLAY_STYLE_INT);

    CircularBuffer_Destroy(b);

}



void test_IsFull(void)

{

    for (int i = 0; i < CircularBuffer_Capacity(buffer); i++)

        CircularBuffer_Put(buffer, i+100);



    do {if ((CircularBuffer_IsFull(buffer))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(80)));}} while(0);

}



void test_EmptyToFullToEmpty(void)

{

    for (int i = 0; i < CircularBuffer_Capacity(buffer); i++)

        CircularBuffer_Put(buffer, i+100);



    do {if ((CircularBuffer_IsFull(buffer))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(88)));}} while(0);



    for (int j = 0; j < CircularBuffer_Capacity(buffer); j++)

        UnityAssertEqualNumber((UNITY_INT)((j+100)), (UNITY_INT)((CircularBuffer_Get(buffer))), (

       ((void *)0)

       ), (UNITY_UINT)(91), UNITY_DISPLAY_STYLE_INT);



    do {if ((CircularBuffer_IsEmpty(buffer))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(93)));}} while(0);

    do {if (!(CircularBuffer_IsFull(buffer))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(94)));}} while(0);

}



void test_WrapAround(void)

{

    int capacity = CircularBuffer_Capacity(buffer);

    for (int i = 0; i < capacity; i++)

        CircularBuffer_Put(buffer, i+100);



    do {if ((CircularBuffer_IsFull(buffer))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(103)));}} while(0);

    UnityAssertEqualNumber((UNITY_INT)((100)), (UNITY_INT)((CircularBuffer_Get(buffer))), (

   ((void *)0)

   ), (UNITY_UINT)(104), UNITY_DISPLAY_STYLE_INT);

    do {if (!(CircularBuffer_IsFull(buffer))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(105)));}} while(0);

    CircularBuffer_Put(buffer, 1000);

    do {if ((CircularBuffer_IsFull(buffer))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(107)));}} while(0);



    for (int j = 1; j < capacity; j++)

        UnityAssertEqualNumber((UNITY_INT)((j+100)), (UNITY_INT)((CircularBuffer_Get(buffer))), (

       ((void *)0)

       ), (UNITY_UINT)(110), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((UNITY_INT)((1000)), (UNITY_INT)((CircularBuffer_Get(buffer))), (

   ((void *)0)

   ), (UNITY_UINT)(112), UNITY_DISPLAY_STYLE_INT);

    do {if ((CircularBuffer_IsEmpty(buffer))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(113)));}} while(0);

}



void test_PutToFullThrows(void)

{

    putManyInTheBuffer(900, CircularBuffer_Capacity(buffer));

    do {if (!(CircularBuffer_Put(buffer, 9999))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(119)));}} while(0);

}



void test_PutToFullDoesNotDamageContents(void)

{

    putManyInTheBuffer(900, CircularBuffer_Capacity(buffer));



        CircularBuffer_Put(buffer, 9999);



    for (int i = 0; i < CircularBuffer_Capacity(buffer); i++)

        UnityAssertEqualNumber((UNITY_INT)((i+900)), (UNITY_INT)((CircularBuffer_Get(buffer))), (

       ((void *)0)

       ), (UNITY_UINT)(129), UNITY_DISPLAY_STYLE_INT);



    do {if ((CircularBuffer_IsEmpty(buffer))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(131)));}} while(0);

}



void test_GetFromEmptyReturns0(void)

{

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((CircularBuffer_Get(buffer))), (

   ((void *)0)

   ), (UNITY_UINT)(136), UNITY_DISPLAY_STYLE_INT);

}
