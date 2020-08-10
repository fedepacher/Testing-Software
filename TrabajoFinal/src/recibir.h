#include "stdio.h"
#include "stdint.h"
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH      255  
#define BUFFER_SIZE     4096  //bytes to be sent in a packet
#define CRC_SIZE        2   //2 crc bytes
#define ASTERISCO_SIZE  1   //1 byte for *
#define FIRST_CHAR_SIZE 1   //1 byte for $
#define DECIMAL         10
#define HEADER_SIZE     5

typedef enum{
    OK = 0, 
    ERROR = 1,
    INPROGRESS = 2,
    UNDEFINED  =4,
}rx_status_t;


/**
 * @brief   File constuctor, initialize file status
 * @param   buffer  process buffer
 * @param   length  buffer's length
 * @param   status  process status
 */
void rx_constructor(char * buffer, uint32_t length, rx_status_t * status);

/**
 * @brief   Calculate the 2bytes CRC
 * @param   packet  packet to calculate crc 
 * @param   length  packet's length
 *  @return  CRC
 */
uint8_t calculate_crc(const unsigned char * packet, size_t length);

/**
 * @brief   Ge data from the file and reconstruct the original file
 * @param   file_name  file where the info is read
 *  @return OK if the file could be read otherwise ERROR
 */
rx_status_t get_data_frame(const char * file_name);