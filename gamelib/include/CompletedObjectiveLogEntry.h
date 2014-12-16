#ifndef COMPLETED_OBJECTIVE_LOG_ENTRY_H
#define COMPLETED_OBJECTIVE_LOG_ENTRY_H

#include "LogEntry.h"
#include "json/json.h"
#include "Util.h"

using namespace std;

class CompletedObjectiveLogEntry : public LogEntry {
public:
    CompletedObjectiveLogEntry(
            unsigned int completedObjectives,
            unsigned int totalObjectives);
    CompletedObjectiveLogEntry() = delete;
    ~CompletedObjectiveLogEntry();

protected:
    Json::Value serialize() override;
    string getType() override;

private:
    unsigned int m_completedObjectives;
    unsigned int m_totalObjectives;

};

#endif
