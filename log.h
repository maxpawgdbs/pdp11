#pragma once

enum LOG_LEVEL {
    DEBUG,
    TRACE,
    INFO,
    WARNING,
    ERROR
};

extern int log_level;

int set_log_level(int level);

void trace(int level, const char *format, ...);