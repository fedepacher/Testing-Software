#include "stdio.h"


typedef enum{
    OK = 0, 
    ERROR = 1,
    INPROGRESS = 2,
}file_status_t;


/**
 * @brief   File constuctor, initialize file status
 * @param   status    file status
 */
void file_constructor(file_status_t * status);

/**
 * @brief   Open file
 * @param   location    file dir
 * @return  OK if the file could open otherwise ERROR
 */
file_status_t open_file(const char * location);