#pragma once

#ifdef NOLOG
#define LOG(level, msg) do {} while;
#else

#include <iostream>
#include <syslog.h>

#define LOG(level, msg) do { \
    std::cerr << msg << std::endl; \
    } while(0)

#endif

#define LOGVVV(msg) LOG(LOG_DEBUG, msg)

#define LOGVV(msg) LOG(LOG_DEBUG, msg)
#define LOGV(msg) LOG(LOG_DEBUG, msg)

#define LOGE(msg) LOG(LOG_ERROR, msg)
