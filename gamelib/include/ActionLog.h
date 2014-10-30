#ifndef ACTION_LOG_H
#define ACTION_LOG_H

#include <map>
#include <memory>
#include <list>

#include "json/json.h"
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
	void log(std::shared_ptr<LogEntry> entry);
	Json::Value getJsonLog();
protected:
private:
	std::map<unsigned int, std::shared_ptr<std::list<std::shared_ptr<LogEntry>>>> records;
};

#endif // ACTION_LOG_H
