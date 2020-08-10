#include "recibir.h"
#include "defs.h"


static rx_status_t * status_rx;
static rx_status_t status_img;


/**
 * @brief   Update status
 */ 
static void update_status(void);

static void update_status(void){
    *status_rx = status_img;
}


void rx_constructor(char * buffer, uint32_t length, rx_status_t * status){
    status_rx = status;
    status_img = UNDEFINED;
    *status = status_img;
    memset((char*)buffer, '\0', length);

}

rx_status_t get_data_frame(const char * file_name, char * buffer){

    int i, len, accum;
    FILE *fp1;

    char line[MAX_LENGTH];

    fp1 = fopen(file_name, "r");
    if(fp1 != NULL)
    {
        accum = 0;
        while(fgets(line, MAX_LENGTH, fp1))
        {          
            sprintf(buffer + accum, line);
            accum += strlen(line);
        }

        /* CON EL BUFFER LLENO BUSCAR EL $ EL DATA: Y * PARA ANALIZAR EL CHECKSUM */

    fclose(fp1);
    status_img = OK;        
    }
    else{
        status_img = ERROR;
    }

    update_status();
    return status_img;
}

uint16_t calculate_crc(const unsigned char * packet, size_t length){
     unsigned int sum;       // nothing gained in using smaller types!
    for ( sum = 0 ; length != 0 ; length-- )
        sum += *(packet++);   // parenthesis not required!
    return (uint8_t)sum;
}