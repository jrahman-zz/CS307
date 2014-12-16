#ifndef OBJECTIVE_LOG_ENTRY_H
#define OBJECTIVE_LOG_ENTRY_H

#include <string>

#include "LogEntry.h"
#include "json/json.h"

using namespace std;

class ObjectiveLogEntry : public LogEntry {
public:
    
    ObjectiveLogEntry(string dialogue, string prompt, string templateCode, int objectiveId);
    ObjectiveLogEntry() = delete;
    virtual ~ObjectiveLogEntry();

protected:
    Json::Value serialize() override;
    string getType();
private:
    string m_dialogue; // Character dialogue to start the objective
    string m_prompt; // Prompt info to display above the text box 
    string m_templateCode; // Basic template code (optional), can be empty
    int m_objectiveId; // Objective ID for database purposes
};

#endif
