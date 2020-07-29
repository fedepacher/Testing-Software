#include "unity.h"
#include "utils.h"
#include "FormatOutputSpy.h"
#include "CircularBuffer.h"

CircularBuffer buffer;

void setUp(void){
    buffer = CircularBuffer_Create(10);
}

void tearDown(void){
    TEST_ASSERT_TRUE(CircularBuffer_VerifyIntegrity(buffer));
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
    TEST_ASSERT_TRUE(CircularBuffer_IsEmpty(buffer));
}

void test_NotFullAfterCreation(void)
{
    TEST_ASSERT_FALSE(CircularBuffer_IsFull(buffer));
}

void test_NotEmpty(void)
{
    CircularBuffer_Put(buffer, 10046);
    TEST_ASSERT_FALSE(CircularBuffer_IsEmpty(buffer));
}

void test_NotEmptyThenEmpty(void)
{
    CircularBuffer_Put(buffer, 4567);
    TEST_ASSERT_FALSE(CircularBuffer_IsEmpty(buffer));
    CircularBuffer_Get(buffer);
    TEST_ASSERT_TRUE(CircularBuffer_IsEmpty(buffer));
}

void test_GetPutOneValue(void)
{
    CircularBuffer_Put(buffer, 4567);
    TEST_ASSERT_EQUAL_INT(4567, CircularBuffer_Get(buffer));
}

void test_GetPutAFew(void)
{
    CircularBuffer_Put(buffer, 1);
    CircularBuffer_Put(buffer, 2);
    CircularBuffer_Put(buffer, 3);
    TEST_ASSERT_EQUAL_INT(1, CircularBuffer_Get(buffer));
    TEST_ASSERT_EQUAL_INT(2, CircularBuffer_Get(buffer));
    TEST_ASSERT_EQUAL_INT(3, CircularBuffer_Get(buffer));
}

void test_Capacity(void)
{
    CircularBuffer b = CircularBuffer_Create(2);
    TEST_ASSERT_EQUAL_INT(2, CircularBuffer_Capacity(b));
    CircularBuffer_Destroy(b);
}

void test_IsFull(void)
{
    for (int i = 0; i < CircularBuffer_Capacity(buffer); i++)
        CircularBuffer_Put(buffer, i+100);

    TEST_ASSERT_TRUE(CircularBuffer_IsFull(buffer));
}

void test_EmptyToFullToEmpty(void)
{
    for (int i = 0; i < CircularBuffer_Capacity(buffer); i++)
        CircularBuffer_Put(buffer, i+100);

    TEST_ASSERT_TRUE(CircularBuffer_IsFull(buffer));

    for (int j = 0; j < CircularBuffer_Capacity(buffer); j++)
        TEST_ASSERT_EQUAL_INT(j+100, CircularBuffer_Get(buffer));

    TEST_ASSERT_TRUE(CircularBuffer_IsEmpty(buffer));
    TEST_ASSERT_FALSE(CircularBuffer_IsFull(buffer));
}

void test_WrapAround(void)
{
    int capacity = CircularBuffer_Capacity(buffer);
    for (int i = 0; i < capacity; i++)
        CircularBuffer_Put(buffer, i+100);

    TEST_ASSERT_TRUE(CircularBuffer_IsFull(buffer));
    TEST_ASSERT_EQUAL_INT(100, CircularBuffer_Get(buffer));
    TEST_ASSERT_FALSE(CircularBuffer_IsFull(buffer));
    CircularBuffer_Put(buffer, 1000);
    TEST_ASSERT_TRUE(CircularBuffer_IsFull(buffer));

    for (int j = 1; j < capacity; j++)
        TEST_ASSERT_EQUAL_INT(j+100, CircularBuffer_Get(buffer));

    TEST_ASSERT_EQUAL_INT(1000, CircularBuffer_Get(buffer));
    TEST_ASSERT_TRUE(CircularBuffer_IsEmpty(buffer));
}

void test_PutToFullThrows(void)
{
    putManyInTheBuffer(900, CircularBuffer_Capacity(buffer));
    TEST_ASSERT_FALSE(CircularBuffer_Put(buffer, 9999));
}

void test_PutToFullDoesNotDamageContents(void)
{
    putManyInTheBuffer(900, CircularBuffer_Capacity(buffer));

        CircularBuffer_Put(buffer, 9999);

    for (int i = 0; i < CircularBuffer_Capacity(buffer); i++)
        TEST_ASSERT_EQUAL_INT(i+900, CircularBuffer_Get(buffer));

    TEST_ASSERT_TRUE(CircularBuffer_IsEmpty(buffer));
}

void test_GetFromEmptyReturns0(void)
{
    TEST_ASSERT_EQUAL_INT(0, CircularBuffer_Get(buffer));
}




