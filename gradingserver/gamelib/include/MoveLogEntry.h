#ifndef MOVE_LOG_ENTRY_H
#define MOVE_LOG_ENTRY_H

#include "LogEntry.h"

#include "json/json.h"

class MoveLogEntry : public LogEntry {

public:
	/*
	 * Construct a new MoveLogEntry
 	 */
	MoveLogEntry(
		unsigned int timestamp,
		unsigned int actorID,
		Position position);
	~MoveLogEntry();

protected:
private:
	unsigned int actorID;
	Position position;
};

#endif // MOVE_LOG_ENTRY_H
