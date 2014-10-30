#include "LogEntry.h"

LogEntry::LogEntry(unsigned int timestep)
	: m_timestep(timestep)
{}

LogEntry::~LogEntry() {}

unsigned int LogEntry::getTimestep() {
	return m_timestep;
}

Json::Value LogEntry::toJson() {
	Json::Value root;
	root["timestamp"] = m_timestep;
	root["type"] = getType();
	root["data"] = serialize();
	return root;
}
