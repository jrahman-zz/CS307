#include "Loggable.h"

#include "LogObserver.h"

Loggable::Loggable() {
}

void Loggable::registerLogObserver(shared_ptr<LogObserver> obs) {
    m_logObserver = obs;
}

void Loggable::log(shared_ptr<LogEntry> entry) {
    if (m_logObserver != nullptr) {
        m_logObserver->onLog(entry);
    }
}
