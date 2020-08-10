#include "recibir.h"
#include "defs.h"


static const char input_file_name[] = "/home/fedepacher/CESE/Testing Soft/PracticaGit/Testing-Software/TrabajoFinal/output_file_test.xml";


static rx_status_t * status_rx;
static rx_status_t status_img;

/**
 * @brief   Get the data bofy
 * @param line     line read from file
 * @param length   line's length
 * @param body      buffer to store the data body $DATA: BODY *CRC     
 */ 
static void get_body(const char * line, uint32_t length, char * body);

/**
 * @brief   Check frame crc
 * @param line          line read from file
 * @param body          buffer to store the data body $DATA: BODY *CRC
 * @param line_length   line's length
 * @param body_length   body's length
 * @return OK if the file could be read otherwise ERROR
 */ 
static rx_status_t check_crc(const char * line, const char * body, uint32_t line_length, uint32_t body_length);

/**
 * @brief   Convert hexadecimal to string
 * @param   crc     crc in decimal mode
 * @param   string  crc in string mode 
 */ 
static void HexaToString(uint8_t crc, uint8_t *string);

/**
 * @brief   Convert char to hexadecimal
 * @param   character   character to be converted
 * @return   hexadecimal
 */
static uint8_t CharToHexa(uint8_t character);

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

rx_status_t get_data_frame(const char * file_name){
    FILE *fp1;
    rx_status_t status_head = UNDEFINED;
    rx_status_t status_body = UNDEFINED;
    rx_status_t status_tail = UNDEFINED;  
    uint32_t packet_length_start=0;
    uint32_t packet_length_end=0;
    char line[MAX_LENGTH];
    char body[MAX_LENGTH];
    char head[HEADER_SIZE + 1];    
    uint32_t accum = 0; 

    memset(line, '\0', MAX_LENGTH);    
   
    fp1 = fopen(file_name, "r");
    if(fp1 != NULL)
    {
        while(fgets(line, MAX_LENGTH, fp1))
        {          
            if(line[0] == '$'){                                     //get the first cahr of the line
                memset(head, '\0', HEADER_SIZE);
                strncpy(head, (char*)(line + 1) , HEADER_SIZE);    //get the head
                head[HEADER_SIZE] = '\0';

                if(strcmp(head, SOTX) == 0){                        //check if it is the start of frame SOTX:
                    memset(body, '\0', MAX_LENGTH);
                    get_body(line, strlen((char *)line), body);     //get the body
                    status_head = check_crc(line, body, strlen((char *)line), strlen((char *)body));    //check crc
                    packet_length_start = atoi(body + HEADER_SIZE);     //get the length of tx file                    
                }
                
                if(strcmp(head, DATA) == 0){                        //check if it is the body of frame DATA:
                    memset(body, '\0', MAX_LENGTH);                
                    accum += strlen((char *)line) - 8;              //-8 to remove $DATA: and *CRC
                    get_body(line, strlen((char *)line), body);     
                    status_body = check_crc(line, body, strlen((char *)line), strlen((char *)body));
                }
               
                if(strcmp(head, EOTX) == 0){                        //check if it is the start of frame EOTX:
                    memset(body, '\0', MAX_LENGTH);
                    get_body(line, strlen((char *)line), body);
                    status_tail = check_crc(line, body, strlen((char *)line), strlen((char *)body));
                    packet_length_end = atoi(body + HEADER_SIZE);   //get the length of tx file    
                }
                
            }
            else{
                status_img = ERROR;
                printf("Error Getting $\r\n");
                break;
            }
        }
    fclose(fp1);     
    }
    else{
        status_img = ERROR;
        printf("Error Opening File\r\n");
    }

    if(packet_length_start == packet_length_end && packet_length_start == accum){
        status_img = OK;
    }
    else{
        status_img = ERROR;
    }
   /* printf("%d%c%c", packet_length_start, '\r', '\n');
    printf("%d%c%c", packet_length_end, '\r', '\n');
    printf("%d%c%c", accum, '\r', '\n');*/
     
    update_status();
    return status_img;
}

static void get_body(const char * line, uint32_t length, char * body){
    
    uint8_t crcMsg = 0;
    int32_t i;

    for(i = 0; i < length; i++ ){
        if(line[i + 1] != ACH){                  //+1 to avoid '$' 
            body[i] = line[i + 1];              //get the body of the packet    
        }
        else{
            body[i] = '\0';
            break;
        }
    }           
}

static rx_status_t check_crc(const char * line, const char * body, uint32_t line_length, uint32_t body_length){
    uint8_t crcMsg = 0;
    
    if(line[body_length + 1] != '\0' && line[body_length + 2] != '\0'){
        line_length = line_length - 1;

        // Get most significant nibble of CRC
        crcMsg = CharToHexa(*(line + line_length-2)) << 4;
        // Get less significant nibble of CRC and total CRC
        crcMsg |= CharToHexa(*(line + line_length-1));
        
        if(crcMsg == calculate_crc(body, strlen(body))){
            return OK;
        }
        else
        {
            return ERROR;
        }
    }
    else
    {
        return ERROR;
    }

}

static uint8_t CharToHexa(uint8_t character)
{
	uint8_t value;

	/* Convert to capital letter */
	if (character >= 'a' && character <= 'f')
	{
		character -= 0x20;
	}

	switch(character)
	{
		case '1':
		{
			value = 0x01;
		}
		break;

		case '2':
		{
			value = 0x02;
		}
		break;

		case '3':
		{
			value = 0x03;
		}
		break;

		case '4':
		{
			value = 0x04;
		}
		break;

		case '5':
		{
			value = 0x05;
		}
		break;

		case '6':
		{
			value = 0x06;
		}
		break;

		case '7':
		{
			value = 0x07;
		}
		break;

		case '8':
		{
			value = 0x08;
		}
		break;

		case '9':
		{
			value = 0x09;
		}
		break;

		case 'A':
		{
			value = 0x0A;
		}
		break;

		case 'B':
		{
			value = 0x0B;
		}
		break;

		case 'C':
		{
			value = 0x0C;
		}
		break;

		case 'D':
		{
			value = 0x0D;
		}
		break;

		case 'E':
		{
			value = 0x0E;
		}
		break;

		case 'F':
		{
			value = 0x0F;
		}
		break;

		default:
			value = 0x00;
	}

	return value;
}


/* ------- Implementation of private function -------- */
static void HexaToString(uint8_t crc, uint8_t *string)
{
	uint8_t crc_LSB = 0, crc_MSB = 0;

	crc_LSB = crc & 0x0F;
	crc_MSB = (crc & 0xF0) >> 4;

	string[0] = "0123456789ABCDEF"[crc_MSB];
	string[1] = "0123456789ABCDEF"[crc_LSB];
}

uint8_t calculate_crc(const unsigned char * packet, size_t length){
     unsigned int sum;       // nothing gained in using smaller types!
    for ( sum = 0 ; length != 0 ; length-- )
        sum += *(packet++);   // parenthesis not required!
    return (uint8_t)sum;
}