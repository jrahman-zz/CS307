#include "ActionLog.h"

ActionLog::ActionLog() {}


ActionLog::~ActionLog() {

}

void ActionLog::log(std::shared_ptr<LogEntry> entry) {
    m_records[entry->getTimestep()].push_front(entry);
}

Json::Value ActionLog::getJsonLog() {
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
        for (auto it2 = actions.begin(); it2 != actions.end(); it2++) {
            auto entry = *it2;
            list.append(entry->toJson());
        }
        root[timestep] = list;
        prev_timestep = timestep;
    }
    return root;
}


