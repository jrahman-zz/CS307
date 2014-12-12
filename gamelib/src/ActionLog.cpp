#include "ActionLog.h"

ActionLog::ActionLog(shared_ptr<const TimeKeeper> timekeeper)
    : m_timekeeper(timekeeper)
{}

ActionLog::~ActionLog() {}

bool ActionLog::onLog(shared_ptr<LogEntry> entry) {
    log(entry);
    return true;
}

void ActionLog::log(std::shared_ptr<LogEntry> entry) {
    m_records[m_timekeeper->getTimestep()].push_back(entry);
}

Json::Value ActionLog::getJsonLog() const {
    Json::Value root(Json::ValueType::arrayValue);

    int prev_timestep = -1; 
    for (auto it = m_records.begin(); it != m_records.end(); it++) {
        unsigned int timestep = it->first;
        auto actions = it->second;

        // Fill in gap within array
        while (prev_timestep + 1 < timestep) {
            Json::Value val(Json::ValueType::arrayValue);
            root[++prev_timestep] = val;
        }

        Json::Value list(Json::ValueType::arrayValue);
        // Sort by priority first
        for (auto it2 = actions.begin(); it2 != actions.end(); it2++) {
            auto entry = *it2;
            list.append(entry->toJson());
        }
        root[timestep] = list;
        prev_timestep = timestep;
    }
    return root;
}

void ActionLog::reset() {
    m_records.clear();
}
