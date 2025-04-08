#ifndef MOOSEHEAD_LOG_H
#define MOOSEHEAD_LOG_H

void log_debug(const char *str);
void log_string(const char *str);
void log_error(const char *str);

enum LogLevel {
    LOG_ERROR,
    LOG_INFO,
    LOG_DEBUG
};

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_INFO
#endif

#endif //MOOSEHEAD_LOG_H
