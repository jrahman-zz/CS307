#ifndef ROTATE_LOG_ENTRY_H
#define ROTATE_LOG_ENTRY_H

#include "LogEntry.h"
#include "json/json.h"
#include "Util.h"

using namespace std;

class RotateLogEntry : public LogEntry {

public:
    RotateLogEntry(
            unsigned int actorID,
            Rotation rotation);
    RotateLogEntry() = delete;
    ~RotateLogEntry();

protected:
    virtual Json::Value serialize();
    virtual string getType();

private:
    unsigned int m_actorID;
    Rotation m_rotation;
};

#endif
