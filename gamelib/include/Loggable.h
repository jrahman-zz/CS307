#ifndef LOGGABLE_H
#define LOGGABLE_H

#include <memory>

using namespace std;

class LogObserver;
class LogEntry;

class Loggable {
public:
    void registerLogObserver(shared_ptr<LogObserver> obs);
    void log(shared_ptr<LogEntry> entry);
    
protected:
    Loggable();
    shared_ptr<LogObserver> m_logObserver;
};

#endif
