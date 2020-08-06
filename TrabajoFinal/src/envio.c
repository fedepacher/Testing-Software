#include "envio.h"


const char ACH  = '*';
const char SCH  = '$';
const char SOTX[] = "SOTX:";
const char DATA[] = "DATA:";
const char EOTX[] = "EOTX:";



//static file_status_t * status_envio;
static file_status_t * status_archivo;
static file_status_t status_img;

/**
 * @brief   Get the file's size
 * @param   file
 * @return  size of the file
 */ 
static long int file_size(FILE * file);

/**
 * @brief   Create the frame to be sent
 * @param   data_out        buffer to store data
 * @param   data_in         buffer in
 * @param   header          header of the frame
 * @param   type_data_in    format of data in 
 * @return  size of the file
 */ 
static void create_frame(char * data_out, void * data_in, const char * header, const char * type_data_in);

/**
 * @brief   Calculate size of file
 * @param   file
 * @return  size of file
 */ 

static long int file_size(FILE * file){
    if(file == NULL)
        return -1;

    fseek(file, 0L, SEEK_END);

    return ftell(file);     //get the size of the file

}

/**
 * @brief   Create the frame to be sent 
 * @param   file_name   name of the file  
 * @param   data_out      
 * @param   header
 * @return  size of file
 */ 
static void create_frame(char * data_out, void * data_in, const char * header, const char * type_data_in){
    uint16_t crc; 
    sprintf((char*)data_out, "%c", SCH);
    sprintf((char*)data_out + strlen((char*)data_out), header);
    sprintf((char*)data_out + strlen((char*)data_out), type_data_in, data_in);
    crc = calculate_crc(data_out + 1, strlen((char*)data_out));
    sprintf((char*)data_out + strlen((char*)data_out), "%c", ACH);
    sprintf((char*)data_out + strlen((char*)data_out), "%02X", crc);
}



void file_constructor(char * buffer, uint32_t length, file_status_t * status){
    status_archivo = status;
    status_img = UNDEFINED;
    *status = status_img;
    memset((char*)buffer, '\0', length);

}



static void update_status(void){
    *status_archivo = status_img;
}


file_status_t open_file(const char * file_name){
    FILE * file = NULL;

    file = fopen(file_name, "r");
    
    if(file != NULL){
        return OK;
    }
    
    return ERROR;
}

file_status_t close_file(FILE * file){
    
    if(file != NULL){
        fclose(file); //sale error cuand lo cierro
        status_img = OK;
    }
    else{    
        status_img = ERROR;
    }
    update_status();
    return status_img;
}


file_status_t create_start_of_frame(const char * file_name, char * buffer){
    //status_img = create_frame(file_name, buffer, SOTX);
    unsigned long file_length = 0;
    FILE * file_aux = fopen(file_name, "r");
           
    if(file_aux == NULL){
        status_img = ERROR;
    }
    else{
        file_length = file_size(file_aux);
       
        if(file_length > 0){
            create_frame(buffer, (unsigned long*) file_length,  SOTX, "%ld");
            status_img = OK;
        }
        else{
          status_img = ERROR;
        } 
               
    }
    fclose(file_aux);
    update_status();
    return status_img;
}

file_status_t create_end_of_frame(const char * file_name, char * buffer){
    unsigned long file_length = 0;
    FILE * file_aux = fopen(file_name, "r");
           
    if(file_aux == NULL){
        status_img = ERROR;
    }
    else{
        file_length = file_size(file_aux);
       
        if(file_length > 0){
            create_frame(buffer, (unsigned long*) file_length,  EOTX, "%ld");
            status_img = OK;
        }
        else{
          status_img = ERROR;
        } 
               
    }
    fclose(file_aux);
    update_status();
    return status_img;
}

uint16_t calculate_crc(const unsigned char * packet, size_t length){
     unsigned int sum;       // nothing gained in using smaller types!
    for ( sum = 0 ; length != 0 ; length-- )
        sum += *(packet++);   // parenthesis not required!
    return (uint8_t)sum;
}


file_status_t create_data_frame(const char * file_name, char * buffer){

    int i, len, accum;
    FILE *fp1;

    char line[MAX_LENGTH];

    fp1 = fopen(file_name, "r");
    if(fp1 != NULL)
    {
        while(fgets(line, MAX_LENGTH, fp1))
        {
            create_frame(buffer, (char*)line,  DATA, "%s");
            printf("%s%c%c", buffer, '\r', '\n');
        }
    fclose(fp1);
    status_img = OK;        
    }
    else{
        status_img = ERROR;
    }

    update_status();
    return status_img;
}
 


file_status_t split_file(const char * file_name, const char * output_file_name, const char * format, char * buffer, const uint32_t length_split){
    int segments=0, i, len, accum;
    FILE *fp1, *fp2;
    long sizeFile;
    
    char smallFileName[MAX_LENGTH];
    char line[MAX_LENGTH];

    fp1 = fopen(file_name, "r");
    
    sizeFile = file_size(fp1);          //once the size is read it must be opened again 
    segments = sizeFile/length_split + 1;//ensure end of file
    

    if(fp1 != NULL)
    {
        fp1 = fopen(file_name, "r");       //re open the file unless fgets return null value 
       
        for(i=0; i<segments; i++)
        {
            accum = 0;
            sprintf(smallFileName, "%s%d.%s", output_file_name, i, format);
            fp2 = fopen(smallFileName, "w");
            if(fp2 != NULL)
            {
               while(fgets(line, MAX_LENGTH, fp1) && accum <= length_split)
               {
                    create_frame(buffer, (char*)line,  DATA, "%s");
                    accum += strlen(buffer);//track size of growing file
                    fputs(buffer, fp2);
               }
               fclose(fp2);
            }
            else{
                status_img = ERROR;
                break;
            }
        }
        fclose(fp1);
        status_img = OK;        
    }
    else{
        status_img = ERROR;
    }

    update_status();
    return status_img;
}