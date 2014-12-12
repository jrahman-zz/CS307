#include "LogEntry.h"

LogEntry::LogEntry()
{}

LogEntry::~LogEntry() {}

Json::Value LogEntry::toJson() {
    Json::Value root(Json::ValueType::objectValue);
    root["type"] = getType();
    root["data"] = serialize();
    return root;
}
