#ifndef LOG_OBSERVER_H
#define LOG_OBSERVER_H

#include "LogEntry.h"

class LogObserver {

public:
    LogObserver() {}
    virtual ~LogObserver() {}
    virtual bool onLog(LogEntry& logEntry) = 0;
}

#endif
