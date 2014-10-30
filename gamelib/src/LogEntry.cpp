#include "LogEntry.h"

LogEntry::LogEntry(unsigned int timestep) :
	timestep(timestep) {}

LogEntry::~LogEntry() {}

unsigned int LogEntry::getTimestep() {
	return timestep;
}

Json::Value LogEntry::toJson() {
	Json::Value root;
	root["timestamp"] = timestep;
	root["type"] = getType();
	root["data"] = serialize();
	return root;
}
