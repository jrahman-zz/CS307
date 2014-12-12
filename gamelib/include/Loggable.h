#ifndef LOGGABLE_H
#define LOGGABLE_H

#include <memory>

using namespace std;

class LogObserver;
class LogEntry;

class Loggable {
public:
    void registerLogObserver(weak_ptr<LogObserver> obs);
    void log(shared_ptr<LogEntry> entry);
    
protected:
    Loggable();
    weak_ptr<LogObserver> m_logObserver;
};

#endif
