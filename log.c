#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdarg.h>

#include "log.h"

int log_level = INFO;

int set_log_level(int level) {
    int last = log_level;
    log_level = level;
    return last;
}

void trace(int level, char *format, ...) {
    if (level >= log_level) {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
}
