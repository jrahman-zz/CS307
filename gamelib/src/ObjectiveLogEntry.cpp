#include "ObjectiveLogEntry.h"

ObjectiveLogEntry::ObjectiveLogEntry(
        int completed,
        int total) 
    : LogEntry()
    , m_total(total)
    , m_completed(completed)
{
}

ObjectiveLogEntry::~ObjectiveLogEntry() {
}

Json::Value ObjectiveLogEntry::serialize() {
    Json::Value root(Json::objectValue);
    root["completed"] = m_completed;
    root["total"] = m_total;

    return root;
}

string ObjectiveLogEntry::getType() {
    return "objective";
}
