#include "stdio.h"
#include "stdint.h"
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH      255  
#define BUFFER_SIZE     50  //bytes to be sent in a packet
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
}file_status_t;


/**
 * @brief   File constuctor, initialize file status
 * @param   buffer  process buffer
 * @param   length  buffer's length
 * @param   status  process status
 */
void file_constructor(char * buffer, uint32_t length, file_status_t * status);

/**
 * @brief   Open file
 * @param   file_name    file dir
 * @return  OK if the file could open otherwise ERROR
 */
file_status_t open_file(const char * file_name);

/**
 * @brief   Close file and update status
 * @param   file         file pointer 
 * @return  OK if the file could open otherwise ERROR
 */
file_status_t close_file(FILE * file);


/**
 * @brief   Create the firt frame to be sent
 *
 * $SOTX: + size of file + *(2bytes)CRC 
 * 
 * @param   file_name    file name
 * @param   buffer       buffer to store the packet 
 * @return  OK if the file could open otherwise ERROR
 */
file_status_t create_start_of_frame(const char * file_name, char * buffer);

/**
 * @brief   Create the end frame to be sent
 *
 * $EOTX: + size of file + *(2bytes)CRC 
 * 
 * @param   file_name    file name
 * @param   buffer       buffer to store the packet 
 * @return  OK if the file could open otherwise ERROR
 */
file_status_t create_end_of_frame(const char * file_name, char * buffer);

/**
 * @brief   Create data frames to be sent, read each file's line and create the frame as follow
 *
 * $DATA: + size of file + *(2bytes)CRC 
 * 
 * @param   file_name    file name
 * @param   buffer       buffer to store the packet 
 * @return  OK if the file could open otherwise ERROR
 */ 
file_status_t create_data_frame(const char * file_name, char * buffer);


/**
 * @brief   Calculate the 2bytes CRC
 * @param   packet  packet to calculate crc 
 * @param   length  packet's length
 *  @return  CRC
 */
uint16_t calculate_crc(const unsigned char * packet, size_t length);

/**
 * @brief   Split the file into smaller files and create the data frame to be sent
 * @param   file_name           input file name
 * @param   output_file_name    output file name
 * @param   format              file format
 * @param   buffer              buffer to store the frame befor send it to the file 
 * @param   length_split        maximun output file length in bytes
 *  @return  CRC
 */
file_status_t split_file(const char * file_name, const char * output_file_name, const char * format, char * buffer, const uint32_t length_split);