#ifndef ACTION_LOG_H
#define ACTION_LOG_H

#include "LogEntry.h"

/*
 * Class to represent log of actions in the game world
 * Will eventually container serialization code into JSON or another format
 *
 */
class ActionLog {

public:
	ActionLog();
	~ActionLog();
	void log(LogEntry& entry);

protected:

private:
	// TODO, add data structures here	
};

#endif // ACTION_LOG_H
