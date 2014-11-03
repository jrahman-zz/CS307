#ifndef LOG_OBSERVER_H
#define LOG_OBSERVER_H

#include <memory>

#include "LogEntry.h"

using namespace std;

class LogObserver {
public:
    LogObserver() {}
    virtual ~LogObserver() {}
    virtual bool onLog(shared_ptr<LogEntry> logEntry) = 0;
};

#endif
