#include "build/temp/_test_envio_arch.c"
#include "src/envio.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"


static const char file_name[] = "/home/fedepacher/Desktop/Pruebas/MSystem0.xml";

static const char output_file_name[] = "/home/fedepacher/Desktop/Pruebas/output_split_";

static const char output_file_format[] = "xml";

static file_status_t file_status;

static FILE file;

static char buffer[1 + 5 + 50 + 1 + 2];





void setUp(void){

    file_constructor(buffer, strlen((char*)buffer), &file_status);

}





void tearDown(void){



}















void test_open_file(void){



    file_status = open_file(file_name);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((file_status)), (

   ((void *)0)

   ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_INT);

}







void test_create_start_of_frame(void){

    file_status = create_start_of_frame(file_name, &buffer[0]);

    printf("%s", buffer);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((file_status)), (

   ((void *)0)

   ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualString((const char*)(("$SOTX:150*1E")), (const char*)((buffer)), (

   ((void *)0)

   ), (UNITY_UINT)(39));

}





void test_create_data_frame(void){

    file_status = create_data_frame(file_name, &buffer[0]);



    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((file_status)), (

   ((void *)0)

   ), (UNITY_UINT)(46), UNITY_DISPLAY_STYLE_INT);



}





void test_split_file(void){

    file_status = split_file(file_name, output_file_name, output_file_format, buffer, 2000);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((file_status)), (

   ((void *)0)

   ), (UNITY_UINT)(53), UNITY_DISPLAY_STYLE_INT);

}





void test_create_end_of_frame(void){

    file_status = create_end_of_frame(file_name, &buffer[0]);

    printf("%s", buffer);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((file_status)), (

   ((void *)0)

   ), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualString((const char*)(("$EOTX:150*10")), (const char*)((buffer)), (

   ((void *)0)

   ), (UNITY_UINT)(61));

}
