#ifndef DIALOGUE_LOG_ENTRY_H
#define DIALOGUE_LOG_ENTRY_H

#include <string>

#include "LogEntry.h"

class DialogueLogEntry : public LogEntry {
public:
    DialogueLogEntry(unsigned int actorID, string dialogue);
    DialogueLogEntry() = delete;
    ~DialogueLogEntry();

protected:
    virtual Json::Value serialize();
    virtual string getType();

private:
    unsigned int m_actorID;
    string m_dialogue;
};

#endif
