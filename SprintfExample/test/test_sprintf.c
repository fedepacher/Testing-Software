#include "unity.h"
#include <string.h>

static char output[100];
static const char * expected;

//! @test funcion que se ejecuta al inicio de cada test
void setUp(void){
    memset(output, 0xaa, sizeof(output));
    expected = "";
}

//! @test funcion que se ejeuta al finalizar cada test
void tearDown(void){

}

//! @test funcion que inicializa variable esperada
static void expect(const char * s){
    expected = s;
}

//! @tedt 
static void given(int chatsWritten){
    TEST_ASSERT_EQUAL(strlen(expected), chatsWritten);
    TEST_ASSERT_EQUAL_STRING(expected, output);
    TEST_ASSERT_EQUAL((uint8_t)0xaa, (uint8_t)output[strlen(expected) + 1]);
}

//! @test Prueba de sprintf
void test_sprintf(void){
    //TEST_FAIL_MESSAGE("HOLA");

    TEST_ASSERT_EQUAL(3, sprintf(output, "hey"));
    TEST_ASSERT_EQUAL_STRING("hey", output);
}

//! @test prueba sprintf con parametros
void test_sprintf_con_param(void){
   
    TEST_ASSERT_EQUAL(10, sprintf(output, "hola %s", "mundo"));
    TEST_ASSERT_EQUAL_STRING("hola mundo", output);
}

//! @test prueba sprintf con parametros y con inicializacion de la entrada output
void test_sprintf_con_inicializacion_de_parametros(void){
    expect("hey");
    given(sprintf(output, expected));
}