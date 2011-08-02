/*!
 * \brief logprintf
 *
 * \author Higepon
 * \param format specifies how subsequent arguments
 * \return  none
 *
 * */
#include <stdio.h>
#include <stdarg.h>
#include <monapi/syscall.h>

void logprintf(const char* format, ...) {

    char str[4096];
    str[0] = '\0';
    va_list args;
    int result;

    va_start(args, format);
    result = vsprintf(str, format, args);
    va_end(args);
    if(result > 4096) {
        /* over flow */
        syscall_log_print("logprintf:overflow");
    }

    syscall_log_print(str);
}

