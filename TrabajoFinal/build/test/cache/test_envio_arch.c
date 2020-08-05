#include "build/temp/_test_envio_arch.c"
#include "src/envio.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"


static file_status_t file_status;





void setUp(void){

    file_constructor(&file_status);

}





void tearDown(void){



}





void test_fail_function(void){

    UnityFail( (("Test inicial de prueba!!!")), (UNITY_UINT)(18));

}
