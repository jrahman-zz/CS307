#ifndef MOVE_LOG_ENTRY_H
#define MOVE_LOG_ENTRY_H

#include <string>

#include "LogEntry.h"
#include "json/json.h"
#include "Position.h"


using namespace std;

class MoveLogEntry : public LogEntry {

public:
    /*
     * Construct a new MoveLogEntry
     */
    MoveLogEntry(
        unsigned int actorID,
        Position position);
    MoveLogEntry() = delete;
    virtual ~MoveLogEntry();

protected:
    Json::Value serialize() override;
    string getType() override;

private:
    unsigned int m_actorID;
    Position m_position;
};

#endif // MOVE_LOG_ENTRY_H
