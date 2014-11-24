#ifndef OBJECTIVE_LOG_ENTRY_H
#define OBJECTIVE_LOG_ENTRY_H

#include <string>

#include "LogEntry.h"
#include "json/json.h"

using namespace std;

class ObjectiveLogEntry : public LogEntry {
    
public:
    /*
     * Construct a new instance of the log entry
     */
    ObjectiveLogEntry(int completed, int total);
    ObjectiveLogEntry() = delete;
    virtual ~ObjectiveLogEntry();

protected:
    Json::Value serialize() override;
    string getType() override;
private:
    int m_total;
    int m_completed;
};

#endif
