#ifndef DIALOGUE_LOG_ENTRY_H
#define DIALOGUE_LOG_ENTRY_H

#include <string>

#include "LogEntry.h"

class DialogueLogEntry : public LogEntry {
public:
    DialogueLogEntry(
            unsigned int actorID,
            string dialogue
        );
    DialogueLogEntry() = delete;
    virtual ~DialogueLogEntry();

protected:
    Json::Value serialize() override;
    string getType() override;

private:
    unsigned int m_actorID;
    string m_dialogue;
};

#endif
