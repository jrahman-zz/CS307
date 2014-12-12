#include "CompletedObjectiveLogEntry.h"

CompletedObjectiveLogEntry::CompletedObjectiveLogEntry(
    unsigned int completedObjectives,
    unsigned int totalObjectives)
    : m_completedObjectives(completedObjectives)
    , m_totalObjectives(totalObjectives)
{}

CompletedObjectiveLogEntry::~CompletedObjectiveLogEntry() {}

Json::Value CompletedObjectiveLogEntry::serialize() {
    Json::Value root(Json::objectValue);

    root["completedobjectives"] = m_completedObjectives;
    root["totalobjectives"] = m_totalObjectives;

    return root;
}

string CompletedObjectiveLogEntry::getType() {
    return string("completedobjective");
}
