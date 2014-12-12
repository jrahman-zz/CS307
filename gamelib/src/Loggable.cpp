#include "Loggable.h"

#include "LogObserver.h"

Loggable::Loggable() {
}

void Loggable::registerLogObserver(weak_ptr<LogObserver> obs) {
    m_logObserver = obs;
}

void Loggable::log(shared_ptr<LogEntry> entry) {
    auto observer = m_logObserver.lock();

    if (observer != nullptr) {
        observer->onLog(entry);
    }
}
