#include "envio.h"


static file_status_t * status_envio;
static file_status_t * status_archivo;
static file_status_t status_img;
FILE * fptr;


void file_constructor(file_status_t * status){
    status_archivo = status;
    status_img = OK;
    *status = status_img;
}

static void update_status(void){
    *status_archivo = status_img;
}


file_status_t open_file(const char * location){
    
    if((fptr = fopen(location, "r")) != NULL){
        status_img = OK;
    }
    else{
        status_img = ERROR;
    }
    update_status();
    return status_img;
}