#include "LogEntry.h"

LogEntry::LogEntry(unsigned int timestep, bool result)
	: m_timestep(timestep)
	, m_result(result)
{}

LogEntry::~LogEntry() {}

unsigned int LogEntry::getTimestep() {
	return m_timestep;
}

bool LogEntry::getResult() {
	return m_result;
}

Json::Value LogEntry::toJson() {
	Json::Value root;
	root["timestamp"] = m_timestep;
	root["type"] = getType();
	root["data"] = serialize();
	return root;
}
