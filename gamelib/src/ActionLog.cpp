#include "ActionLog.h"

ActionLog::ActionLog() {}


ActionLog::~ActionLog() {

}

void ActionLog::log(std::shared_ptr<LogEntry> entry) {
	auto it = records.find(entry->getTimestep());
	if (it == records.end()) {
		std::shared_ptr<std::list<std::shared_ptr<LogEntry>>> ptr(new std::list<std::shared_ptr<LogEntry>>());
		records[entry->getTimestep()] = ptr;
	}
	records[entry->getTimestep()]->push_front(entry);
}

Json::Value ActionLog::getJsonLog() {
	Json::Value root;
	
	for (auto it = records.begin(); it != records.end(); it++) {
		unsigned int timestep = it->second;
		auto entry = it->first;
		if (!root[timestep].isArray()) {
			Json::Value list;
			root[timestep] = list;
		}
		root[timestep].append(entry->toJson());
	}
	return root;
}


