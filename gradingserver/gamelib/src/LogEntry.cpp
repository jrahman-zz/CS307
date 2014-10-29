#include "LogEntry.h"

LogEntry::LogEntry(unsigned int timestep) :
	timestep(timestep) {}

LogEntry::~LogEntry() {}

Json::Value LogEntry::toJson() {
	Json::Value root;
	root["timestamp"] = timestep;
	root["type"] = getType();
	root["data"] = serialize();
	return root;
}
