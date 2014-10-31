#include "ActionLog.h"

ActionLog::ActionLog() {}


ActionLog::~ActionLog() {

}

void ActionLog::log(std::shared_ptr<LogEntry> entry) {
	m_records[entry->getTimestep()].push_front(entry);
}

Json::Value ActionLog::getJsonLog() {
	Json::Value root;
	
	for (auto it = m_records.begin(); it != m_records.end(); it++) {
		unsigned int timestep = it->first;
		auto actions = it->second;
		if (!root[timestep].isArray()) {
			Json::Value list;
			root[timestep] = list;
		}
		for (auto it2 = actions.begin(); it2 != actions.end(); it2++) {
			auto entry = *it2;
			root[timestep].append(entry->toJson());
		}
	}
	return root;
}


