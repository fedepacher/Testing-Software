#include "build/temp/_test_envio_arch.c"
#include "src/envio.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"


static const char file_name[] = "/home/fedepacher/Desktop/MSystem0.xml";

static file_status_t file_status;





void setUp(void){

    file_constructor(&file_status);

}





void tearDown(void){



}















void test_open_file(void){

    file_status = open_file((char*)file_name);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((file_status)), (

   ((void *)0)

   ), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_INT);

}
