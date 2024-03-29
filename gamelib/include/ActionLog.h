#ifndef ACTION_LOG_H
#define ACTION_LOG_H

#include <unordered_map>
#include <memory>
#include <list>

#include "json/json.h"
#include "LogEntry.h"
#include "LogObserver.h"
#include "TimeKeeper.h"

using namespace std;

/*
 * Class to represent log of actions in the game world
 * Will eventually container serialization code into JSON or another format
 *
 */
class ActionLog : public LogObserver {

public:
    ActionLog(shared_ptr<const TimeKeeper> timekeeper);
    virtual ~ActionLog();

    virtual bool onLog(shared_ptr<LogEntry> entry);
    Json::Value getJsonLog() const;
    void reset();

protected:
    void log(shared_ptr<LogEntry> entry);

private:
    unordered_map<unsigned int, list<shared_ptr<LogEntry>>> m_records;

    shared_ptr<const TimeKeeper> m_timekeeper;
};

#endif // ACTION_LOG_H
