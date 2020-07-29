#include "utils.h"
#include <stdio.h>

/*static int FormatOutput_Impl(const char * format, ...){
    printf(format);
}*/

int (*FormatOutput)(const char * format, ...) = printf;