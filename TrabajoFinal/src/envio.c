#include "envio.h"
#include "defs.h"


static const char output_file_name[] = "/home/fedepacher/CESE/Testing Soft/PracticaGit/Testing-Software/TrabajoFinal/output_file_test.xml";

//static tx_status_t * status_envio;
static tx_status_t * status_tx;
static tx_status_t status_img;

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
 * @brief   Create a file with start frame data frame and end frame in order to test receive functions
 * @param   output_file_name    output file name
 * @param   buffer              buffer to store the frame befor send it to the file 
 *  @return  OK if the file could create it otherwise ERROR
 */
static tx_status_t create_file(const char * output_file_name, char * buffer);

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
    uint8_t crc; 
    sprintf((char*)data_out, "%c", SCH);
    sprintf((char*)data_out + strlen((char*)data_out), "%s", header);
    sprintf((char*)data_out + strlen((char*)data_out), type_data_in, data_in);
    crc = calculate_crc(data_out + 1, strlen((char*)data_out) - 1);
    sprintf((char*)data_out + strlen((char*)data_out), "%c", ACH);
    sprintf((char*)data_out + strlen((char*)data_out), "%02X", crc);

    //Create a file to debug the receive file
    create_file(output_file_name, data_out);
}

/**
 * @brief   Update status
 */ 
static void update_status(void);

void tx_constructor(char * buffer, uint32_t length, tx_status_t * status){
    status_tx = status;
    status_img = UNDEFINED;
    *status = status_img;
    memset((char*)buffer, '\0', length);
    
}



static void update_status(void){
    *status_tx = status_img;
}


tx_status_t open_file(const char * file_name){
    FILE * file = NULL;

    file = fopen(file_name, "r");
    
    if(file != NULL){
        return OK;
    }    
    return ERROR;
}

tx_status_t close_file(FILE * file){
    
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


tx_status_t create_start_of_frame(const char * file_name, char * buffer){
    
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

tx_status_t create_end_of_frame(const char * file_name, char * buffer){
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

uint8_t calculate_crc(const unsigned char * packet, size_t length){
     unsigned int sum;       // nothing gained in using smaller types!
    for ( sum = 0 ; length != 0 ; length-- )
        sum += *(packet++);   // parenthesis not required!
    return (uint8_t)sum;
}


tx_status_t create_data_frame(const char * file_name, char * buffer){

    int i, len, accum;
    FILE *fp1;

    char line[MAX_LENGTH];

    fp1 = fopen(file_name, "r");
    if(fp1 != NULL)
    {
        while(fgets(line, MAX_LENGTH, fp1))
        {
            len = strlen(line);
            if(line[len - 2] == '\r' && line[len - 1] == '\n'){
                line[len - 2] = '\0';
            }
            else{
                if(line[len - 1] == '\n')
                    line[len - 1] = '\0';               
            }
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
 

static tx_status_t create_file(const char * output_file_name, char * buffer){
    
    char buffer_aux[MAX_LENGTH];
    uint32_t length;
    FILE *fp1;
    memset(buffer_aux, '\0', MAX_LENGTH);   //clean the aux buffer
    sprintf(buffer_aux, "%s", buffer);      //copy buffer to aux buffer
    
    fp1 = fopen(output_file_name, "a");     //create output file
    if(fp1 != NULL)
    {   
        length = strlen(buffer_aux);
        *(buffer_aux + length) = '\n';      //add \n at the end of the file
        fputs(buffer_aux, fp1);             //append data to the file   
    }
    else{
        return ERROR;   
    }
    fclose(fp1);                            //close file
    return OK;
}

