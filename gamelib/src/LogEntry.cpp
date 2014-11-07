#include "LogEntry.h"

LogEntry::LogEntry()
{}

LogEntry::~LogEntry() {}

Json::Value LogEntry::toJson() {
    Json::Value root;
    root["type"] = getType();
    root["data"] = serialize();
    return root;
}
