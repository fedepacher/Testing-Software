#include "recibir.h"
#include "defs.h"


static const char input_file_name[] = "/home/fedepacher/Desktop/Pruebas/output_file_test1.xml";


static rx_status_t * status_rx;
static rx_status_t status_img;

static rx_status_t check_crc(const char * line, uint32_t length);

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
    
    
    char line[MAX_LENGTH];
    char head[HEADER_SIZE + 1];
    
    

    memset(line, '\0', MAX_LENGTH);
    memset(head, '\0', HEADER_SIZE);

    fp1 = fopen(file_name, "r");
    if(fp1 != NULL)
    {
        while(fgets(line, MAX_LENGTH, fp1))
        {          
            if(line[0] == '$'){
                strncpy(head, (char*)(line + 1) , HEADER_SIZE);    //get the head
                head[HEADER_SIZE] = '\0';
                //printf("%s", head);

                if(strcmp(head, SOTX)){
                    status_img = check_crc(line, strlen((char *)line));
                }
                
                if(strcmp(head, DATA) == 0){                    
                    status_img = check_crc(line, strlen((char *)line));
                }
                if(strcmp(head, EOTX)){
                    status_img = check_crc(line, strlen((char *)line));
                }
            }
            else{
                status_img = ERROR;
            }
        }
    fclose(fp1);     
    }
    else{
        status_img = ERROR;
        printf("error 118\r\n");
    }

    update_status();
    return status_img;
}

static rx_status_t check_crc(const char * line, uint32_t length){
    char body[MAX_LENGTH];
    uint32_t get_asterisk_postion = 0;                      //indicate where in the array is the *
    uint8_t crcMsg = 0;
    int32_t i;

    memset(body, '\0', MAX_LENGTH);

    get_asterisk_postion = 0;
    for(i = 0; i < length; i++ ){
        if(line[i + 1] != ACH){                  //+1 to avoid '$' 
            body[i] = line[i + 1];              //get the body of the packet    
        }
        else{
            body[i] = '\0';
            get_asterisk_postion = i + 1;       //+1 to add '$'   
            break;
        }
    }                       
    
    if(line[get_asterisk_postion + 1] != '\0' && line[get_asterisk_postion + 2] != '\0'){
        length = length - 1;

        // Get most significant nibble of CRC
        crcMsg = CharToHexa(*(line + length-2)) << 4;
        // Get less significant nibble of CRC and total CRC
        crcMsg |= CharToHexa(*(line + length-1));
        
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