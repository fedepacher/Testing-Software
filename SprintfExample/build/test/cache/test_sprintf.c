#include "build/temp/_test_sprintf.c"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"




TEST_GROUP(sprintf);



static char output[100];

static const char * expected;





void setUp(void){

    memset(output, 0xaa, sizeof(output));

    expected = "";

}





void tearDown(void){



}





static void expect(const char * s){

    expected = s;

}





static void given(int chatsWritten){

    UnityAssertEqualNumber((UNITY_INT)((strlen(expected))), (UNITY_INT)((chatsWritten)), (

   ((void *)0)

   ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualString((const char*)((expected)), (const char*)((output)), (

   ((void *)0)

   ), (UNITY_UINT)(28));

    UnityAssertEqualNumber((UNITY_INT)(((uint8_t)0xaa)), (UNITY_INT)(((uint8_t)output[strlen(expected) + 1])), (

   ((void *)0)

   ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_INT);

}





void test_sprintf(void){





    UnityAssertEqualNumber((UNITY_INT)((3)), (UNITY_INT)((sprintf(output, "hey"))), (

   ((void *)0)

   ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualString((const char*)(("hey")), (const char*)((output)), (

   ((void *)0)

   ), (UNITY_UINT)(37));

}





void test_sprintf_con_param(void){



    UnityAssertEqualNumber((UNITY_INT)((10)), (UNITY_INT)((sprintf(output, "hola %s", "mundo"))), (

   ((void *)0)

   ), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualString((const char*)(("hola mundo")), (const char*)((output)), (

   ((void *)0)

   ), (UNITY_UINT)(44));

}





void test_sprintf_con_inicializacion_de_parametros(void){

    expect("hey");

    given(sprintf(output, expected));

}
