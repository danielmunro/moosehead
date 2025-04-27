#pragma once

void log_debug(const char *str);
void log_info(const char *str);
void log_error(const char *str);

enum LogLevel {
    LOG_ERROR,
    LOG_INFO,
    LOG_DEBUG
};

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_INFO
#endif
